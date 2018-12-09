//
// Created by alexandern on 07/12/18.
//

#include "addresses_prompt.h"
#include "parser_addresses.h"
#include "map_parser.h"


int main(void) {
    struct address *searches;
    struct point *map_points;


    addresses_prompt(searches);
    map_parser(map_points);

    return 1;
}