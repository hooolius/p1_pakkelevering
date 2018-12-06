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

#define ANTALPUNKTER 100
struct punkt{
	double latitude;
	double longitude;
};

double converter(struct punkt *arr_punkter);
/*array af punkter fra A* med calloc*/


int main(int argc, char **argv) {
	struct punkt *ptrarr_punkter=calloc(ANTALPUNKTER,sizeof(struct punkt));
	if(ptrarr_punkter == NULL)
	{
		printf("Error! memory not allocated.");
		exit(-1);
	}

	/*test punkter*/
	ptrarr_punkter[1].latitude = 57.048270;
	ptrarr_punkter[1].longitude = 9.863372;
	ptrarr_punkter[2].latitude = 57.046114;
	ptrarr_punkter[2].longitude = 9.867273;
	double afstantest= converter(&ptrarr_punkter);
	printf("test afstand %lf", afstantest);
	free(ptrarr_punkter);
	return 0;
}

double converter(struct punkt *arr_punkter){
	int i;
	/*resultat*/
	double res=0;
	for (i = 0; i < ANTALPUNKTER; ++i) {
		/*Beregn afstanden mellem to punkter og summer til res*/
		res+=calculate_distance_to_points_3(&arr_punkter[i],&arr_punkter[i++]);
	}
	return res;
}
