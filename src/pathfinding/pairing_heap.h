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

/**
 * @brief Node in a pairing heap
 */
struct heap_node {
    node *element; /**< The element the heap node holds, this also has the f value that is used to sort */
    struct heap_node *child; /**< A pointer to the leftmost child of the node */
    struct heap_node *sib_left; /**< A pointer to the sibling to the left of the node, the parent if it's the leftmost node, or to itself it the node is the root of the heap tree. */
    struct heap_node *sib_right; /**< A pointer to the sibling to the right of the node */
    struct heap_node *next; /**< A pointer to the next node in the iteration list */
    struct heap_node *prev; /**> A pointer to the previous node in the iteration list */
};

/**
 * @brief Dynamic array holding heap nodes
 */
struct dyn_array_heap {
  int low_water_mark; /**< The threshold for then the array is reduced in size */
  int high_water_mark; /**< The threshold for then the array is expanded in size */
  int min_capacity; /**< The minimum size the array can have */
  int items; /**< Number of items in array */
  heap_node **heap_nodes; /**< Array of heap nodes */
};

/**
 * @brief A pairing heap
 */
struct pairing_heap {
    int size; /**< Amount of elements in the heap */
    heap_node *root; /**< A pointer to the root element (lowest) of the node */
    heap_node FORE; /**< The FORE element is the first element in the iteration list */
    heap_node AFT; /**< The AFT element is the last element in the iteration list */
    dyn_array_heap *detached; /**< A dynamic array containing the currently detached heap nodes, used when rebuilding structure */
};

/**
 * @brief Initialises an empty heap
 *
 * @return A pointer to a new heap
 */
pairing_heap *init_heap();
/**
 * @brief Checks whether or not an element is in a heap
 *
 * @param[in] pheap The heap to search in
 * @param[in] element The element to search for
 *
 * @return 1 if the element is in the heap, else 0
 */
int heap_contains(pairing_heap *pheap, node *element);
/**
 * @brief Adds an element to a heap
 *
 * @param[out] pheap The heap to add the element to
 * @param[in] element The element to add to the heap
 */
void add_element(pairing_heap *pheap, node *element);
/**
 * @brief Extracts the root of the heap, and removes it from the heap
 *
 * @param[in] pheap The heap to extract minimum from
 *
 * @return The minimum value of the heap
 */
node *extract_min(pairing_heap *pheap);
/**
 * @brief Frees all memory in the heap
 *
 * @param[in] pheap The heap to free memory froom
 */
void clean_heap(pairing_heap *pheap);
#endif
