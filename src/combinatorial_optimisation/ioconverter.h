#include "../pathfinding/a_star.h"
#include "../libs/dynamic_array.h"

/**
 * prototypes
/**
 *main function in input output converter:
 * @param[in] a dynamic array of adresses
 * @param[in] pointer of type point
 * @return 2D integer distance matrix
 */
int **astar_to_matrix_converter(dyn_array_address *searches, struct point *map_points);
node *convert_points_to_nodes(int number_of_points, point *points);

node *convert_point_to_node(point *the_point);
void remove_from_closed(int number_of_points, node *nodes);

