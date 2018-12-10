#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "addresses_prompt.h"


void addresses_prompt(struct address *searches) {
    int i = 0, number_of_packages = 0, j = 1;
    char check_for_end[50], end[] = "END", input_choice[2], manual_check[] = "1", document_check[] = "2", newline_find;
    //searches = calloc(20, sizeof(struct address));
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
                strcpy(searches[i].tags.street, check_for_end);
                printf("Please enter the housenumber (Element number %d)\n", j);
                scanf("%s", searches[i].tags.house_number);
                i++;
                number_of_packages++;
                j++;
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
                   searches[i].tags.city, searches[i].tags.country,
                   searches[i].tags.house_number, searches[i].tags.muncipality,
                   searches[i].tags.postcode, searches[i].tags.street);
        }


    }
    else {
        printf("Invalid input - Try again\n");
    }
    printf("Got this far?");
    parser_addreses(searches);
    printf("lat is: %lf \n", searches[0].lat);
}
