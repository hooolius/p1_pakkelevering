#include <stdio.h>
#include <stdlib.h>
#include "main_config.h"
#include "dynamic_array.h"
#include "cleaner.h"
#include "a_star.h"
#include "addresses_prompt.h"
#include "parser_addresses.h"
#include "map_parser.h"
#include "address_to_point_calc.h"
#include "held_karp.h"
#include "ioconverter.h"

typedef struct point point;

void print_help();

int main(int argc, char *argv[]) {

  if (argc >= 2) {
    for (int i = 0; i < argc; i++) {
      if (strcmp("--version", argv[i]) == 0 || strcmp("--Version", argv[i]) == 0) {
        printf("Version %d.%d \n",
               p1_pakkelevering_VERSION_MAJOR, p1_pakkelevering_VERSION_MINOR);
      }
    }
  }

  if (argc >= 2) {
    for (int i = 0; i < argc; i++) {
      if (strcmp("--help", argv[i]) == 0 || strcmp("-h", argv[i]) == 0) {
        print_help();
        exit(0);
      }
    }
  }

  int verbose = 0;
  if (argc >= 2) {
    for (int i = 0; i < argc; i++) {
      if (strcmp("-v", argv[i]) == 0 || strcmp("-V", argv[i]) == 0) {
        verbose = 1;
      }
    }
  }

  FILE *input = NULL;
  if (argc >= 2) {
    for (int i = 1; i < argc; i++) {
      input = fopen(argv[i], "r");
      if (input != NULL) {
        break;
      }
    }
  }

  dyn_array_address *searches = make_dyn_array_a(2);
  point *map_points = calloc(points_counter(), sizeof(point));

  addresses_prompt(searches, input);

  if (verbose) {
    printf("Map parsed started \n");
  }
  map_parser(map_points);
  addresses_to_point_calc(searches, map_points);
  if (verbose) {
    printf("Map parsed successfully \n");
  }

  if (verbose) {
    printf("A* started \n");
  }
  int **matrix = astar_to_matrix_converter(searches, map_points);
  if (verbose) {
    printf("A* finished successfully \n");
  }

  int min_cost = 0;
  int plan[searches->items + 1];

  if (verbose) {
    printf("Held-Karp started \n");
  }
  min_cost = held_karp(matrix, searches->items, 0, plan);
  if (verbose) {
    printf("Held-Karp finished successfully \n");
  }

  printf("length = %.2lf; \n", (double) min_cost / 1000);
  for (int i = 0; i < searches->items + 1; i++) {
    printf("var marker%d = L.marker([%lf,%lf]).addTo(mymap).bindPopup(\" <b>Punkt nummer %d \").openPopup(); \n", i,
           searches->addresses[plan[i]].lat, searches->addresses[plan[i]].lon, i);
  }

  printf("$('#input').hide();\n"
         "document.getElementById('result').style.display=\"block\";\n"
         "document.getElementById('result_length').innerHTML = \"Total distance: \" + String(length);\n");
  printf("document.getElementById('result_trip').innerHTML = \" ");
  for (int j = 0; j < searches->items + 1; ++j) {

    printf("%d %s %s <br>",j, searches->addresses[plan[j]].tags.street, searches->addresses[plan[j]].tags.house_number);
    if (j > 0 && j < searches->items + 1) {
      printf("\" + \"");
    }
    if (j == searches->items) {
      printf("\"");
    }
  }
  free(searches);

  printf("\n");
  return 0;
}

void print_help() {
  printf("usage: p1_pakkelevering input_file\n");
  printf("\toptions:\n");
  printf("\t -h --help: Display this message\n");
  printf("\t -v -V: Verbose mode, print progress\n");
  printf("\t --version --Version: Print version number\n");
}
