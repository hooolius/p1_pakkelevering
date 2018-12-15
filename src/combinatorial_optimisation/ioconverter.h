#include "../pathfinding/a_star.h"
#include "../libs/dynamic_array.h"

/*input param med antal punkter fra a* filen laves om*/
//#define ANTALPUNKTER 100

/*prototypes*/

/**
 *main function in converter:
 * @param[in] dyn_array_address
 * @param[in] pointer of type point
 * @return afstand_matrix 2D integer matrix
 */
int **astar_to_matrix_converter(dyn_array_address *searches, struct point *map_points);