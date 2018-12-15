#include <dynamic_array.h>
#include "address_to_point_calc.h"

void addresses_to_point_calc(dyn_array_address *searches, struct point *map_points) {
    double difference = 0;
    int points;
    double lat_difference;
    double lon_difference;

    points = points_counter();

    for (int i = 0; i < points; ++i) {
        for (int j = 0; j < searches->items; ++j) {
            lat_difference = map_points[i].lat - searches->addresses[j].lat;

            if (lat_difference < 0) {
                lat_difference = lat_difference * (-1);
            }

            lon_difference = map_points[i].lon - searches->addresses[j].lon;

            if (lon_difference < 0) {
                lon_difference = lon_difference * (-1);
            }

            difference = lat_difference + lon_difference;

            if (searches->addresses[j].closest_point == 0) {
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