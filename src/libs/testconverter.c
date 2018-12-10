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
#define ANTALPUNKTER 100

double converter(struct gps_point *arr_punkter);


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
		start.lat = nodes[addresses[i].closest_node].lat;
		start.lon = nodes[addresses[i].closest_node].lon;
		slut.lat = nodes[addresses[++i].closest_node].lat;
		slut.lon = nodes[addresses[++i].closest_node].lon;

		struct gps_point *ptrarr_punkter = a_star(start, slut);
		if(ptrarr_punkter == NULL)
		{
			printf("Error! memory not allocated.");
			exit(-1);
		}

		/*test punkter
		ptrarr_punkter[0].latitude = 57.048270;
		ptrarr_punkter[0].longitude = 9.863372;
		ptrarr_punkter[1].latitude = 57.046114;
		ptrarr_punkter[1].longitude = 9.867273;*/
		double afstantest = converter(ptrarr_punkter);
		printf("test afstand %lf", afstantest);

		matrice_maker();

		free(ptrarr_punkter);
		++number_of_address;
	}

	return 0;
}
/*converter input output funtion fra a* til kombinatorisk */
double converter(gps_point *arr_punkter){
	int i;
	/*resultat*/
	double res=0;
	for (i = 0; i < ANTALPUNKTER - 1; ++i) {
		/*Beregn afstanden mellem to punkter og summere til res*/
		res += vincent_inv_dist(&arr_punkter[i],&arr_punkter[i++]);
	}
	return res;
}

void matrice_maker() {

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
