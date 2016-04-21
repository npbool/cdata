#include "Series.h"
#include <exception>
namespace cdata
{
Series *Series::newSeries(char typecode, string name)
{
    switch (typecode) {
        case 'c':
            return new CategoricalSeries(name);
        case 'f':
            return new FloatSeries(name);
        case 'd':
            return new DatetimeSeries(name);
        case 's':
            return new StringSeries(name);
        default:
            throw std::invalid_argument(name);
    }
}
}

