#include "DataFrame.h"
#include <cstdio>
#include <algorithm>
#include <exception>
#include <iostream>

using namespace cdata;
using namespace std;

DataFrame *DataFrame::read_csv(const char *path, int nrow)
{
    const size_t MAX_LEN = 1024;
    FILE *file = fopen(path, "r");
    if (!file) {
        throw runtime_error("Can't open " + string(path));
    }

    DataFrame *df = new DataFrame();

    char line[MAX_LEN + 1];
    int num_line = 0;
    while (std::fgets(line, sizeof line, file) != NULL) {
        num_line += 1;
        if(num_line%1==1000000) cout<<num_line<<endl;
        if (num_line == 1) {
            df->parse_header(line);
        }
        else {
            if (nrow > 0 && num_line > nrow) break;
            df->parse_line(line);
        }

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
    int index = 0;
    while (st < ed) {
        char *next = find(st, ed, sep);
        if (next == 0) next = ed;
        *next = 0;
        data[index++]->parse(st);
        st = next + 1;
    }
}
void DataFrame::parse_header(char *header, char sep)
{
    size_t len = strlen(header);
    char *st = header;
    char *ed = header + len;
    int index = 0;
    while (st < ed) {
        char *next = find(st, ed, sep);
        if (next == 0) next = ed;
        *next = 0;
        string name(st);
        this->columns[name] = index;
        Series *series = Series::newSeries(name[0], name);
        this->data.push_back(shared_ptr<Series>(series));

        ++index;
        st = next + 1;
    }
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
