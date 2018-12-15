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

int *converter_main(struct address *addresses, struct point *map_points){
	/*start and end point to A-star*/
	//node start;
	//node slut;
	/*count number of addresses*/
	int number_of_address = 0;
	while (addresses[number_of_address].closest_point != 0) {
		++number_of_address;
	}

	/*distance matrix*/
	/*calloc two dim array of pointer*/
	int **afstand_matrix=calloc(number_of_address,sizeof(int*));
	for (int y=0; y<number_of_address;++y){
		afstand_matrix[y]=(int *) calloc(number_of_address,sizeof(int))
	}
	if(afstand_matrix == NULL)
	{
		printf("Error! memory not allocated.");
		exit(-1);
	}
	afstand_matrix[number_of_address][number_of_address];
		for (int i = 0; i < number_of_address; ++i) {
			for (int j = 0; j < number_of_address; ++j) {
				if (i==j){
					afstand_matrix[i][j]=0;
					afstand_matrix[j][i]=0;
				}
				/*calling A star function*/
				dyn_array_node *star = a_star(&start, &slut, map_points);
				printf("TEST: %lf ",star->nodes[0].g);
				/*round and type cast to integer*/
				afstand_matrix[i][j] = (int) round(star->nodes[0].g);
				afstand_matrix[j][i] = (int) round(star->nodes[0].g);
			}
		}

	return afstand_matrix;
}




