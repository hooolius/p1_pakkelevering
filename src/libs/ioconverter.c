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
#include "ioconverter.h"

int * converter_main(struct address *addresses, struct point *map_points){
    /*start and end point to A-star*/
	node start;
	node slut;
    /*count number of addresses*/
	int number_of_address = 0;
	while (addresses[number_of_address].closest_point != 0) {
		++number_of_address;
	}
	/*pointer array nodes*/
	node *ptrarr_punkter;
    
	/*distance matrix*/
	/*calloc two dim array of pointer*/
    int **afstand_matrix=calloc(number_of_address,sizeof(int*));
    for (int y=0; y<number_of_address;++y){
		afstand_matrix[y]=(int *) calloc(number_of_address,sizeof(int))
	}
	afstand_matrix[number_of_address][number_of_address];
	for (int g = 0; g < number_of_address; ++g) {
		for (int i = 0; i < number_of_address; ++i) {
			for (int j = 0; j < number_of_address; ++j) {
				start.lat = map_points[addresses[i].closest_point].lat;
				start.lon = map_points[addresses[i].closest_point].lon;
				slut.lat = map_points[addresses[j].closest_point].lat;
				slut.lon = map_points[addresses[j].closest_point].lon;
				ptrarr_punkter = a_star(start, slut,map_points);
				/*round and type cast to integer*/
				afstand_matrix[i][j] = (int) round(converter(ptrarr_punkter, number_of_address));
			}
		}
	}
	
    return afstand_matrix;
free(ptrarr_punkter);
free(afstand_matrix);
}


/*converter input output funtion fra a* til kombinatorisk */
double converter(node *arr_punkter, int number_of_address){
	double res = 0;
	int i;
		/*calc result*/
	for (i = 0; i < number_of_address - 1; ++i) {
			/*calc dist between two points as res and add it to it self.*/
			res+=vincent_inv_dist(arr_punkter[i].lat, arr_punkter[i].lon, arr_punkter[++i].lat,arr_punkter[++i].lon);
		}
	return res;
}


