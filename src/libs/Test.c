#include <stdio.h>
#include <stdio.h>
#include <math.h>
/*link header fil*/
#include "Vincent_inv_dist_points.h"

int main()
{

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

/*test function*/
    printf("%lf\n", calculate_distance_to_points_3(&point1, &point2));

    return 0;
}

