//const major semi axis
#define R 6371e3;

//struct GPS points
struct gps_point{
    double latitude;
    double longitude;
};

/*typedef*/
typedef struct gps_point s_point; 


//function prototype
//function that we use in this project
double calculate_distance_to_points_3(s_point *point1, s_point *point2);

//struct point input data
	s_point point1;
	s_point point2;

