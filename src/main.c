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
  struct address *searches = calloc(2, sizeof(struct address));
  point *map_points;
  map_points = calloc(points_counter(), sizeof(point));

  addresses_prompt(searches);
  map_parser(map_points);
  addresses_to_point_calc(searches, map_points);
  printf("Size: %ld",sizeof(searches)/ sizeof(struct address));

  printf("Version %d.%d \n",
      p1_pakkelevering_VERSION_MAJOR, p1_pakkelevering_VERSION_MINOR);

  point start = map_points[searches[0].closest_point];
  point slut = map_points[searches[1].closest_point];

  int **matrix = astar_to_matrix_converter(searches, map_points);

  int *min_cost = 0;
  int plan[count_addresses(searches)];

  held_karp(matrix, count_addresses(searches), 0, min_cost, plan);
  printf("min cost: %d", *min_cost);
  for (int i = 0; i < count_addresses(searches); i++) {
    printf("%d, ", plan[i]);
  }
  return 0;
}