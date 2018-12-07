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
//const major semi axis
#define R 6371e3;

//struct GPS points
struct gps_point{
    double latitude;
    double longitude;
};

//function prototype
//function that we use in this project
double calculate_distance_to_points_3(struct gps_point *point1 , struct gps_point *point2);

//#include "Vincent_inv_dist_points.h"
/*input param fra a* filen laves om*/
#define ANTALPUNKTER 100
/*struct punkt{
	double latitude;
	double longitude;
};*/

double converter(struct gps_point *arr_punkter);


int main(int argc, char **argv) {
	/*array af punkter fra A* med calloc*/
	struct gps_point *ptrarr_punkter=calloc(ANTALPUNKTER,sizeof(struct gps_point));
	if(ptrarr_punkter == NULL)
	{
		printf("Error! memory not allocated.");
		exit(-1);
	}

	/*test punkter*/
	ptrarr_punkter[0].latitude = 57.048270;
	ptrarr_punkter[0].longitude = 9.863372;
	ptrarr_punkter[1].latitude = 57.046114;
	ptrarr_punkter[1].longitude = 9.867273;
	double afstantest= converter(ptrarr_punkter);
	printf("test afstand %lf", afstantest);
	free(ptrarr_punkter);
	return 0;
}

double converter(struct gps_point *arr_punkter){
	int i;
	/*resultat*/
	double res=0;
	for (i = 0; i < ANTALPUNKTER-1; ++i) {
		/*Beregn afstanden mellem to punkter og summer til res*/
		res+=calculate_distance_to_points_3(&arr_punkter[i],&arr_punkter[i++]);
	}
	return res;
}
/* https://github.com/pkohut/GeoFormulas/blob/master/include/GeoFormulas.h */
/* https://community.esri.com/groups/coordinate-reference-systems/blog/2017/10/11/vincenty-formula */
/* Most accurate Vincenty’s formula */
/*the function we use Vincenty's distance formula*/
double calculate_distance_to_points_3(struct gps_point *point1, struct gps_point *point2)
{
    const double k_inverse_flattening = 298.2572235636654651;
    const double k_flattening = 1.0 / k_inverse_flattening;
    const double k_semi_major_axis = 6378137.0;
    const double k_semi_minor_axis = k_semi_major_axis * (1 - k_flattening);
    const double keps = 0.5e-15;


    double l = ((point2->longitude * M_PI) / 180) - ((point1->longitude * M_PI) / 180);
    double u1 = atan((1 - k_flattening) * tan(((point1->latitude * M_PI) / 180)));
    double u2 = atan((1 - k_flattening) * tan(((point2->latitude * M_PI) / 180)));

    double sinu1 = sin(u1);
    double cosu1 = cos(u1);
    double sinu2 = sin(u2);
    double cosu2 = cos(u2);

    double dcosu1cosu2 = cosu1 * cosu2;
    double dcosu1sinu2 = cosu1 * sinu2;

    double dsinu1sinu2 = sinu1 * sinu2;
    double dsinu1cosu2 = sinu1 * cosu2;


    double lambda = l;
    double lambdap = 2.0 * M_PI;
    int iterlimit = 0;
    double cossqalpha;
    double sinsigma;
    double cos2sigmam;
    double cossigma;
    double sigma;
    double sinalpha;
    double c;
    double sinlambda, coslambda;

    double result = 0;

    do
    {
        sinlambda = sin(lambda);
        coslambda = cos(lambda);
        sinsigma = sqrt((cosu2 * sinlambda) * (cosu2 * sinlambda) +
                        (dcosu1sinu2 - dsinu1cosu2 * coslambda) * (dcosu1sinu2 - dsinu1cosu2 * coslambda));

        if (sinsigma == 0)
            return 0;

        cossigma = dsinu1sinu2 + dcosu1cosu2 * coslambda;
        sigma = atan2(sinsigma, cossigma);
        sinalpha = dcosu1cosu2 * sinlambda / sinsigma;
        cossqalpha = 1.0 - sinalpha * sinalpha;
        cos2sigmam = cossigma - 2.0 * dsinu1sinu2 / cossqalpha;

        if (cos2sigmam < 0.0)
            cos2sigmam = 0.0;  // equatorial line: cosSqAlpha=0
        c = k_flattening / 16.0 * cossqalpha * (4.0 + k_flattening * (4.0 - 3.0 * cossqalpha));
        lambdap = lambda;
        lambda = l + (1.0 - c) * k_flattening * sinalpha *
                     (sigma + c * sinsigma * (cos2sigmam + c * cossigma * (-1.0 + 2.0 * cos2sigmam * cos2sigmam)));
    }
    while (fabs(lambda - lambdap) > keps && ++iterlimit < 40);

    double usq = cossqalpha * (k_semi_major_axis * k_semi_major_axis - k_semi_minor_axis * k_semi_minor_axis) /
                 (k_semi_minor_axis * k_semi_minor_axis);
    double a = 1.0 + usq / 16384.0 * (4096.0 + usq * (-768.0 + usq * (320.0 - 175.0 * usq)));
    double b = usq / 1024.0 * (256.0 + usq * (-128.0 + usq * (74.0 - 47.0 * usq)));
    double deltaSigma = b * sinsigma * (cos2sigmam + b / 4.0 * (cossigma * (-1.0 + 2.0 * cos2sigmam * cos2sigmam) -
                                                                b / 6.0 * cos2sigmam *
                                                                (-3.0 + 4.0 * sinsigma * sinsigma) *
                                                                (-3.0 + 4.0 * cos2sigmam * cos2sigmam)));

    result = k_semi_minor_axis * a * (sigma - deltaSigma);

    return result;
}
