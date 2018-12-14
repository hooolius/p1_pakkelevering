/* pairing_heap.h - pairing heap implementation for C, to be used in our P1
 * project at AAU. Designed for use in our A* implementation. */
#ifndef NODE
#define NODE

typedef struct node node;
struct node {
  double id;
  double lat;
  double lon;
  double g;
  double h;
  double f;
  int is_active;
  int p1;
  int p2;
  int p3;
  int p4;
  int p5;
  int p6;
  node *came_from;
};
#endif
#ifndef PAIRING
#define PAIRING
typedef struct heap_node heap_node;
typedef struct pairing_heap pairing_heap;
typedef struct dyn_array_heap dyn_array_heap;

struct heap_node {
    node *element;
    struct heap_node *child;
    struct heap_node *sib_left;
    struct heap_node *sib_right;
    struct heap_node *next;
    struct heap_node *prev;
};

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

struct pairing_heap {
    int size;
    heap_node *root;
    heap_node FORE;
    heap_node AFT;
    dyn_array_heap detached;
};

pairing_heap *init_heap();
node min(pairing_heap *pheap);
heap_node *find(pairing_heap *pheap,node *element);
int heap_contains(pairing_heap *pheap, node *element);
void add_element(pairing_heap *pheap, node *element);
void update(pairing_heap *pheap, heap_node *hnode, node *element);
node *extract_min(pairing_heap *pheap);

#endif
