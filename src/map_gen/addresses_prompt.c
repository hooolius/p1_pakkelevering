#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "addresses_prompt.h"

#define DEBUG 1

void addresses_prompt(dyn_array_address *searches) {
  int i = 0, number_of_packages = 0, j = 1;
  char check_for_end[50], end[] = "END", input_choice[2], manual_check[] = "1", document_check[] = "2", newline_find;
  struct address *current_searches = calloc(1, sizeof(struct address));
  if (DEBUG != 1) {
    printf("Hello there! - I need to know if you want to insert the addresses manually or using a document."
           "\nPress (1) for typing them in yourself and press (2) for using a document\n");
    scanf("%s", input_choice);
    if (strcmp(input_choice, manual_check) == 0) {
      printf("You have chosen to type in the addresses yourself\n "
             "When you are done typing your addresses type 'END' to end the process of typing in addresses \n");

      while (strcmp(check_for_end, end) != 0) {
        printf("Please enter the streetname streetname (Element number %d)\n", j);
        scanf("  %[^\n]s  ", check_for_end);

        if (0 != strcmp(check_for_end, end)) {
          strcpy(current_searches->tags.street, check_for_end);
          printf("Please enter the housenumber (Element number %d)\n", j);
          scanf("%s", current_searches->tags.house_number);
          searches = add_address_to_end_a(searches, *current_searches);
          i++;
          j++;
          number_of_packages++;
        }
      }

    }
    else if (strcmp(input_choice, document_check) == 0) {

      FILE *pinput_file;
      pinput_file = fopen("leveringsfil.txt", "r");

      if (pinput_file == NULL) {
        printf("Input file not found");
        exit(-1);
      }

      /*Cound the number of lines in the txt file*/
      while (!feof(pinput_file)) {
        newline_find = fgetc(pinput_file);
        if (newline_find == '\n') {
          ++number_of_packages;
        }
      }

      rewind(pinput_file);
      for (i = 0; i < number_of_packages; i++) {
        fscanf(pinput_file, " %[A-Za-z ], %[A-Za-z], %[0-9], %[A-Za-z-], %[0-9], %[A-Za-z].",
               current_searches->tags.city, current_searches->tags.country,
               current_searches->tags.house_number, current_searches->tags.muncipality,
               current_searches->tags.postcode, current_searches->tags.street);
        searches = add_address_to_end_a(searches, *current_searches);
      }


    }
    else {
      printf("Invalid input - Try again\n");
    }
  }
  else {
    printf("\n\tDEBUG MODE \n");
    strcpy(current_searches->tags.street, "Badehusvej");
    strcpy(current_searches->tags.house_number, "13");
    searches = add_address_to_end_a(searches, *current_searches);
    strcpy(current_searches->tags.street, "Deltavej");
    strcpy(current_searches->tags.house_number, "30");
    searches = add_address_to_end_a(searches, *current_searches);
  }
  parser_addreses(searches->addresses);
}
