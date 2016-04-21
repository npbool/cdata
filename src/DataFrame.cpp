#include "DataFrame.h"
#include <cstdio>
#include <algorithm>
#include <exception>
#include <iostream>
#include <unordered_map>
#include <cassert>
#include <queue>
#include <thread>
#include <mutex>

using namespace cdata;
using namespace std;


const size_t BUF_LINE = 100;
const size_t MAX_LEN = 1024;
template<class VT>
class SafeQueue
{
public:
    VT get()
    {
        while (1) {
            mtx.lock();
            if (!q.empty()) {
                VT r = q.front();
                q.pop();
                mtx.unlock();
                return r;
            } else {
                mtx.unlock();
            }
        }
    }
    void put(VT v)
    {
        mtx.lock();
        q.push(v);
        mtx.unlock();
    }
private:
    std::mutex mtx;
    std::queue<VT> q;
};
struct Pool
{
public:
    SafeQueue<char *> avail;
    SafeQueue<char *> used;

    char *fetch_avail()
    {
        return avail.get();
    }
    void put_avail(char *buf)
    {
        avail.put(buf);
    }
    char *fetch_used()
    {
        return used.get();
    }
    void put_used(char *buf)
    {
        used.put(buf);
    }
};

void func(Pool &pool, DataFrame &part)
{
    char *buf;
    while ((buf = pool.fetch_used())) {
        part.parse_line(buf, ',');
        pool.put_avail(buf);
    }
}

DataFrame *DataFrame::read_csv(const char *path, unordered_map<string, BaseSeriesFactory> &factory, int nrow)
{
    FILE *file = fopen(path, "r");
    if (!file) {
        throw runtime_error("Can't open " + string(path));
    }

    DataFrame *df = new DataFrame();

    char buf[BUF_LINE][MAX_LEN];
    Pool pool;
    for (int i = 0; i < BUF_LINE; ++i) {
        pool.put_avail(buf[i]);
    }

    const int NT = 3;
    DataFrame partition[NT];
    std::thread threads[NT];
    for (int i = 0; i < NT; ++i) {
        threads[i] = std::thread(func, std::ref(pool), std::ref(partition[i]));
    };
    int num_line = 0;
    while (true) {
        char *line = pool.fetch_avail();
        if (!fgets(line, MAX_LEN - 1, file)) break;

        num_line += 1;
        if (num_line % 100000 == 0) cout << num_line << endl;
        if (num_line == 1) {
            char header[MAX_LEN];
            strcpy(header, line);
            df->parse_header(header, factory);

            for (int i = 0; i < NT; ++i) {
                strcpy(header, line);
                partition[i].parse_header(header, factory);
            }
        }
        else {
            if (nrow > 0 && num_line > nrow) break;
//            cout<<"PUT"<<endl;
        }
        pool.put_used(line);
    }
    for (int i = 0; i < NT; ++i) {
        pool.put_used(0);
    }
    for (int i = 0; i < NT; ++i) {
        threads[i].join();
    }
    df->length = num_line - 1;
    return df;

}

DataFrame *DataFrame::load(const char *path)
{
    return 0;
}

void DataFrame::parse_line(char *line, char sep)
{
    size_t len = strlen(line);
    char *st = line;
    char *ed = line + len;
    *(ed - 1) = sep;
    int index = 0;
    while (st < ed) {
        char *next = find(st, ed, sep);
        *next = 0;
        data[index++]->parse(st);
        st = next + 1;
    }
}
void DataFrame::parse_header(char *header, unordered_map<string, BaseSeriesFactory> &factory, char sep)
{
    size_t len = strlen(header);
    char *st = header;
    char *ed = header + len;
    *(ed - 1) = sep;
    int index = 0;
    while (st < ed) {
        char *next = find(st, ed, sep);
        *next = 0;
        string name(st);
        this->columns[name] = index;
        if (factory.find(name) == factory.end()) {
            throw logic_error("Col " + name + " not configured");
        }
        Series *series = factory.find(name)->second.new_series(name);
        assert(series != 0);
        this->data.push_back(shared_ptr<Series>(series));

        ++index;
        st = next + 1;
    }
    cout << "H done" << endl;
}

void DataFrame::dump(const char *path)
{

}

void DataFrame::info()
{
    for (shared_ptr<Series> series : data) {
        if (series) {
            cout << series->getName() << endl;
            series->output();
        }
    }

}
