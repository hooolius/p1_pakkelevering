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

void pointer_writer(struct point points_array[], int j, int j_old);

int is_written(struct point point, int j, int j_old);

int main(void) {
    cJSON *json = NULL;
    struct point *points_array;
    int i = 0;
    long len;
    char *data = NULL;
    FILE *paddress_file;
    paddress_file = fopen("map_data.json", "rb");


    if (paddress_file == NULL) {
        printf("SHIT");
        exit(-1);
    }
    fseek(paddress_file, 0, SEEK_END);
    len = ftell(paddress_file);
    fseek(paddress_file, 0, SEEK_SET);


    data = (char *) malloc(len + 1);
    fread(data, 1, len, paddress_file);


    json = cJSON_Parse(data);

    if (json == NULL) {
        printf("Error before: [%s]\n", cJSON_GetErrorPtr());
        exit(-1);
    } else {

        /*Counts the amount of points within the file*/
        i = points_counter(json);
        points_array = calloc(i, sizeof(points_array[0]));

        search_and_parse_points(data, points_array);

        printf("Points array: %lf", points_array[0].id);
        search_and_parse_streets(data, points_array);
    }

}


void search_and_parse_points(char data[], struct point points_array[]) {
    cJSON *json = NULL;
    const cJSON *points = NULL;
    const cJSON *point = NULL;
    json = cJSON_Parse(data);

    int i = 0, j = 0;

    points = cJSON_GetObjectItemCaseSensitive(json, "points");
    i = points_counter(json);

    cJSON_ArrayForEach(point, points) { ;
        points_array[j].id = cJSON_GetObjectItemCaseSensitive(point, "id")->valuedouble;
        points_array[j].lat = cJSON_GetObjectItemCaseSensitive(point, "lat")->valuedouble;
        points_array[j].lon = cJSON_GetObjectItemCaseSensitive(point, "lon")->valuedouble;
        j++;
    }
    qsort(points_array, i, sizeof(points_array[0]), sorter_function);

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


void search_and_parse_streets(char *data, struct point points_array[]) {
    cJSON *json = NULL;
    const cJSON *road_points = NULL;
    const cJSON *road_point = NULL;
    const cJSON *roads = NULL;
    const cJSON *road = NULL;
    int array_len = 0, j = 0, j_old = 0;
    double input;

    json = cJSON_Parse(data);

    if (json == NULL) {
        printf("Error before: [%s]\n", cJSON_GetErrorPtr());

    } else {
        array_len = points_counter(json);
        roads = cJSON_GetObjectItemCaseSensitive(json, "roads");
        cJSON_ArrayForEach(road, roads) {

            road_points = cJSON_GetObjectItemCaseSensitive(road, "nodes");
            //array_len = cJSON_GetArraySize(road_point);
            cJSON_ArrayForEach(road_point, road_points) {

                input = road_point->valuedouble;
                j = binary_searcher(input, points_array, array_len);
                if (j_old !=0) {
                    pointer_writer(points_array, j, j_old);
                    printf("\t Test of return  ID:: %d Array key: %lf \nJ_Old: %d", j, input, j_old);
                    printf("\n P1: %d \n P2: %d \n P3: %d \n P4: %d \n P5: %d \n", points_array[j].p1, points_array[j].p2,
                           points_array[j].p3, points_array[j].p4, points_array[j].p5);
                }
                j_old = j;

            }

            j_old = 0;
            printf("End of section \n");
        }
    }
}

void pointer_writer(struct point points_array[], int j, int j_old) {
    if (!is_written(points_array[j], j, j_old)) {
        if (points_array[j].p1 == 0) {
            points_array[j].p1 = j;

        } else if (points_array[j].p2 == 0) {
            points_array[j].p2 = j;

        } else if (points_array[j].p3 == 0) {
            points_array[j].p3 = j;

        } else if (points_array[j].p4 == 0) {
            points_array[j].p4 = j;

        } else if (points_array[j].p5 == 0) {
            points_array[j].p5 = j;

        } else if (points_array[j].p6 == 0) {
            points_array[j].p6 = j;
        }

        if (j_old != 0) {
            if (points_array[j_old].p1 == 0) {
                points_array[j_old].p1 = j;

            } else if (points_array[j_old].p2 == 0) {
                points_array[j_old].p2 = j;

            } else if (points_array[j_old].p3 == 0) {
                points_array[j_old].p3 = j;

            } else if (points_array[j_old].p4 == 0) {
                points_array[j_old].p4 = j;

            } else if (points_array[j_old].p5 == 0) {
                points_array[j_old].p5 = j;

            } else if (points_array[j_old].p6 == 0) {
                points_array[j_old].p6 = j;
            }

            if (points_array[j].p1 == 0) {
                points_array[j].p1 = j_old;

            } else if (points_array[j].p2 == 0) {
                points_array[j].p2 = j_old;

            } else if (points_array[j].p3 == 0) {
                points_array[j].p3 = j_old;

            } else if (points_array[j].p4 == 0) {
                points_array[j].p4 = j_old;

            } else if (points_array[j].p5 == 0) {
                points_array[j].p5 = j_old;

            } else if (points_array[j].p6 == 0) {
                points_array[j].p6 = j_old;
            }
        }
    }
}

int is_written(struct point point, int j, int j_old) {
    if (point.p1 == j) {
        return 1;
    } else if (point.p2 == j) {
        return 1;
    } else if (point.p3 == j) {
        return 1;
    } else if (point.p4 == j) {
        return 1;
    } else if (point.p5 == j) {
        return 1;
    } else if (point.p6 == j) {
        return 1;
    }

    if (point.p1 == j_old) {
        return 1;
    } else if (point.p2 == j_old) {
        return 1;
    } else if (point.p3 == j_old) {
        return 1;
    } else if (point.p4 == j_old) {
        return 1;
    } else if (point.p5 == j_old) {
        return 1;
    } else if (point.p6 == j_old) {
        return 1;
    }
    return 0;
}

int binary_searcher(double input, struct point points_array[], int array_len) {
    int first;
    int middle;

    first = 0;
    middle = (first + array_len) / 2;

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
