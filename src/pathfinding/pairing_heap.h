/* pairing_heap.h - pairing heap implementation for C, to be used in our P1 #include <stdio.h>
#include <math.h>

#define R 6371e3;

struct gps_point{
    double latitude;
    double longitude;
};

double calculate_distance_to_points(struct gps_point *point1, struct gps_point *point2);
double calculate_distance_to_points_2(struct gps_point *point1, struct gps_point *point2);
double calculate_distance_to_points_3(struct gps_point *point1, struct gps_point *point2);

 * project at AAU. Designed for use in our A* implementation. */

typedef struct dyn_array_heap dyn_array_heap;
typedef struct heap_elem heap_elem;
typedef struct pairing_heap pairing_heap;

struct dyn_array_heap {
  //The threshold for then the array is reduced in size
  int low_water_mark;
  //The threshold for then the array is expanded in size
  int high_water_mark;
  //The minimum size the array can have
  int min_capacity;
  //Number of items in array
  int items;
  pairing_heap *heaps;
};

struct heap_elem {
  double value;
  heap_elem *pleft_child;
  heap_elem *pprev_sibling;
  heap_elem *pnext_sibling;
};

struct pairing_heap {
  int size;
  heap_elem *proot;
  dyn_array_heap *subheaps;
};

//initialize heap
void heap_init(pairing_heap heap);
// returns the lowest value in the heap
heap_elem find_min(pairing_heap heap);
// merges two heaps together
pairing_heap merge(pairing_heap heap1, pairing_heap heap2);
// returns and deletes the min element in a heap
heap_elem extract_min(pairing_heap heap);
// deletes the minimum element of the heap
void delete_min(pairing_heap heap);
// inserts an element into a heap 
void insert_elem(pairing_heap heap, heap_elem elem, double value);
// removes a node from the heap 
void delete_elem(int i, pairing_heap heap);
// redefines the element i to n 
