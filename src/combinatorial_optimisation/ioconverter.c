#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <parser_addresses.h>
#include "ioconverter.h"

node *convert_points_to_nodes(int number_of_points, point *points);
node *convert_point_to_node(point *the_point);
int **astar_to_matrix_converter(dyn_array_address *searches, struct point *map_points) {

/*count number of searches */
  int number_of_points = points_counter();
  int number_of_address = searches->items; 

/*calloc two dim array of pointer  */
  int **afstand_matrix = (int **) calloc(number_of_address, sizeof(int *)); 
  for (int y = 0; y < number_of_address; ++y) {
    afstand_matrix[y] = (int *) calloc(number_of_address, sizeof(int));
  }
  if (afstand_matrix == NULL) {
    printf("Error! memory not allocated.");
    exit(-1);
  }
  node *nodes = convert_points_to_nodes(number_of_points, map_points);
  for (int i = 0; i < number_of_address; ++i) {
    for (int j = 0; j < number_of_address; ++j) {
      if (i == j) {
        afstand_matrix[i][j] = 0;
        afstand_matrix[j][i] = 0;
      }
      else {
        if (afstand_matrix[i][j] == 0 || afstand_matrix[j][i] == 0) {
          node *start = convert_point_to_node(&map_points[searches->addresses[i].closest_point]);
          node *goal = convert_point_to_node(&map_points[searches->addresses[j].closest_point]);
          double star = a_star(start, goal, nodes, number_of_points);
          afstand_matrix[i][j] = (int) round(star);
          afstand_matrix[j][i] = (int) round(star);
          free(start);
          free(goal);
        }
      }
    }
  }
  free(map_points);
  free(nodes);
  return afstand_matrix;
}

node *convert_points_to_nodes(int number_of_points, point *points) {
  node *nodes = calloc(number_of_points, sizeof(struct node));
  for (int i = 0; i < number_of_points; ++i) {
    nodes[i].id = points[i].id;
    nodes[i].lon = points[i].lon;
    nodes[i].lat = points[i].lat;
    nodes[i].is_active = 0;
    nodes[i].g = 0;
    nodes[i].h = 0;
    nodes[i].f = 0;
    nodes[i].p1 = points[i].p1;
    nodes[i].p2 = points[i].p2;
    nodes[i].p3 = points[i].p3;
    nodes[i].p4 = points[i].p4;
    nodes[i].p5 = points[i].p5;
    nodes[i].p6 = points[i].p6;
    nodes[i].p7 = points[i].p7;
    nodes[i].p8 = points[i].p8;
  }
  return nodes;
}

node *convert_point_to_node(point *point) {
  node *node = calloc(1, sizeof(struct node));
  node->id = point->id;
  node->lon = point->lon;
  node->lat = point->lat;
  node->is_active = 0;
  node->g = 0;
  node->h = 0;
  node->f = 0;
  node->p1 = point->p1;
  node->p2 = point->p2;
  node->p3 = point->p3;
  node->p4 = point->p4;
  node->p5 = point->p5;
  node->p6 = point->p6;
  node->p7 = point->p7;
  node->p8 = point->p8;
  return node;
}