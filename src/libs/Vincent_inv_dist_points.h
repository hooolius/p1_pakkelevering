//const major semi axis
#define R 6371e3;

//struct GPS points
struct gps_point{
    double latitude;
    double longitude;
};

//function prototype
//function that we use in this project
double vincent_inv_dist(struct gps_point *point1 , struct gps_point *point2);

//struct point input data
//	struct gps_point point1;
//	struct gps_point point2;

