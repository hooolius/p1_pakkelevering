#ifndef MAP_AND_PARSER_PARSERS_H
#define MAP_AND_PARSER_PARSERS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


struct point {
    double id;
    double lon;
    double lat;
    int p1;
    int p2;
    int p3;
    int p4;
    int p5;
    int p6;
    int p7;
    int p8;
};


void map_parser(struct point *map_points);

int points_counter();



#endif //MAP_AND_PARSER_PARSERS_H
