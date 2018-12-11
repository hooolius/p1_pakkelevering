#include <stdio.h>
#include <stdlib.h>
#include "main_config.h"
/*#include "convert_distance.h"*/
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
};
*/
typedef struct node node;


#include "pairing_heap.h"
#include "dynamic_array.h"
#include "a_star.h"
#include "map_gen/addresses_prompt.h"
#include "map_gen/parser_addresses.h"
#include "map_gen/map_parser.h"
#include "map_gen/address_to_point_calc.h"
typedef struct point point;


int main(void) {
    struct address *searches;
    point *map_points;

    searches = calloc(20, sizeof(struct address));
    map_points = calloc(points_counter(), sizeof(point));

    addresses_prompt(searches);
    map_parser(map_points);
    addresses_to_point_calc(searches, map_points);

    printf("Version %d.%d \n",
      p1_pakkelevering_VERSION_MAJOR, p1_pakkelevering_VERSION_MINOR);
    printf("Testing: %lf",searches[0].closest_point_dist);

    point start = map_points[0];
    point slut = map_points[100];

    node *star = a_star(start, slut, map_points);
    int i = 0;
    while (star[i].id != 0) {
      printf("%lf : %lf\n", star[i].lat, star[i].lon);
      ++i;
    }

    return 0;
}
