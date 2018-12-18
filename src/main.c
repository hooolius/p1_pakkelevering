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
#include "combinatorial_optimisation/greedy.h"

#if defined(__linux) || defined(__linux__) || defined(linux)
# define LINUX
  
#elif defined(__APPLE__)
# define MACOS
  
#elif defined(_WIN32) || defined(__WIN32__) || defined(WIN32) || defined(_WIN64)
# define WINDOWS
  
#endif

typedef struct point point;


int main(int argc, char *argv[]) {

  FILE* input = fopen(NULL, "r");
  if (argc == 2) {
    input = fopen(argv[1], "r");
  }
  time_t total_timer,total_end_timer;
  time_t start_map, end_map;
  time_t start_a, end_a;
  time_t start_held, end_held;
  total_timer = clock();

  dyn_array_address *searches = make_dyn_array_a(2);
  point *map_points = calloc(points_counter(), sizeof(point));

  addresses_prompt(searches, input);
  start_map = clock();
  //printf("Map parsed started \n");
  map_parser(map_points);
  addresses_to_point_calc(searches, map_points);
  end_map = clock();
  //printf("Map and addresses parsed time %f \n",(double )(end_map-start_map)/1000000);

  //printf("Version %d.%d \n",
  //    p1_pakkelevering_VERSION_MAJOR, p1_pakkelevering_VERSION_MINOR);

  //printf("A* started \n");
  start_a = clock();
  int **matrix = astar_to_matrix_converter(searches, map_points);
  end_a = clock();
  //printf("All A* done, time: %f \n",(double ) (end_a-start_a)/1000000);

  int min_cost = 0;
  int plan[searches->items+1];

  //printf("Held karp started \n");
  start_held = clock();
  min_cost = run_greedy(matrix, searches->items);
  //min_cost = held_karp(matrix, searches->items, 0, plan);
  end_held = clock();
  //printf("Held karp done, time: %f \n",(double) (end_held-start_held)/1000000);
  //printf("Rutens kilometer: %.2lf km \n",(double) min_cost/1000);
  //for (int i = 0; i < searches->items+1; i++) {
  //  printf("%d: %s %s \n", i, searches->addresses[plan[i]].tags.street, searches->addresses[plan[i]].tags.house_number);
  //}
  total_end_timer = clock();
  printf("%lf , %lf, %lf ",(double) (end_a-start_a)/1000000,(double) (end_held-start_held)/1000000,(double) (total_end_timer-total_timer)/1000000);
  free(searches);

  printf("min cost: %d\n", min_cost);
  return 0;
}
