#include "a_star.h"

/*input param med antal punkter fra a* filen laves om*/
//#define ANTALPUNKTER 100

/*prototypes*/


/**
 *main function in converter remember to add param:
 * an array of pointers of struct of point AKA param points_adress
 * an array of pointer from point struct from map parser
 * @param addresses
 * @param nodes
 * @return
 */
int * converter_main(struct address *addresses, struct point *map_points);