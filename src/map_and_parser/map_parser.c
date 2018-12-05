#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cJSON.c"
#include "cJSON.h"

struct point {
    double id;
    double lon;
    double lat;
    struct point *p1;
    struct point *p2;
    struct point *p3;
    struct point *p4;
    struct point *p5;
    struct point *p6;
};


void nodes_parser(struct point *points_array);

void search_and_parse(char data[], struct point *points_array);

int sorter_function(const void *a, const void *b);

void streets_parser(struct point *points_array);

void search_and_parse_streets(char *data, struct point *points_array);

int binary_searcher(double input, struct point points_array[], int array_len);

int points_counter(cJSON *pJSON);

int main(void) {
    struct point *points_array;
    nodes_parser(points_array);
    streets_parser(points_array);
}

void nodes_parser(struct point *points_array) {
    long len;
    char *data = NULL;
    FILE *paddress_file;
    paddress_file = fopen("map_data.json", "rb");
    /* get the length */
    if (paddress_file == NULL) {
        printf("SHIT");
        exit(-1);
    }
    fseek(paddress_file, 0, SEEK_END);
    len = ftell(paddress_file);
    fseek(paddress_file, 0, SEEK_SET);


    data = (char *) malloc(len + 1);
    fread(data, 1, len, paddress_file);
    search_and_parse(data, points_array);
}

void search_and_parse(char data[], struct point *points_array) {
    cJSON *json = NULL;
    const cJSON *points = NULL;
    const cJSON *point = NULL;

    int i = 0, j = 0;

    json = cJSON_Parse(data);

    if (json == NULL) {
        printf("Error before: [%s]\n", cJSON_GetErrorPtr());

    } else {
        points = cJSON_GetObjectItemCaseSensitive(json, "points");
        /*Counts the amount of points within the file*/
        i = points_counter(json);
        points_array = calloc(i, sizeof(points_array[0]));

        cJSON_ArrayForEach(point, points) { ;
            points_array[j].id = cJSON_GetObjectItemCaseSensitive(point, "id")->valuedouble;
            points_array[j].lat = cJSON_GetObjectItemCaseSensitive(point, "lat")->valuedouble;
            points_array[j].lon = cJSON_GetObjectItemCaseSensitive(point, "lon")->valuedouble;
            j++;
        }
        qsort(points_array, i, sizeof(points_array[0]), sorter_function);
    }
}

int points_counter(cJSON *pJSON) {
    const cJSON *points = NULL;
    const cJSON *point = NULL;
    int i;
    points = cJSON_GetObjectItemCaseSensitive(pJSON, "points");
    cJSON_ArrayForEach(point, points) {
        i++;
    }
    return i;
}

int sorter_function(const void *a, const void *b) {
    struct point *ia = (struct point *) a;
    struct point *ib = (struct point *) b;
    if (ia->id > ib->id) {
        return 1;
    } else if (ia->id < ib->id) {
        return -1;
    }
    return 0;

}

void streets_parser(struct point *points_array) {
    long len;
    char *data = NULL;
    FILE *paddress_file;
    paddress_file = fopen("map_data.json", "rb");
    /* get the length */
    if (paddress_file == NULL) {
        printf("SHIT");
        exit(-1);
    }
    fseek(paddress_file, 0, SEEK_END);
    len = ftell(paddress_file);
    fseek(paddress_file, 0, SEEK_SET);


    data = (char *) malloc(len + 1);
    fread(data, 1, len, paddress_file);
    search_and_parse_streets(data, points_array);
}

void search_and_parse_streets(char *data, struct point *points_array) {
    cJSON *json = NULL;
    const cJSON *road_points = NULL;
    const cJSON *road_point = NULL;
    const cJSON *roads = NULL;
    const cJSON *road = NULL;
    int i = 0;
    double input;
    double test,j=0;

    json = cJSON_Parse(data);

    if (json == NULL) {
        printf("Error before: [%s]\n", cJSON_GetErrorPtr());

    } else {
        i = points_counter(json);
        roads = cJSON_GetObjectItemCaseSensitive(json, "roads");
        cJSON_ArrayForEach(road, roads) {

            road_points = cJSON_GetObjectItemCaseSensitive(road, "nodes");
            //i = cJSON_GetArraySize(road_point);
            cJSON_ArrayForEach(road_point, road_points) {

                input = road_point->valuedouble;
                printf("%.0lf \n",input);

                //printf("Test of return : %lf \n", j);
               // j = binary_searcher(input, points_array, i);

            }
            printf("End of section \n");
        }
    }
}

int binary_searcher(double input, struct point points_array[], int array_len) {
    int first;
    int middle;

    while (input <= points_array[array_len - 1].id) {

        first = 0;
        middle = (first + array_len - 1) / 2;

        while (first <= array_len) {
            if (points_array[middle].id < input) {
                first = middle + 1;
            } else if (points_array[middle].id == input) {
                return middle;
            } else {
                array_len = middle - 1;
            }
            middle = (first + array_len) / 2;
        }
    }
}
