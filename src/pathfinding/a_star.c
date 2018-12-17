#include "a_star.h"

node *convert_points_to_nodes(int number_of_points, point *points);

node *convert_point_to_node(point *the_point);

int count_elements_in_list(dyn_array_node *list);

/* Function copys one node to a other node */
void copy_node_to_node(node *destination, node *source);

node *find_min_array(dyn_array_node *list);

dyn_array_node *reconstruct_path(node *end, double start);

dyn_array_node *make_neighbours_list(node *current, node *nodes);

int contains(dyn_array_node *closed_list, node *item);

int cmp_func(const void *a, const void *b);

/* A star setup */
/**
*@brief In this is the main function in A* that calculates the distances inbetween the nodes 
*@param[in] *start_p This is where the route has to start
*@param[in] "point *goal_point" This is where the route has to end
*@param[in] "point *points" The list of nodes the route has to visit 
*@return 
*/
dyn_array_node *a_star(point *start_p, point *goal_p, point *points) {
  int number_of_points = 1;
  while (points[number_of_points].id != 0) {
    ++number_of_points;
  }

  node *start = convert_point_to_node(start_p);
  node *goal = convert_point_to_node(goal_p);
  node *nodes = convert_points_to_nodes(number_of_points, points);

  int count = 0;
  dyn_array_node *closed_list = make_dyn_array_n(100);
  start->g = 0;
  start->h = vincent_inv_dist(start->lat, start->lon, goal->lat, goal->lon);
  start->f = start->g + start->h;
  pairing_heap *open_list = init_heap();

  add_element(open_list, start);

  node *current;

  /* A star algoritme */
  int q = 0;
  while (open_list->size != 0) {
    q++;
    /* Take node with the smallest value and copy to current */
    current = extract_min(open_list);

    /* if the distance to goal is less than 1 meter then reconstruct path */
    if (vincent_inv_dist(current->lat, current->lon, goal->lat, goal->lon) < 1.0) {

      //return reconstruct_path(current, start->id);
      dyn_array_node *output = reconstruct_path(current, start->id);
      double output_distance = output->nodes[0]->g;
      free(start);
      free(goal);
      free(closed_list->nodes);
      free(closed_list);
      clean_heap(open_list);
      free(output);
      free(nodes);
      return output_distance;
    }
    /* Move current node from open_list to closed_list */
    add_node_to_end_n(closed_list, current);
    /* Count number of neighbours and check if they exied in closed_list */
    dyn_array_node *neighbour_list = make_neighbours_list(current, nodes);
    for (size_t i = 0; i < neighbour_list->items; ++i) {
      if (contains(closed_list, neighbour_list->nodes[i]) || heap_contains(open_list, neighbour_list->nodes[i])) {
        continue;
      }
      neighbour_list->nodes[i]->g = current->g +
                                   vincent_inv_dist(current->lat, current->lon, neighbour_list->nodes[i]->lat,
                                                    neighbour_list->nodes[i]->lon);
      neighbour_list->nodes[i]->h = vincent_inv_dist(neighbour_list->nodes[i]->lat, neighbour_list->nodes[i]->lon,
      goal->lat, goal->lon);
      neighbour_list->nodes[i]->f = neighbour_list->nodes[i]->h + neighbour_list->nodes[i]->g;
      neighbour_list->nodes[i]->came_from = current;

      add_element(open_list, neighbour_list->nodes[i]);
    }
    free(neighbour_list->nodes);
    free(neighbour_list);
  }
  printf("A star: No path exiting program!\n");
  exit(-1);
}

/**
*@brief This function will find the neighbour node with the smallest f(x) value 
*@param[in] "dyn_array_noce *list" This array contains all the neighbours in the open list
*@return returns the node with the smallest f(x) value
*/
node *find_min_array(dyn_array_node *list) {
  qsort(list->nodes, list->items, sizeof(node), cmp_func);

  return list->nodes[0];
}

int cmp_func(const void *a, const void *b) {
  int res;
  node *aa = (node *) a;
  node *bb = (node *) b;

  if (aa->f > bb->f) {
    res = -1;
  }
  else if (aa->f == aa->f) {
    res = 0;
  }
  else {
    res = 1;
  }
  return res;
}

