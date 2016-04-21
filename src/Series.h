//
// Created by npbool on 16-4-21.
//

#ifndef CDATA_SERIES_H
#define CDATA_SERIES_H

#include <vector>
#include <string>
#include <iostream>
#include <limits>
#include <cmath>
namespace cdata
{

using namespace std;

class CategoricalSeries;
class FloatSeries;

class Series
{
public:
    virtual bool isCategorical() = 0;
    virtual bool isNumerical() = 0;
    virtual void parse(const char *str) = 0;

    static Series *newSeries(char typecode, string name);

    Series(const string &name)
        : name(name)
    { }
    string getName()
    { return name; }
    virtual void output(ostream &os = std::cout) = 0;

private:
    string name;
};

class CategoricalSeries: public Series
{
public:
    typedef int VT;
    const VT nan = numeric_limits<VT>::min();

    CategoricalSeries(const string &name)
        : Series(name)
    { }

    VT val(int index){
        return data[index];
    }
    virtual bool isCategorical() override
    {
        return true;
    }

    virtual bool isNumerical() override
    {
        return false;
    }

    virtual void parse(const char *str) override
    {
        if (*str == 0) {
            data.push_back(nan);
        }
        else {
            data.push_back(atoi(str));
        }
    }
    virtual void output(ostream &os) override
    {
        for (int d : data) {
            if(d==nan){
                os<<"nan"<<' ';
            } else {
                os << d << ' ';
            }
        }
        os << endl;
    }

private:
    vector<int> data;
};

class FloatSeries: public Series
{
public:
    typedef float VT;
    const VT nan = numeric_limits<float>::quiet_NaN();

    VT val(int index){
        return data[index];
    }

    virtual bool isCategorical() override
    {
        return false;
    }
    virtual bool isNumerical() override
    {
        return true;
    }
    virtual void parse(const char *str) override
    {
        if (*str == 0) {
            data.push_back(nan);
        }
        else {
            data.push_back(atof(str));
        }
    }
    FloatSeries(const string &name)
        : Series(name)
    { }

    virtual void output(ostream &os) override
    {
        for (float f : data) {
            if (isnan(f)) os << "nan" << ' ';
            else
                os << f << ' ';
        }
        os << endl;
    }

private:
    vector<float> data;
};

class StringSeries: public Series
{
public:
    typedef string VT;
    StringSeries(const string &name)
        : Series(name)
    { }
    virtual void parse(const char *str) override
    {
        data.push_back(str);
    }

    virtual bool isCategorical() override
    {
        return false;
    }

    virtual bool isNumerical() override
    {
        return false;
    }
    virtual void output(ostream &os) override
    {
        for(string str:data){
            cout<<str<<" "<<endl;
        }
        cout<<endl;
    }
private:
    vector<string> data;
};

class DatetimeSeries : public Series{
public:
    virtual bool isCategorical() override
    {
        return false;
    }
    virtual bool isNumerical() override
    {
        return false;
    }
    virtual void parse(const char *str) override
    {

    }
    virtual void output(ostream &os) override
    {

    }
    DatetimeSeries(const string &name)
        : Series(name)
    { }
};
}


#endif //CDATA_SERIES_H
