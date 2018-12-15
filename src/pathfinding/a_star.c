#include "a_star.h"

node *convert_points_to_nodes(int number_of_points, point *points);

node *convert_point_to_node(point *the_point);

int count_elements_in_list(dyn_array_node *list);

/* Function copys one node to a other node */
void copy_node_to_node(node *destination, node *source);

node *find_min_array(dyn_array_node *list);

dyn_array_node *reconstruct_path(node *end, double start);

dyn_array_node *make_neighbours_list(node current, node *nodes);

int contains(dyn_array_node *closed_list, node item);

int cmp_func(const void *a, const void *b);


/* A star setup */
dyn_array_node *a_star(point *start_p, point *goal_p, point *points) {
  int number_of_points = 1;
  //FILE *fil = fopen("output.txt", "w");
  printf("ID,LAT,LON\n");
  while (points[number_of_points].id != 0) {
    //fprintf(fil,"%lf, %lf, %lf\n",points[number_of_points].id, points[number_of_points].lat, points[number_of_points].lon);
    ++number_of_points;
  }
  printf("START LAT: %lf LON: %lf\n", start_p->lat, start_p->lon);
  printf("GOAL LAT: %lf LON: %lf\n", goal_p->lat, goal_p->lon);
  /* Debug code */
  node *start = convert_point_to_node(start_p);
  node *goal = convert_point_to_node(goal_p);
  node *nodes = convert_points_to_nodes(number_of_points, points);
  printf("%d", number_of_points);
  /*for (int j = 1; j < number_of_points; ++j) {
    printf("ID:%.0lf LAT: %.0lf LON: %.0lf\n", nodes[j].id, nodes[j].lat, nodes[j].lon);
  }*/

  int count = 0;
  dyn_array_node *closed_list = make_dyn_array_n(100);
  start->g = 0;
  start->h = vincent_inv_dist(start->lat, start->lon, goal->lat, goal->lon);
  start->f = start->g + start->h;
  pairing_heap *open_list = init_heap();

  //dyn_array_node *open_list = make_dyn_array_n(10);
  //heap_clear(open_list);
  //add_node_to_end_n(open_list, *start);
  add_element(open_list, start);
  //dyn_array_node *came_from = make_dyn_array_n(100);;
  //node *current;
  node *current;
  node neighbour;
  //printf("ID,LAT,LON\n");
  //heap_insert(open_list, start);
  //heap_insert(open_list, start);
  /* A star algoritme */
  int q = 0;
  while (open_list->size != 0) {
    q++;
    /* Take node with the smallest value and copy to current */
    //copy_node_to_node(current, find_min_array(open_list));
    //copy_node_to_node(current, extract_min(open_list));
    current = extract_min(open_list);

    if (current == NULL) {
      printf("%d current is null \n", q);
    }
    //printf("G: %lf H: %lf F: %lf\n", current->g, current->h, current->f);
    /* if the distance to goal is less than 1 meter then reconstruct path */
    if (vincent_inv_dist(current->lat, current->lon, goal->lat, goal->lon) < 1.0) {
      printf("i did the thing\n");
      //free(closed_list);
      //free(open_list);
      return reconstruct_path(current, start->id);
    }
    /* Move current node from open_list to closed_list */
    //heap_delete(open_list, current);
    //delete_node_n(open_list, current);
    add_node_to_end_n(closed_list, *current);
    /* Count number of neighbours and check if they exied in closed_list */
    dyn_array_node *neighbour_list = make_neighbours_list(*current, nodes);
    for (size_t i = 0; i < neighbour_list->items; ++i) {
      //if (contains(closed_list, neighbour_list->nodes[i]) || contains(open_list, neighbour_list->nodes[i])) {
      if (contains(closed_list, neighbour_list->nodes[i]) || heap_contains(open_list, &neighbour_list->nodes[i])) {
        continue;
      }
      heap_node *curr_value = find(open_list, &neighbour_list->nodes[i]);
      /* Neighbour is calculated and put in open_list and current is put in came_from */
      //neighbour_list->nodes[i].g = current->g +
      //                             vincent_inv_dist(current->lat, current->lon, neighbour_list->nodes[i].lat,
      //                                              neighbour_list->nodes[i].lon);
      //neighbour_list->nodes[i].h = vincent_inv_dist(neighbour_list->nodes[i].lat, neighbour_list->nodes[i].lon,
      //                                              goal->lat, goal->lon);
      //neighbour_list->nodes[i].f = neighbour_list->nodes[i].h + neighbour_list->nodes[i].g;
      neighbour_list->nodes[i].g = current->g +
                                   vincent_inv_dist(current->lat, current->lon, neighbour_list->nodes[i].lat,
                                                    neighbour_list->nodes[i].lon);
      neighbour_list->nodes[i].h = vincent_inv_dist(neighbour_list->nodes[i].lat, neighbour_list->nodes[i].lon,
                                                    goal->lat, goal->lon);
      neighbour_list->nodes[i].f = neighbour_list->nodes[i].h + neighbour_list->nodes[i].g;
      //heap_insert(open_list, neighbour_list.nodes[i]);
      neighbour_list->nodes[i].came_from = current;
      if(neighbour_list->nodes[i].id == 60117825.000000) {
        printf("\n");
      }
      add_element(open_list, &neighbour_list->nodes[i]);
      //add_node_to_end_n(open_list, neighbour_list->nodes[i]);
      //add_node_to_end_n(came_from, *current);
    }
    free(neighbour_list);
  }
  printf("A star: No path exiting program!\n");
  exit(-1);
}