/**
*@brief This function makes the list of neighbours to each node
*@param[in] "node *current" this is the node A* is currently working on
*@param[in] "node *nodes" The array of all streetpoints
*@return returns all the neighbours to a singe point
*/
dyn_array_node *make_neighbours_list(node *current, node *nodes) {
  /* Follow pointers and count number of neighbours */
  /* return a pointer from a memory space where neighbours are stored */
  dyn_array_node *neighbour_list = make_dyn_array_n(6);
  if (current->p1 != 0) {
    neighbour_list = add_node_to_end_n(neighbour_list, &nodes[current->p1]);
  }
  if (current->p2 != 0) {
    neighbour_list = add_node_to_end_n(neighbour_list, &nodes[current->p2]);
  }
  if (current->p3 != 0) {
    neighbour_list = add_node_to_end_n(neighbour_list, &nodes[current->p3]);
  }
  if (current->p4 != 0) {
    neighbour_list = add_node_to_end_n(neighbour_list, &nodes[current->p4]);
  }
  if (current->p5 != 0) {
    neighbour_list = add_node_to_end_n(neighbour_list, &nodes[current->p5]);
  }
  if (current->p6 != 0) {
    neighbour_list = add_node_to_end_n(neighbour_list, &nodes[current->p6]);
  }
  return neighbour_list;
}

/* Function copys one node to a other node */
/**
*@brief This copies a node from one destination to another. 
*@param[in] "node *destination" This is where the node is copied to.
*@param[in] "noce *source" This is where the node originally was.
*/
void copy_node_to_node(node *destination, node *source) {
  destination->id = source->id;
  destination->lat = source->lat;
  destination->lon = source->lon;
  destination->is_active = source->is_active;
  destination->g = source->g;
  destination->h = source->h;
  destination->f = source->f;
  destination->p1 = source->p1;
  destination->p2 = source->p2;
  destination->p3 = source->p3;
  destination->p4 = source->p4;
  destination->p5 = source->p5;
  destination->p6 = source->p6;
  destination->p7 = source->p7;
  destination->p8 = source->p8;
  destination->came_from = source->came_from;
}


int count_elements_in_list(dyn_array_node *list) {
  return list->items;
}

/**
*@brief Checks if an element i in the closed list 
*@param[in] "dyn_array_noce *closed_list" An array of all the elements in the closed list
*@param[in] "node *item" The specific node that is being checked for
*@return True or false depending if the node is in the list
*/
int contains(dyn_array_node *closed_list, node *item) {
  int res = 0;
  for (int i = 0; i < closed_list->items; ++i) {
    if (closed_list->nodes[i]->id == item->id) {
      res = 1;
      break;
    }
  }
  return res;
}

/**
*@brief This function reconstructs the path from the goal node to the start node
*@param[in] "node *end" The end node
*@param[in] start the start node
*@return The path that has been determined to be the fastest one
*/
dyn_array_node *reconstruct_path(node *end, double start) {
  dyn_array_node *total_path = make_dyn_array_n(100);
  int i = 0;
  node *current = end;
  while (current->came_from != NULL) {
    add_node_to_end_n(total_path, current);
    current = current->came_from;
    i++;
  }
  return total_path;
}

/**
*@brief Copies the data from the points struct to the nodes struckt
*@param[in] number_of_points The amount of street nodes
*@param[in] "point *points" The array of points where the mapdata is stored
*@return The array of nodes
*/
node *convert_points_to_nodes(int number_of_points, point *points) {
  node *nodes = calloc(number_of_points, sizeof(struct node));
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
    nodes[i].p7 = points[i].p7;
    nodes[i].p8 = points[i].p8;
  }
  return nodes;
}

/** 
*@brief copies the data from a single point into a single node 
*@param[in] "point *point" the array of points where the mapata is stored
*@return The node the data has been copied into.
*/
node *convert_point_to_node(point *point) {
  node *node = calloc(1, sizeof(struct node));
  node->id = point->id;
  node->lon = point->lon;
  node->lat = point->lat;
  node->is_active = 0;
  node->g = 0;
  node->h = 0;
  node->f = 0;
  node->p1 = point->p1;
  node->p2 = point->p2;
  node->p3 = point->p3;
  node->p4 = point->p4;
  node->p5 = point->p5;
  node->p6 = point->p6;
  node->p7 = point->p7;
  node->p8 = point->p8;
  return node;
}
