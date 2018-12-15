#include <stdio.h>
#include <stdlib.h>
#include "main_config.h"
#include "libs/dynamic_array.h"
#include "pathfinding/a_star.h"
#include "map_gen/addresses_prompt.h"
#include "map_gen/parser_addresses.h"
#include "map_gen/map_parser.h"
#include "map_gen/address_to_point_calc.h"
#include "combinatorial_optimisation/held_karp.h"
#include "combinatorial_optimisation/ioconverter.h"
typedef struct point point;


main(int argc, char *argv[]) {

  printf("%s", argv[0]);
  dyn_array_address *searches = make_dyn_array_a(2);
  point *map_points;
  map_points = calloc(points_counter(), sizeof(point));

  addresses_prompt(searches);
  map_parser(map_points);
  addresses_to_point_calc(searches, map_points);
  printf("Size: %d",searches->items);

  printf("Version %d.%d \n",
      p1_pakkelevering_VERSION_MAJOR, p1_pakkelevering_VERSION_MINOR);

  int **matrix = astar_to_matrix_converter(searches, map_points);

  int *min_cost = 0;
  int plan[searches->items];

  held_karp(matrix, searches->items, 0, min_cost, plan);
  printf("min cost: %d", *min_cost);
  for (int i = 0; i < searches->items; i++) {
    printf("%d, ", plan[i]);
  }
  return 0;
}