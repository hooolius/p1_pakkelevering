/* 
 * converter.c
 *
 *  Created on: Dec 6, 2018
 *      Author: 
 * 
 * a star ind matrixe ud
 * a star punkt lat lon ind i gps point struct og afstand ud som matrixe
 */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <parser_addresses.h>
#include "ioconverter.h"

int **astar_to_matrix_converter(dyn_array_address *searches, struct point *map_points) {
  /*start and end point to A-star*/
  //node start;
  //node slut;
  /*count number of searches*/
  int number_of_address = searches->items;

  /*distance matrix*/
  /*calloc two dim array of pointer*/
  int **afstand_matrix = (int **) calloc(number_of_address, sizeof(int *));
  for (int y = 0; y < number_of_address; ++y) {
    afstand_matrix[y] = (int *) calloc(number_of_address, sizeof(int));
  }
  if (afstand_matrix == NULL) {
    printf("Error! memory not allocated.");
    exit(-1);
  }

  for (int i = 0; i < number_of_address; ++i) {
    for (int j = 0; j < number_of_address; ++j) {
      if (i == j) {
        afstand_matrix[i][j] = 0;
        afstand_matrix[j][i] = 0;
      }
      else {
        if (afstand_matrix[i][j] == 0 || afstand_matrix[j][i] == 0) {
          dyn_array_node *star = a_star(&map_points[searches->addresses[i].closest_point],
                                        &map_points[searches->addresses[j].closest_point], map_points);
          afstand_matrix[i][j] = (int) round(star->nodes[0]->g);
          afstand_matrix[j][i] = (int) round(star->nodes[0]->g);
          free(star);
        }
      }
    }
  }
  return afstand_matrix;
}
