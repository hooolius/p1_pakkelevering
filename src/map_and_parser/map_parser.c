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


void nodes_parser();

void search_and_parse(char data[]);

int sorter_function(const void *a, const void *b);

void streets_parser();

int main(void) {
    nodes_parser();
    streets_parser();
}

void nodes_parser() {
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
    search_and_parse(data);
}

void search_and_parse(char data[]) {
    cJSON *json = NULL;
    const cJSON *points = NULL;
    const cJSON *point = NULL;
    struct point *points_array;
    int i = 0, j = 0;

    json = cJSON_Parse(data);

    if (json == NULL) {
        printf("Error before: [%s]\n", cJSON_GetErrorPtr());

    } else {
        points = cJSON_GetObjectItemCaseSensitive(json, "points");
        /*Counts the amount of points within the file*/
        cJSON_ArrayForEach(point, points) {
            i++;
        }
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

void streets_parser() {

}
