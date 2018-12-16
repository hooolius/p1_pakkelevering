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

int main(int argc, char *argv[]) {
  dyn_array_address *map_points = make_dyn_array_a(500);
  int num_addr = parser_addreses_ALL(map_points);

  int num_points = atoi(argv[1]);
  int times_to_gen = atoi(argv[2]);
  char mkdir_str[100];
  char file_str[100];

  for (int j = 0; j < times_to_gen; j++){
    sprintf(mkdir_str, "mkdir -p count%d/", num_points);
    system(mkdir_str);
    sprintf(file_str, "count%d/set%d.txt", num_points, j+1);
    FILE *output_file = fopen(file_str, "w");
    for (int i = 0; i < num_points; i++) {
      int n = rand() % map_points->items + 1;
      fprintf(output_file, "%s, %s, %s, %s, %s, %s.\n",
               map_points->addresses[n].tags.city, map_points->addresses[n].tags.country,
               map_points->addresses[n].tags.house_number, map_points->addresses[n].tags.muncipality,
               map_points->addresses[n].tags.postcode, map_points->addresses[n].tags.street);
    }
  }
}
