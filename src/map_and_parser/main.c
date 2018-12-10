//
// Created by alexandern on 07/12/18.
//

#include "addresses_prompt.h"
#include "parser_addresses.h"
#include "map_parser.h"
#include "address_to_point_calc.h"


int main(void) {
    struct address *searches;
    struct point *map_points;
    struct address *addresses;


    addresses_prompt(searches,addresses);
    printf("Searches  %s",searches[0].tags.country);
    //printf("Error yet?");
    //map_parser(map_points);
    //printf("Error yet? 2");
  //  addresses_to_point_calc(searches,map_points);

    return 1;
}