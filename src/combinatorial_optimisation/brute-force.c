#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

int *brute_force(int **matrix, int size) {
  int min_cost = INT_MAX;
  int curr_cost;
  int min_route[size+1];
  int curr_route[size+1];
  int route_table[size][size];
  memset(route_table, 0, size * size * sizeof(int));

  
}
