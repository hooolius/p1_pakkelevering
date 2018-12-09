//
// Created by alexandern on 07/12/18.
//

#ifndef MAP_AND_PARSER_PARSER_ADDRESSES_C_H
#define MAP_AND_PARSER_PARSER_ADDRESSES_C_H
#include "cJSON.c"
#include "cJSON.h"

struct tags {
    char city[30];
    char street[30];
    char country[5];
    char house_number[5];
    char muncipality[20];
    char postcode[4];
};

struct address {
    int id;
    double lat;
    double lon;
    int closest_point;
    double closest_point_dist;
    struct tags tags;

} address;

void parser_addreses(struct address searches[]);

int is_in_array(char input_streetname[], char input_housenumber[], struct address searches[]);

void convert_to_array(char *text, struct address searches[]);

#endif //MAP_AND_PARSER_PARSER_ADDRESSES_C_H
