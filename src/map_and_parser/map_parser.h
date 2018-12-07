//
// Created by alexandern on 07/12/18.
//

#ifndef MAP_AND_PARSER_PARSERS_H
#define MAP_AND_PARSER_PARSERS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cJSON.c"
#include "cJSON.h"

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
};

void search_and_parse_points(char data[], struct point *points_array);

int sorter_function(const void *a, const void *b);

void search_and_parse_streets(char *data, struct point points_array[]);

int binary_searcher(double input, struct point points_array[], int array_len);

int points_counter(cJSON *pJSON);

void pointer_writer(struct point points_array[], int array_key, int old_array_key);

int is_written(struct point point, int array_key, int old_array_key);


#endif //MAP_AND_PARSER_PARSERS_H
