#include <stdio.h>
#include <stdlib.h>
#include "main_config.h"
#include "libs/dynamic_array.h"
#include "pathfinding/a_star.h"
#include "map_gen/addresses_prompt.h"
#include "map_gen/parser_addresses.h"
#include "map_gen/map_parser.h"
#include "map_gen/address_to_point_calc.h"
typedef struct point point;


main(int argc, char *argv[]) {

  printf("%s", argv[0]);
  struct address *searches;
  point *map_points;

  searches = calloc(20, sizeof(struct address));
  map_points = calloc(points_counter(), sizeof(point));

  addresses_prompt(searches);
  map_parser(map_points);
  addresses_to_point_calc(searches, map_points);

  printf("Version %d.%d \n",
      p1_pakkelevering_VERSION_MAJOR, p1_pakkelevering_VERSION_MINOR);

  point start = map_points[searches[0].closest_point];
  point slut = map_points[searches[1].closest_point];

  //dyn_array_node *star = a_star(&start, &slut, map_points);



  //int i = 0;
  //while (star->nodes[i].id != 0) {
   // printf("%lf : %lf\n", star->nodes[i].lat, star->nodes[i].lon);
   // ++i;
  //}

  return 0;
}
