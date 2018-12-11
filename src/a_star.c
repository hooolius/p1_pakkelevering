#include <stdio.h>
#include <stdlib.h>

#define SOME_VALUE 10

struct node{
  int id;
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
};

struct point {
    double id;
    double lon;
    double lat;
    int p1;
    int p2;
    int p3;
    int p4;
    int p5;
    int p6;
};

typedef struct point point;
typedef struct node node;

int main(void) {
  node *nodes = convert_point_to_node();
  a_star(start, goal, nodes);
  return 0;
}
/* A star setup */
void a_star(node start, node goal, node *nodes) {
  int count = 0;
  dyn_array_node *closed_list = make_dyn_array_n(100);
  start.g = 0;
  start.f = start.g + jorden_er_ikke_flad(start, goal);
  //pairing_heap open_list;
  dyn_array_node *open_list = make_dyn_array_n(10);
  //heap_clear(open_list);
  add_node_to_end_n(open_list, start);
  dyn_array_node *came_from = make_dyn_array_n(100);
  node current;
  node neighbour;

  //heap_insert(open_list, start);
  //heap_insert(open_list, start);
  /* A star algoritme */
  while (count_elements_in_list(open_list) != 0) {
    /* Take node with the smallest value and copy to current */
    copy_node_to_node(current, find_min(open_list));
    /* if the distance to goal is less than 1 meter then reconstruct path */
    if(jorden_er_ikke_flad(current, goal) < 1.0) {
      free(closed_list);
      free(open_list);
      return reconstruct_path(came_from);
    }
    /* Move current node from open_list to closed_list */
    //heap_delete(open_list, current);
    delete_node_n(open_list, current);
    add_node_to_end_n(closed_list, current);
    /* Count number of neighbours and check if they exied in closed_list */
    dyn_array_node *neighbour_list = make_neighbours_list(current);
    for (size_t i = 0; i < neighbour_list.items; ++i) {
      if (contains(closed_list, neighbour_list[i])) {
        continue;   // husk at ændre neighbour til neighbour[i] i koden
      }
      /* Neighbour is calculated and put in open_list and current is put in came_from */
      neighbour_list.nodes[i].g = current.g + jorden_er_ikke_flad(current, neighbour_list.nodes[i]);
      neighbour_list.nodes[i].h = jorden_er_ikke_flad(neighbour_list.nodes[i], goal);
      neighbour_list.nodes[i].f = neighbour_list.nodes[i].h + neighbour_list.nodes[i].g;
      //heap_insert(open_list, neighbour_list.nodes[i]);
      add_node_to_end_n(open_list, neighbour_list.nodes[i]);
      add_node_to_end_n(came_from, current);
      ++count;
    }
    free(neighbour_list);
  }
  printf("A star: No path exiting program!\n");
  exit(-1);
}

node *find_min(dyn_array_node list) {
  qsort(list.nodes, list.items, sizeof(node), cmp_func);
  return list.nodes[0];
}

int cmp_func(void *a, void *b) {
  int res;
  node *aa = (node*)a;
  node *bb = (node*)b;

  if(aa.f < bb.f) {
    res = -1;
  }
  else if(aa.f == aa.f) {
    res = 0;
  }
  else {
    res = 1;
  }
  return res;
}

/*if (contains(closed_list, neighbour)) {
  continue;
}*/
node *next_neighbour(node *neighbour_list, int number_of_neighbour) {

}

dyn_array_node *make_neighbours_list(node current, node *nodes) {
  /* Follow pointers and count number of neighbours */
  /* return a pointer from a memory space where neighbours are stored */
  dyn_array_node *neighbour_list = make_dyn_array_n(6);
  if(current.p1 != 0) {
  neighbour_list = add_node_to_end_n(neighbour_list, nodes[current.p1 - 1])
  }
  if(current.p2 != 0) {
    neighbour_list = add_node_to_end_n(neighbour_list, nodes[current.p2 - 1])
  }
  if(current.p3 != 0) {
    neighbour_list = add_node_to_end_n(neighbour_list, nodes[current.p3 - 1])
  }
  if(current.p4 != 0) {
    neighbour_list = add_node_to_end_n(neighbour_list, nodes[current.p4 - 1])
  }
  if(current.p5 != 0) {
    neighbour_list = add_node_to_end_n(neighbour_list, nodes[current.p5 - 1])
  }
  if(current.p6 != 0) {
    neighbour_list = add_node_to_end_n(neighbour_list, nodes[current.p6 - 1])
  }
  return neighbour_list;
}

/* Function copys one node to a other node */
void copy_node_to_node(node destination, node source) {
  destination.lat = source.lat;
  destination.lon = source.lon;
}

int count_elements_in_list(dyn_array_node *list) {
  return list.items;
}

int contains(dyn_array_node *closed_list, node item) {
  int res = 0;
  for (int i = 0; i < closed_list.items; ++i) {
    if (closed_list.nodes[i].id == item.id) {
      res = 1;
      break;
    }
  }
  return res;
}

node reconstruct_path(dyn_array_node came_from, current) {
  node *total_path = calloc(came_from.items, sizeof(node));
  for (int i = 0; i < came_from.items; i++) {
    total_path[i] = came_from.nodes[i];
  }
  free(came_from);
  return total_path;
}

node *convert_point_to_node(int number_of_points, point *points) {
  node *nodes = malloc(sizeof(node) * number_of_points);
  for (int i = 0; i < number_of_points; ++i) {
    nodes[i].id = points[i].id;
    nodes[i].lon = points[i].lon;
    nodes[i].lat = points[i].lat;
    nodes[i].is_active = 0;
    nodes[i].g = 0;
    nodes[i].h = 0;
    nodes[i].f = 0;
    nodes[i].p1 = points[i].p1;
    nodes[i].p2 = points[i].p2;
    nodes[i].p3 = points[i].p3;
    nodes[i].p4 = points[i].p4;
    nodes[i].p5 = points[i].p5;
    nodes[i].p6 = points[i].p6;
  }
}
