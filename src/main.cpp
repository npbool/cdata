//
// Created by npbool on 16-4-21.
//

#include "DataFrame.h"
#include "Series.h"
#include <unordered_map>
#include <ctime>
using namespace cdata;
int main(int argc, char *argv[])
{

    BaseSeriesFactory D = SeriesFactory<DatetimeSeries>();
    BaseSeriesFactory C = SeriesFactory<CategoricalSeries>();
    BaseSeriesFactory F = SeriesFactory<FloatSeries>();
    BaseSeriesFactory S = SeriesFactory<StringSeries>();

    unordered_map<string, BaseSeriesFactory> factory = {
        {"date_time", D},
        {"site_name", C},
        {"posa_continent", C},
        {"user_location_country", C},
        {"user_location_region", C},
        {"user_location_city", C},
        {"orig_destination_distance", F},
        {"user_id", C},
        {"is_mobile", C},
        {"is_package", C},
        {"channel", C},
        {"srch_ci", D},
        {"srch_co", D},
        {"srch_adults_cnt", C},
        {"srch_children_cnt", C},
        {"srch_rm_cnt", C},
        {"srch_destination_id", C},
        {"srch_destination_type_id", C},
        {"is_booking", C},
        {"cnt", C},
        {"hotel_continent", C},
        {"hotel_country", C},
        {"hotel_market", C},
        {"hotel_cluster", C},
    };

    cout << "A" << endl;
    time_t ct = time(0);
    DataFrame *df = DataFrame::read_csv(argv[1], factory);
    time_t et = time(0);
    cout<<"used "<<et-ct<<endl;

    cout << "B" << endl;
//    df->info();
//
//    df->select<CategoricalSeries>("c_user_location_region", [](int rgn)
//    { return rgn == 348; });
//    df->select<CategoricalSeries, FloatSeries>("c_is_package", "f_srch_destination_id",
//                                               [](int rgn, float dist)
//                                               {
//                                                   return rgn && dist < 10000;
//                                               });
}
