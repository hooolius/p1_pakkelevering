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
#include "Vincent_inv_dist_points.h"
#include "map_gen/addresses_prompt.h"
#include "map_gen/parser_addresses.h"
#include "map_gen/map_parser.h"
#include "map_gen/address_to_point_calc.h"
#include "a_star.h"

/*input param med antal punkter fra a* filen laves om*/
//#define ANTALPUNKTER 100

/*prototypes*/
double converter(gps_point *arr_punkter int number_of_address);

gps_point * node_to_gps_point_converter(node *nodes);

/**
 *main function in converter remember to add param:
 * an array of pointers of struct of point AKA param points_adress
 * an array of pointer from point struct from map parser
 * @param addresses
 * @param nodes
 * @return
 */
int converter_main(struct address *addresses, struct point *map_points);

int main (void){

	return 0;
}


int converter_main(struct address *addresses, struct point *map_points) {
	/*array af punkter fra A* med calloc*/
	//struct gps_point *ptrarr_punkter=calloc(ANTALPUNKTER,sizeof(struct gps_point));
	/*struct gps_point *ptrarr_punkter;
	 */


	node start;
	node slut;
	int number_of_address = 0;
	/*count number of addresses*/
	while (addresses[number_of_address].closest_point != 0) {
		++number_of_address;
	}
	/*calloc array nodes*/
	node *ptrarr_punkter;
	/*distance matrix*/
	double afstand[number_of_address][number_of_address];
	for (int g = 0; g < number_of_address; ++g) {
		for (int i = 0; i < number_of_address; ++i) {
			for (int j = 0; j < number_of_address; ++j) {
				start.lat = map_points[addresses[i].closest_point].lat;
				start.lon = map_points[addresses[i].closest_point].lon;
				slut.lat = map_points[addresses[j].closest_point].lat;
				slut.lon = map_points[addresses[j].closest_point].lon;
				ptrarr_punkter = a_star(start, slut,map_points);
				afstand[i][j] = converter(ptrarr_punkter, number_of_address);
			}
		}
	}
	free(ptrarr_punkter);
}


/*converter input output funtion fra a* til kombinatorisk */
double converter(node *arr_punkter, int number_of_address){
	double res = 0;
	int i;
	/*sporg mark*/
	if(arr_punkter > 1) {

		/*calc result*/

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