node *find_min_array(dyn_array_node *list) {
  qsort(list->nodes, list->items, sizeof(node), cmp_func);

  return &list->nodes[0];
}

int cmp_func(const void *a, const void *b) {
  int res;
  node *aa = (node *) a;
  node *bb = (node *) b;

  if (aa->f > bb->f) {
    res = -1;
  } else if (aa->f == aa->f) {
    res = 0;
  } else {
    res = 1;
  }
  return res;
}

dyn_array_node *make_neighbours_list(node current, node *nodes) {
  /* Follow pointers and count number of neighbours */
  /* return a pointer from a memory space where neighbours are stored */
  dyn_array_node *neighbour_list = make_dyn_array_n(6);
  if (current.p1 != 0) {
    neighbour_list = add_node_to_end_n(neighbour_list, nodes[current.p1]);
  }
  if (current.p2 != 0) {
    neighbour_list = add_node_to_end_n(neighbour_list, nodes[current.p2]);
  }
  if (current.p3 != 0) {
    neighbour_list = add_node_to_end_n(neighbour_list, nodes[current.p3]);
  }
  if (current.p4 != 0) {
    neighbour_list = add_node_to_end_n(neighbour_list, nodes[current.p4]);
  }
  if (current.p5 != 0) {
    neighbour_list = add_node_to_end_n(neighbour_list, nodes[current.p5]);
  }
  if (current.p6 != 0) {
    neighbour_list = add_node_to_end_n(neighbour_list, nodes[current.p6]);
  }
  return neighbour_list;
}

/* Function copys one node to a other node */
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
  destination->came_from = source->came_from;
}

int count_elements_in_list(dyn_array_node *list) {
  return list->items;
}

int contains(dyn_array_node *closed_list, node item) {
  int res = 0;
  for (int i = 0; i < closed_list->items; ++i) {
    if (closed_list->nodes[i].id == item.id) {
      res = 1;
      break;
    }
  }
  return res;
}

dyn_array_node *reconstruct_path(node *end, double start) {
  dyn_array_node *total_path = make_dyn_array_n(100);
  int i = 0;
  node *current = end;
  printf("ID,LAT,LON\n");
  while (current->came_from != NULL) {
    add_node_to_end_n(total_path, *current);
    current = current->came_from;
    printf("%lf,%lf,%lf\n", current->id, current->lat, current->lon);
    i++;
  }
  return total_path;
}

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
  }
  return nodes;
}

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
  return node;
}
