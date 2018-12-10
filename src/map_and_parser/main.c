#include "addresses_prompt.h"
#include "parser_addresses.h"
#include "map_parser.h"
#include "address_to_point_calc.h"


int main(void) {
    struct address *searches;
    struct point *map_points;

    searches = calloc(20, sizeof(struct address));
    map_points = calloc(points_counter(), sizeof(struct point));


    addresses_prompt(searches);
    map_parser(map_points);
    addresses_to_point_calc(searches,map_points);

    printf("Testing: %lf",searches[0].closest_point_dist);


    return 1;
}