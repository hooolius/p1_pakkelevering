#include <stdio.h>
#include <stdlib.h>
#include "../map_gen/map_parser.h"
#include "convert_distance_from_points.h"

struct node{
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
};

typedef struct point point;
typedef struct node node;

#include "../dynamic_array.h"
//#include "pairing_heap.h"

#define SOME_VALUE 10

node *a_star(struct point *start_p, struct point *goal_p, struct point *points);

node *convert_point_to_node(int number_of_points, point *points);

int count_elements_in_list(dyn_array_node *list);

/* Function copys one node to a other node */
void copy_node_to_node(node destination, node source);

node *find_min_array(dyn_array_node *list);

node *reconstruct_path(dyn_array_node *came_from);

dyn_array_node *make_neighbours_list(node current, node *nodes);

int contains(dyn_array_node *closed_list, node item);

int cmp_func(const void *a, const void *b);
