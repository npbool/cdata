//
// Created by npbool on 16-4-21.
//

#include "DataFrame.h"

using namespace cdata;
int main(int argc, char *argv[])
{
    cout<<"A"<<endl;
    DataFrame *df = DataFrame::read_csv(argv[1]);
    cout<<"B"<<endl;
//    df->info();

    df->select<CategoricalSeries>("c_user_location_region", [](int rgn)
    { return rgn == 348; });
    df->select<CategoricalSeries, FloatSeries>("c_is_package", "f_srch_destination_id",
                                               [](int rgn, float dist)
                                               {
                                                   return rgn && dist < 10000;
                                               });
}
