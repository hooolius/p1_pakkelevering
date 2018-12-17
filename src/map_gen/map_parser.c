#include "map_parser.h"
#include "cJSON.h"

void search_and_parse_points(cJSON *json, struct point *map_points);

int sorter_function(const void *a, const void *b);

void search_and_parse_streets(cJSON *json, struct point map_points[]);

int binary_searcher(double input, struct point *map_points, int array_len);

void pointer_writer(struct point *map_points, int array_key, int old_array_key);

int is_written(struct point point, int array_key, int old_array_key);

/**
*@brief Updates the data from the map file using cJSOM
*@param[in] "point *map_points" The array of structs the contains the map data.
*/
void map_parser(struct point *map_points) {
  /*Terms:
   *  Points: A representation of a geographical point.*/
  cJSON *json = NULL;
  int i = 0;
  long len;
  char *data = NULL;
  FILE *paddress_file;
  paddress_file = fopen("map_data.json", "rb");

  /*Start of standard modification of file to make it capable of JSON parsing*/
  if (paddress_file == NULL) {
    printf("File not found in map parser\n");
    exit(-1);
  }
  fseek(paddress_file, 0, SEEK_END);
  len = ftell(paddress_file);
  fseek(paddress_file, 0, SEEK_SET);


  data = (char *) malloc(len + 1);
  fread(data, 1, len, paddress_file);
  data[len] = '\0';
  fclose(paddress_file);
  /*End of standard modification of file to make it capable of JSON parsing*/

  /*Calls the cJSON libary parser function*/
  json = cJSON_Parse(data);

  if (json == NULL) {
    printf("Error before: [%s]\n", cJSON_GetErrorPtr());
    exit(-1);
  }
  else {

    /*Calls the parsing functions*/
    search_and_parse_points(json, map_points);
    search_and_parse_streets(json, map_points);
  }
  free(data);

}

/**
*@brief Searches for a specific map node
*@param[in] data[] a string that contains a certain map node.
*@param[in] "point *map_points" The array of structs that contains the map data
*/
void search_and_parse_points(cJSON *json, struct point *map_points) {
  const cJSON *points = NULL;
  const cJSON *json_point = NULL;
  int i = 0, j = 1;

  points = cJSON_GetObjectItemCaseSensitive(json, "points");
  i = points_counter();
  /*Uses cJSON libary function to construct an array of all JSON points (Points being coordinates)*/

  cJSON_ArrayForEach(json_point, points) {
    map_points[j].id = cJSON_GetObjectItemCaseSensitive(json_point, "id")->valuedouble;
    map_points[j].lat = cJSON_GetObjectItemCaseSensitive(json_point, "lat")->valuedouble;
    map_points[j].lon = cJSON_GetObjectItemCaseSensitive(json_point, "lon")->valuedouble;
    j++;
  }
  /*Sorts the array of points to make searching faster later.*/
  qsort(map_points, i, sizeof(map_points[1]), sorter_function);

}

/**
*@brief Counts the amount of nodes in the JSON map file
*@return Returns the amount of nodes in the JSON map file
*/
int points_counter() {
  /*Counts points within the JSON file*/
  long len;
  char *data = NULL;
  FILE *paddress_file;
  const cJSON *json;
  const cJSON *points = NULL;
  const cJSON *json_point = NULL;
  int i = 0;

  paddress_file = fopen("map_data.json", "rb");

  /*Start of standard modification of file to make it capable of JSON parsing*/
  if (paddress_file == NULL) {
    printf("File not found\n");
    exit(-1);
  }
  fseek(paddress_file, 0, SEEK_END);
  len = ftell(paddress_file);
  fseek(paddress_file, 0, SEEK_SET);

  data = (char *) malloc(len + 1);
  fread(data, 1, len, paddress_file);
  data[len] = '\0';
  json = cJSON_Parse(data);

  points = cJSON_GetObjectItemCaseSensitive(json, "points");
  cJSON_ArrayForEach(json_point, points) {
    i++;
  }
  fclose(paddress_file);
  //free(data);
  return i;
}

/**
*@brief Sorts all the nodes in the map file after node id 
*/
int sorter_function(const void *a, const void *b) {
  /*Qsort helper function.*/
  struct point *ia = (struct point *) a;
  struct point *ib = (struct point *) b;
  if (ia->id > ib->id) {
    return 1;
  }
  else if (ia->id < ib->id) {
    return -1;
  }
  return 0;

}

/**
*@brief Function passes streets, and connects the points, so all the points know what points they are connected to. 
*@param[in] *data Contains all the data from the map file
*@param[in] "points *map_points" The array of structs where all the data is copied into
*/
void search_and_parse_streets(cJSON *json, struct point *map_points) {

  /*Function passes streets, and connects the points, so all the points know what points they are connected to.*/
  const cJSON *road_points = NULL;
  const cJSON *road_point = NULL;
  const cJSON *roads = NULL;
  const cJSON *road = NULL;
  int array_len = 0, array_key, old_array_key = 0;

  if (json == NULL) {
    printf("Error before: [%s]\n", cJSON_GetErrorPtr());

  }
  else {
    array_len = points_counter();
    /*Itterates through the JSON file*/
    roads = cJSON_GetObjectItemCaseSensitive(json, "roads");
    cJSON_ArrayForEach(road, roads) {
      /*Finds the elements within the JSON file, and links points.*/
      road_points = cJSON_GetObjectItemCaseSensitive(road, "nodes");
      cJSON_ArrayForEach(road_point, road_points) {
        /*To make sure all points are connected the following steps are done:
         * Binary_search outputs the corresponding array__key to the id of the point.
         * If the old_array_key == 0, the array_key is the first within the road.
         * */
        array_key = binary_searcher(road_point->valuedouble, map_points, array_len);
        if (old_array_key != 0) {
          pointer_writer(map_points, array_key, old_array_key);
        }
        old_array_key = array_key;
      }

      old_array_key = 0;
    }
  }
}

