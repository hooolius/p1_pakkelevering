/*
 * converter.c
 *
 *  Created on: Dec 6, 2018
 *      Author: m
 *      input array af noder,
 *      beregns afstanden mellem dem ved vincentyafstan.
 *      summere afstandene sammen
 */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "Vincent_inv_dist_points.h"

/*input param med antal punkter fra a* filen laves om*/
//#define ANTALPUNKTER 100

double converter(gps_point *arr_punkter int number_of_address);

gps_point *node_to_gps_point_converter(node *nodes)

int converter_main(points_address *addresses, node *nodes) {
	/*array af punkter fra A* med calloc*/
	//struct gps_point *ptrarr_punkter=calloc(ANTALPUNKTER,sizeof(struct gps_point));

	node_to_gps_point_converter();

	node start;
	node slut;
	int number_of_address = 0;
	while (addresses[number_of_address].closest_node != 0) {
		++number_of_address;
	}

	for (int i = 0; i < number_of_address, ++i) {
		struct gps_point *ptrarr_punkter;
		double afstantest[number_of_address][number_of_address];
		for (int i = 0; i < number_of_address; ++i) {
			for (int j = 0; j < number_of_address; ++j) {
				start.lat = nodes[addresses[i].closest_node].lat;
				start.lon = nodes[addresses[i].closest_node].lon;
				slut.lat = nodes[addresses[j].closest_node].lat;
				slut.lon = nodes[addresses[j].closest_node].lon;
				ptrarr_punkter; = a_star(start, slut);
				if(ptrarr_punkter == NULL)
				{
					printf("Error! memory not allocated.");
					exit(-1);
				}
				afstantest[i][j] = converter(ptrarr_punkter int number_of_address);
				free(ptrarr_punkter);
			}
		}
	}
	return 0;
}
/*converter input output funtion fra a* til kombinatorisk */
double converter(gps_point *arr_punkter int number_of_address){
	double res = 0;
	if(arr_punkter > 1) {
		int i;
		/*resultat*/

		for (i = 0; i < number_of_address - 1; ++i) {
			/*Beregn afstanden mellem to punkter og summere til res*/
			res += vincent_inv_dist(&arr_punkter[i],&arr_punkter[i++]);
		}
	}
	else {
		res = 0;
	}
	return res;
}

void matrice_maker() {
	double matrice[number_of_address][number_of_address];
	int i, j;

   /* for every value of   */
   for (i = 0; i < number_of_address; ++i) {

      for (j = 0; j < number_of_address; ++j) {

      }
   }
}

gps_point *node_to_gps_point_converter(node *nodes) {
	int i = 0, number_of_nodes;
	while (nodes[i].id != 0) {
		++number_of_nodes;
	}
	gps_point *points = calloc(number_of_nodes, sizeof(gps_point));
	for (i = 0; i < number_of_nodes; ++i) {
		points.latitude = nodes.lat;
		points.longitude = nodes.lon;
	}
	return points;
}
