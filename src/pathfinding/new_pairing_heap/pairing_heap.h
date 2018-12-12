/* pairing_heap.h - pairing heap implementation for C, to be used in our P1
 * project at AAU. Designed for use in our A* implementation. */
#include "../a_star.h"

typedef struct heap_node heap_node;
typedef struct pairing_heap pairing_heap;

struct heap_node {
  double value;
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
  queue detached;
};

