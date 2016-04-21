#ifndef CDATA_DATAFRAME_H
#define CDATA_DATAFRAME_H

#include <cstdio>
#include <cstring>
#include <unordered_map>
#include <unordered_set>
#include <memory>
#include <vector>
#include <functional>

#include "Series.h"


namespace cdata
{

using namespace std;


class DataFrame
{
public:
    static DataFrame *read_csv(const char *path, int nrow=-1);
    static DataFrame *load(const char *path);

    void dump(const char *path);

    void info();


    void drop_column(const string col){
        int index = columns[col];
        columns.erase(col);
        data[index] = 0;
    }
    shared_ptr<Series> get_series(const string& col){
        return data[columns[col]];
    }
    shared_ptr<Series> operator[](const string& col){
        return get_series(col);
    }
    size_t get_length(){
        return length;
    }
    template<class ST>
    void select(const string col, function<bool(typename ST::VT)> test){
        shared_ptr<ST> series = dynamic_pointer_cast<ST>(get_series(col));
        for(int i=0;i<get_length();++i){
            test(series->val(i));
        }
    }

    template<class ST1, class ST2>
        void select(const string col1, const string col2, function<bool(typename ST1::VT, typename ST2::VT)> test){
        shared_ptr<ST1> series1 = dynamic_pointer_cast<ST1>(get_series(col1));
        shared_ptr<ST2> series2 = dynamic_pointer_cast<ST2>(get_series(col2));
        for(int i=0;i<get_length();++i){
            test(series1->val(i), series2->val(i));
        }
    };


private:
    unordered_map<string, int> columns;
    vector<shared_ptr<Series>> data;

    void parse_header(char *, char sep = ',');
    void parse_line(char *, char sep = ',');
    size_t length;
};

}

#endif
