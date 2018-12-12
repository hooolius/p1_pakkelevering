/*link header fil*/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "Vincent_inv_dist_points.h"

/* https://github.com/pkohut/GeoFormulas/blob/master/include/GeoFormulas.h */
/* https://community.esri.com/groups/coordinate-reference-systems/blog/2017/10/11/vincenty-formula */
/* Most accurate Vincenty’s formula */
/*the function we use Vincenty's distance formula*/
double vincent_inv_dist(struct gps_point *point1, struct gps_point *point2)
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

