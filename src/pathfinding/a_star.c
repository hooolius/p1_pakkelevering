#include "a_star.h"

dyn_array_node *reconstruct_path(node *end);

dyn_array_node *make_neighbours_list(node *current, node *nodes);

/* A star setup */
/**
*@brief In this is the main function in A* that calculates the distances between the nodes
*@param[in] "node *start" This is where the route has to start
*@param[in] "node *goal" This is where the route has to end
*@param[in] "node *nodes" The list of all nodes a star can visit
*@return "output_distance" a double that is the distance that a star travels from start to goal
*/
double a_star(node *start, node *goal, node *nodes) {
  dyn_array_node *closed_list = make_dyn_array_n(100);
  start->g = 0;
  start->h = vincent_inv_dist(start->lat, start->lon, goal->lat, goal->lon);
  start->f = start->g + start->h;
  pairing_heap *open_list = init_heap();
  add_element(open_list, start);
  node *current;

  /* A star algorithm */
  while (open_list->size != 0) {
    current = extract_min(open_list);

    /* if the distance to goal is less than 1 meter then reconstruct path */
    if (vincent_inv_dist(current->lat, current->lon, goal->lat, goal->lon) < 1.0) {
      dyn_array_node *output = reconstruct_path(current);
      double output_distance = output->nodes[0]->g;
      free(closed_list->nodes);
      free(closed_list);
      clean_heap(open_list);
      free(output);
      return output_distance;
    }
    /* Move current node from open_list to closed_list */
    current->f = -1;
    /* Count number of neighbours and check if they exied in closed_list */
    dyn_array_node *neighbour_list = make_neighbours_list(current, nodes);
    for (size_t i = 0; i < neighbour_list->items; ++i) {
      if (neighbour_list->nodes[i]->f == -1 || heap_contains(open_list, current)) {
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
*@brief This function makes the list of neighbours to each node
*@param[in] "node *current" this is the node A* is currently working on
*@param[in] "node *nodes" The array of all streetpoints
*@return "neighbour_list" returns a dynamic array with the neighbours to a singe point
*/
dyn_array_node *make_neighbours_list(node *current, node *nodes) {
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

/**
*@brief This function reconstructs the path from the start node to the goal node
*@param[in] "node *end" The end node
*@return "total_path" The path that has been determined to be the fastest one
*/
dyn_array_node *reconstruct_path(node *end) {
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