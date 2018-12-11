#include <stdio.h>
#include <stdlib.h>
#include "libs/convert_distance_from_points.h"

/*struct node{
  int id;
  double lat;
  double lon;
  double g;
  double h;
  double f;
  int is_active;
  int p1;
  int p2;
  int p3;
  int p4;
  int p5;
  int p6;
};*/

/*struct point {
    double id;
    double lon;
    double lat;
    int p1;
    int p2;
    int p3;
    int p4;
    int p5;
    int p6;
};*/

//typedef struct point point;
//typedef struct node node;

//#include "pairing_heap.h"
//#include "dynamic_array.h"

#define SOME_VALUE 10

#include "map_gen/map_parser.h"
node *a_star(struct point start_p, struct point goal_p, struct point *points);
