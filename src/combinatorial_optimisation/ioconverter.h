#include "../pathfinding/a_star.h"
#include "../libs/dynamic_array.h"

/**
 * prototypes
/**
 *main function in input output converter:
 * @param[in] "*searches" is a dynamic array of addresses
 * @param[in] "*map_points" is a pointer of type point
 * @return "afstand_matrix" 2D integer distance matrix
 */
int **astar_to_matrix_converter(dyn_array_address *searches, struct point *map_points);
