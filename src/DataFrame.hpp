#include <cstdio>
#include <cstring>
#include <unordered_map>
#include <unordered_set>
#include <memory>
namespace cdata {

class Series {
public:
    bool isCategorical() = 0;
    bool isNumerical() = 0;
protected:
    string name;
};

class CategoricalSeries: public Series {
public:
    typedef int V;
private:
    vector<int> data;
};

class StrSeries: public Series {

};

class NumericalSeries: public Series {
public:
    typedef float V;
private:
    vector<float> data;
};

class DataFrame{
public:
    static DataFrame read_csv(const char* path);
    static DataFrame load(const char* path);

    void dump(const char* path);

private:
    unordered_map<string, int> columns;
    vector<Series*> data;

    void parse_header(const char*);
    void parse_line(const char*)
};

}
