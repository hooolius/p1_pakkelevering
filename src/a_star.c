#include <stdio.h>
#include <stdlib.h>

#define SOME_VALUE 10

struct a_node{
  float lat;
  float lon;
  double g;
  double h;
  double f;
  int is_active;
};

typedef struct a_node node;

int main(void) {
  a_star();
  return 0;
}
/* A star setup */
void a_star(node start, node goal) {
  node closed_list = calloc(SOME_VALUE, sizeof(node));
  start.g = 0;
  start.f = start.g + jorden_er_ikke_flad(start, goal);
  pairing_heap open_list;
  heap_clear(open_list);
  insert_elem(start);
  dyn_array came_from;
  node current;

  node neighbour;

  heap_insert(open_list, start);
  /* A star algoritme */
  while (count_elements_in_list(open_list) != 0) {
    /* Take node with the smallest value and copy to current */
    copy_node_to_node(current, find_min(open_list));
    /* if the distance to goal is less than 1 meter then reconstruct path */
    if(jorden_er_ikke_flad(current, goal) < 1){
      return reconstruct_path(came_from, current);
    }
    /* Move current node from open_list to closed_list */
    heap_delete(open_list, current);
    dyn_insert(closed_list, current);
    /* Count number of neighbours and check if they exied in closed_list */
    node *neighbour_list = make_neighbours_list(current);
    int number_of_neighbours = count_elements_in_list(neighbour_list);
    for (size_t i = 0; i < number_of_neighbours; ++i) {
      if (contains(closed_list, next_neighbour(neighbour_list, i))) {
        continue;   // husk at ændre neighbour til neighbour[i] i koden
      }
      /* Neighbour is calculated and put in open_list and current is put in came_from */
      neighbour.g = current.g + jorden_er_ikke_flad(current, neighbour);
      neighbour.h = jorden_er_ikke_flad(neighbour, goal);
      neighbour.f = neighbour.h + neighbour.g;
      heap_insert(open_list, neighbour);
      insert(came_from, current);
    }
  }
}

/*if (contains(closed_list, neighbour)) {
  continue;
}*/
node *next_neighbour(node *neighbour_list, int number_of_neighbour) {

}

node *make_neighbours_list(node current) {
  /* Follow pointers and count number of neighbours */
  /* return a pointer from a memory space where neighbours are stored */
}

/* Function copys one node to a other node */
void copy_node_to_node(node destination, node source) {
  destination.lat = source.lat;
  destination.lon = source.lon;
}
/* Julius ved ikke om du skal tænke over om denne funktion skal virke sådan */
int count_elements_in_list(node *list){
  int res = 0;
  for (size_t i = 0; i < list.count; i++) {
    if (list[i].is_active == 1) {
      ++res;
    }
  }
  return res;
}

node reconstruct_path(came_from, current) {
  while (contains(came_from, current)) {
    insert(total_path, current);
    current = came_from[current];
  }
}

void insert(node list[], node node_to_insert) {
  /* Julius du laver sådan en her tak */
}

void delete(node list[], node node_to_delete) {
  /* Julius du laver sådan en her tak */
}

node extract_min(node list[]) {
  /* Julius du laver sådan en her tak */
}