/**
*@brief Connects the neighbours in the map data to eachother
*@param[in] "point *map_points" The array of structs that contains the map data
*@param[in] array_key The arra_key of the examined node
*@param[in] old_array_key The array key of the neighbour to the examined node.
*/
void pointer_writer(struct point *map_points, int array_key, int old_array_key) {
  /*Inputs the array_key and old_array key into the points.
   * The points gets connected to eachoter, by writing the array key into the struct,
   * of the points to which its connected.*/

  if (!is_written(map_points[array_key], array_key, old_array_key)) {
    if (map_points[array_key].p1 == 0) {
      map_points[array_key].p1 = old_array_key;

    }
    else if (map_points[array_key].p2 == 0) {
      map_points[array_key].p2 = old_array_key;

    }
    else if (map_points[array_key].p3 == 0) {
      map_points[array_key].p3 = old_array_key;

    }
    else if (map_points[array_key].p4 == 0) {
      map_points[array_key].p4 = old_array_key;

    }
    else if (map_points[array_key].p5 == 0) {
      map_points[array_key].p5 = old_array_key;

    }
    else if (map_points[array_key].p6 == 0) {
      map_points[array_key].p6 = old_array_key;

    }
    else if (map_points[array_key].p7 == 0) {
      map_points[array_key].p7 = old_array_key;

    }
    else if (map_points[array_key].p8 == 0) {
      map_points[array_key].p8 = old_array_key;

    }
  }

  if (!is_written(map_points[old_array_key], array_key, old_array_key)) {
    if (map_points[old_array_key].p1 == 0) {
      map_points[old_array_key].p1 = array_key;

    }
    else if (map_points[old_array_key].p2 == 0) {
      map_points[old_array_key].p2 = array_key;
    }
    else if (map_points[old_array_key].p3 == 0) {
      map_points[old_array_key].p3 = array_key;

    }
    else if (map_points[old_array_key].p4 == 0) {
      map_points[old_array_key].p4 = array_key;

    }
    else if (map_points[old_array_key].p5 == 0) {
      map_points[old_array_key].p5 = array_key;

    }
    else if (map_points[old_array_key].p6 == 0) {
      map_points[old_array_key].p6 = array_key;
    }
    else if (map_points[old_array_key].p7 == 0) {
      map_points[old_array_key].p7 = array_key;
    }
    else if (map_points[old_array_key].p8 == 0) {
      map_points[old_array_key].p8 = array_key;
    }
  }
}

/**
*@brief Checks if the point is already written into the points
*@param[in] "point point" The array of structs that contains the neighbours
*@param[in] array_key The array key of the examined node
*@param[in] old_array_key the array key of the neighbour to the examined node
*/
int is_written(struct point point, int array_key, int old_array_key) {
  /*Checks if the point is already written into the points.*/
  if (point.p1 == array_key) {
    return 1;
  }
  else if (point.p2 == array_key) {
    return 1;
  }
  else if (point.p3 == array_key) {
    return 1;
  }
  else if (point.p4 == array_key) {
    return 1;
  }
  else if (point.p5 == array_key) {
    return 1;
  }
  else if (point.p6 == array_key) {
    return 1;
  }
  else if (point.p7 == array_key) {
    return 1;
  }
  else if (point.p8 == array_key) {
    return 1;
  }
  else if (point.p1 == old_array_key) {
    return 1;
  }
  else if (point.p2 == old_array_key) {
    return 1;
  }
  else if (point.p3 == old_array_key) {
    return 1;
  }
  else if (point.p4 == old_array_key) {
    return 1;
  }
  else if (point.p5 == old_array_key) {
    return 1;
  }
  else if (point.p6 == old_array_key) {
    return 1;
  }
  else if (point.p7 == old_array_key) {
    return 1;
  }
  else if (point.p8 == old_array_key) {
    return 1;
  }
  return 0;
}

/**
*@brief Searches binay for a certain map node
*@param[in] input A certain node from the map file
*@param[in] "point *map_points" The array of structs that contains the map data
*@param[in] "array_len" The length of the array
*/
int binary_searcher(double input, struct point *map_points, int array_len) {
  int first;
  int middle;

  first = 0;
  middle = (first + array_len) / 2;

  while (first <= array_len) {
    if (map_points[middle].id < input) {
      first = middle + 1;
    }
    else if (map_points[middle].id == input) {
      return middle;
    }
    else {
      array_len = middle - 1;
    }
    middle = (first + array_len) / 2;
  }
}
