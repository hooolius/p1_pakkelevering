#include <dynamic_array.h>
#include "address_to_point_calc.h"

/**
*@param[in] "dyn_array_address *searches" Contains the adresses the user has given
*@param[in] "point *map_points" Contains all the map data
*/
void addresses_to_point_calc(dyn_array_address *searches, struct point *map_points) {
    double lat_difference = 0;
    double lon_difference = 0;
    double difference = 0;
    int points;


    points = points_counter();

    for (int i = 1; i < points; ++i) {
        for (int j = 0; j < searches->items; ++j) {

            lat_difference = map_points[i].lat - searches->addresses[j].lat;
            lon_difference = map_points[i].lon - searches->addresses[j].lon;

            difference = sqrt(pow(lat_difference,2)+pow(lon_difference,2));

            if (searches->addresses[j].closest_point <= 0) {
                searches->addresses[j].closest_point_dist = difference;
                searches->addresses[j].closest_point = i;
            }
            else if (difference < searches->addresses[j].closest_point_dist) {
                searches->addresses[j].closest_point_dist = difference;
                searches->addresses[j].closest_point = i;
            }
        }
    }
}