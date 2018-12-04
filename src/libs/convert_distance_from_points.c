#include <stdio.h>
#include <stdio.h>
#include <math.h>
#include "convert_distance_from_points.h"
int main()
{
	//struct point
	s_point point1;
	s_point point2;

    /* Deltavej raw data */
    /*point1.latitude = 57.0451913;
    point1.longitude = 9.8714065;
    point2.latitude = 57.0464232;
    point2.longitude = 9.8689897;*/
    /* Deltavej as read from QGIS */
    /*point1.latitude = 57.045191;
    point1.longitude = 9.871407;
    point2.latitude = 57.046423;
    point2.longitude = 9.868990;*/
    /* Other road */
    point1.latitude = 57.048270;
    point1.longitude = 9.863372;
    point2.latitude = 57.046114;
    point2.longitude = 9.867273;

    printf("%lf\n", calculate_distance_to_points(&point1, &point2));
    printf("%lf\n", calculate_distance_to_points_2(&point1, &point2));
    printf("%lf\n", calculate_distance_to_points_3(&point1, &point2));

    return 0;
}

/* http://www.5thandpenn.com/GeoMaps/GMapsExamples/distanceComplete2.html */
double calculate_distance_to_points(struct gps_point *point1, struct gps_point *point2)
{
    double phi_1 = (point1->latitude * M_PI) / 180;
    double phi_2 = (point2->latitude * M_PI) / 180;
    double lambda_1 = (point1->longitude * M_PI) / 180;
    double lambda_2 = (point2->longitude * M_PI) / 180;

    double x = (lambda_2 - lambda_1) * cos((phi_1+phi_2)/2);
    double y = (phi_2 - phi_1);
    double d = sqrt(x*x + y*y) * R;

    return d;
}

/* http://www.5thandpenn.com/GeoMaps/GMapsExamples/distanceComplete2.html */
double calculate_distance_to_points_2(struct gps_point *point1, struct gps_point *point2)
{
    double phi_1 = (point1->latitude * M_PI) / 180;
    double phi_2 = (point2->latitude * M_PI) / 180;

    double delta_phi = ((point2->latitude - point1->latitude) * M_PI) / 180;
    double delta_lambda = ((point2->longitude - point1->longitude) * M_PI) / 180;

    double a = sin(delta_phi/2) * sin(delta_phi/2) + cos(phi_1) * cos(phi_2) * sin(delta_lambda/2) * sin(delta_lambda/2);
    double c = 2 * atan(sqrt(a));
    double radius = R;
    double d = radius * c;

    return d;
}

/* https://github.com/pkohut/GeoFormulas/blob/master/include/GeoFormulas.h */
/* https://community.esri.com/groups/coordinate-reference-systems/blog/2017/10/11/vincenty-formula */
/* Most accurate Vincenty’s formula */
double calculate_distance_to_points_3(struct gps_point *point1, struct gps_point *point2)
{
    const double kInverseFlattening = 298.2572235636654651;
    const double kFlattening = 1.0 / kInverseFlattening;
    const double kSemiMajorAxis = 6378137.0;
    const double kSemiMinorAxis = kSemiMajorAxis * (1 - kFlattening);
    const double kEps = 0.5e-15;


    double L = ((point2->longitude * M_PI) / 180) - ((point1->longitude * M_PI) / 180);
    double U1 = atan((1 - kFlattening) * tan(((point1->latitude * M_PI) / 180)));
    double U2 = atan((1 - kFlattening) * tan(((point2->latitude * M_PI) / 180)));

    double sinU1 = sin(U1);
    double cosU1 = cos(U1);
    double sinU2 = sin(U2);
    double cosU2 = cos(U2);

    double dCosU1CosU2 = cosU1 * cosU2;
    double dCosU1SinU2 = cosU1 * sinU2;

    double dSinU1SinU2 = sinU1 * sinU2;
    double dSinU1CosU2 = sinU1 * cosU2;


    double lambda = L;
    double lambdaP = 2.0 * M_PI;
    int iterLimit = 0;
    double cosSqAlpha;
    double sinSigma;
    double cos2SigmaM;
    double cosSigma;
    double sigma;
    double sinAlpha;
    double C;
    double sinLambda, cosLambda;

    double result = 0;

    do
    {
        sinLambda = sin(lambda);
        cosLambda = cos(lambda);
        sinSigma = sqrt((cosU2 * sinLambda) * (cosU2 * sinLambda) +
                        (dCosU1SinU2 - dSinU1CosU2 * cosLambda) * (dCosU1SinU2 - dSinU1CosU2 * cosLambda));

        if (sinSigma == 0)
            return 0;

        cosSigma = dSinU1SinU2 + dCosU1CosU2 * cosLambda;
        sigma = atan2(sinSigma, cosSigma);
        sinAlpha = dCosU1CosU2 * sinLambda / sinSigma;
        cosSqAlpha = 1.0 - sinAlpha * sinAlpha;
        cos2SigmaM = cosSigma - 2.0 * dSinU1SinU2 / cosSqAlpha;

        if (cos2SigmaM < 0.0)
            cos2SigmaM = 0.0;  // equatorial line: cosSqAlpha=0
        C = kFlattening / 16.0 * cosSqAlpha * (4.0 + kFlattening * (4.0 - 3.0 * cosSqAlpha));
        lambdaP = lambda;
        lambda = L + (1.0 - C) * kFlattening * sinAlpha *
                     (sigma + C * sinSigma * (cos2SigmaM + C * cosSigma * (-1.0 + 2.0 * cos2SigmaM * cos2SigmaM)));
    }
    while (fabs(lambda - lambdaP) > kEps && ++iterLimit < 40);

    double uSq = cosSqAlpha * (kSemiMajorAxis * kSemiMajorAxis - kSemiMinorAxis * kSemiMinorAxis) /
                 (kSemiMinorAxis * kSemiMinorAxis);
    double A = 1.0 + uSq / 16384.0 * (4096.0 + uSq * (-768.0 + uSq * (320.0 - 175.0 * uSq)));
    double B = uSq / 1024.0 * (256.0 + uSq * (-128.0 + uSq * (74.0 - 47.0 * uSq)));
    double deltaSigma = B * sinSigma * (cos2SigmaM + B / 4.0 * (cosSigma * (-1.0 + 2.0 * cos2SigmaM * cos2SigmaM) -
                                                                B / 6.0 * cos2SigmaM *
                                                                (-3.0 + 4.0 * sinSigma * sinSigma) *
                                                                (-3.0 + 4.0 * cos2SigmaM * cos2SigmaM)));

    result = kSemiMinorAxis * A * (sigma - deltaSigma);

    return result;
}