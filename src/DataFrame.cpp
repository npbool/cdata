#include "DataFrame.cpp"
#include <cstdio>
#include <algorithm>
using namespace cdata;

DataFrame DataFrame::read_csv(const char* path, header=false){
    const size_t MAX_LEN = 1024;
    FILE* file = fopen(path);
    if(!file){
        throw "Fail to open"
    }

    DataFrame df;

    char line[MAX_LEN+1];
    int num_line = 0;
    while(std::fgets(buf, sizeof buf, file) != NULL){
        df.parse_line(buf);
        num_line += 1;
        if(num_line==1){
            df.parse_header(buf);
        }
    }
}

DataFrame DataFrame::load(const char* path);

void DataFrame::parse_line(const char* line) {

}
void DataFrame::parse_header(const char* header, char sep=','){
    size_t len = strlen(header);
    char* st = header;
    char* ed = header+len;
    int index = 0;
    while((int pos = find(st, ed, sep)) != ed){
        string col_name(st, pos-st);
        this->columns[col_name] = index++;

        st = header + pos + 1;
    }
}

void DataFrame::dump(const char* path){

}
