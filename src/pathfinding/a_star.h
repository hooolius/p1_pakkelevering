#include <stdio.h>
#include <stdlib.h>
#include "../map_gen/map_parser.h"
#include "pairing_heap.h"
#include "../libs/dynamic_array.h"
#include "../libs/vincent_inv_dist_points.h"

typedef struct point point;

double a_star(struct point *start_p, struct point *goal_p, struct point *points);