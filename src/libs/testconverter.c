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
 * an array of struct of point AKA param points_adress
 * an pointer array of point struct from map parser
 * @param addresses
 * @param nodes
 * @return
 */
int converter_main(points_address *addresses, point_arr *nodes);

int main (void){
	converter_main();
	return 0;
}


int converter_main(points_address *addresses, point_arr *point) {
	/*array af punkter fra A* med calloc*/
	//struct gps_point *ptrarr_punkter=calloc(ANTALPUNKTER,sizeof(struct gps_point));

	/*node_to_gps_point_converter(node *nodes);*/

	node start;
	node slut;
	int number_of_address = 0;
	/*count number of addresses*/
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
				ptrarr_punkter = a_star(start, slut);
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
