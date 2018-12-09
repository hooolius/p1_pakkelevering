#include "address_to_point_calc.h"

void addresses_to_point_calc(struct address searches[], struct point map_points[]) {
    double difference = 0;
    int points = 30000;
    int number_of_searches = 30;
    double lat_difference;
    double lon_difference;

    for (int i = 0; i < points; ++i) {
        for (int j = 0; j < number_of_searches; ++j) {
            lat_difference = map_points[i].lat - searches[j].lat;
            if (lat_difference < 0) {
                lat_difference = lat_difference * (-1);
            }
            lon_difference = map_points[i].lon - searches[j].lon;
            if (lon_difference < 0) {
                lon_difference = lon_difference * (-1);
            }
            if (searches[j].closest_point == 0) {
                searches[j].closest_point_dist = difference;
                searches[j].closest_point = i;
            } else if (lat_difference + lon_difference < searches[j].closest_point_dist) {
                searches[j].closest_point_dist = difference;
                searches[j].closest_point = i;
            }
        }
    }
}