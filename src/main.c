#include <stdio.h>
#include <stdlib.h>
#include "main_config.h"
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

  point start = map_points[0];
  point slut = map_points[100];

  node *star = a_star(&start, &slut, map_points);
  int i = 0;
  while (star[i].id != 0) {
    printf("%lf : %lf\n", star[i].lat, star[i].lon);
    ++i;
  }

  return 0;
}
