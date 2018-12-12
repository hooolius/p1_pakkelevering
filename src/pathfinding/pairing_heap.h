/* pairing_heap.h - pairing heap implementation for C, to be used in our P1
 * project at AAU. Designed for use in our A* implementation. */
#include "../a_star.h"

typedef struct heap_node heap_node;
typedef struct pairing_heap pairing_heap;
typedef struct locator locator;
typedef struct dyn_array_heap dyn_array_heap;

struct dyn_array_heap {
    //The threshold for then the array is reduced in size
    int low_water_mark;
    //The threshold for then the array is expanded in size
    int high_water_mark;
    //The minimum size the array can have
    int min_capacity;
    //Number of items in array
    int items;
    heap_node *heap_nodes;
};

struct heap_node {
  node *element;
  heap_node *child;
  heap_node *sib_left;
  heap_node *sib_right;
  heap_node *next;
  heap_node *prev;
};

struct pairing_heap {
  int size;
  heap_node *root;
  heap_node *FORE;
  heap_node *AFT;
  dyn_array_heap detached;
};

// struct locator {
  // heap_node tracked_element;
// };
