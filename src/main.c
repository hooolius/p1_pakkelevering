#include <stdio.h>
#include <stdlib.h>
#include "main_config.h"
#include "libs/dynamic_array.h"
#include "libs/cleaner.h"
#include "pathfinding/a_star.h"
#include "map_gen/addresses_prompt.h"
#include "map_gen/parser_addresses.h"
#include "map_gen/map_parser.h"
#include "map_gen/address_to_point_calc.h"
#include "combinatorial_optimisation/held_karp.h"
#include "combinatorial_optimisation/ioconverter.h"
#include <time.h>
typedef struct point point;


int main(int argc, char *argv[]) {


  clock_t start_map, end_map;
  clock_t start_a, end_a;
  clock_t start_held, end_held;
  double cpu_time_used;

  dyn_array_address *searches = make_dyn_array_a(2);
  point *map_points;
  map_points = calloc(points_counter(), sizeof(point));

  addresses_prompt(searches);
  start_map =clock();
  printf("Map parsed started \n");
  map_parser(map_points);
  addresses_to_point_calc(searches, map_points);
  end_map = clock();
  printf("Map and addresses parsed time %f \n",(double )(start_map-end_map/CLOCKS_PER_SEC));

  printf("Version %d.%d \n",
      p1_pakkelevering_VERSION_MAJOR, p1_pakkelevering_VERSION_MINOR);

  printf("A* started \n");
  start_a = clock();
  int **matrix = astar_to_matrix_converter(searches, map_points);
  end_a = clock();
  printf("All A* done, time: %f \n",(double ) (start_a-end_a/CLOCKS_PER_SEC));
  free(map_points);
  int min_cost = 0;
  int plan[searches->items+1];

  printf("Held karp started \n");
  start_held = clock();
  min_cost = held_karp(matrix, searches->items, 0, plan);
  end_held = clock();
  printf("Held karp done, time: %f \n",(double) (start_held-end_held/CLOCKS_PER_SEC));
  printf("min cost: %d \n", min_cost);
  for (int i = 0; i < searches->items+1; i++) {
    printf("%d: %s %s \n", i, searches->addresses[plan[i]].tags.street, searches->addresses[plan[i]].tags.house_number);
  }
  free(searches);
  freeArray(matrix,searches->items);
  free(matrix);

  printf("\n");
  return 0;
}