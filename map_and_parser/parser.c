#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "jsmn.h"
int lines_counter(FILE *str);

struct address {
    int id;
    double lat;
    double lon;
    char city[30];
    char country[5];
    int house_number;
    char muncipality[20];
    int postcode;
    char street[30];
} address;

struct address parser(struct address curr_address,FILE *file,char search[],int line);

int main() {
    FILE *file;
    file = fopen("../src/map_and_parser/addresses.json","r");
    int lines = lines_counter(file);
    printf("Number of lines: %d \n",lines);


    if (file == NULL) {
        printf("ERROR ON LOADING FILE");
        return 0;
    }
    //struct address addresses[lines];
    //printf("Number of lines: %d",lines);




    //for (int j = 0; j < lines; ++j) {
     //   addresses[j] = parser(addresses[j],file,"James Tobins Alle",j);
    //}

    return 0;
}

struct address parser(struct address curr_address,FILE *file, char search[],int line) {
    fscanf(file, "id\": %d,\n",&curr_address.id);
    fscanf(file, "lat\": %lf,\n",&curr_address.lat);
    fscanf(file, "lon\": %lf,\n",&curr_address.lon);
    fscanf(file, "addr:city\": \" %[a-zA-Z ]\",\n",curr_address.country);
    fscanf(file, "addr:country\": \" %s\",\n",curr_address.city);
    fscanf(file, "addr:housenumber\": \" %d \",\n",&curr_address.house_number);
    fscanf(file, "addr:municipality\": \" %s \",\n",curr_address.muncipality);
    fscanf(file, "addr:postcode\": \" %d\" ,\n",&curr_address.postcode);
    fscanf(file, "addr:street\\\": \\\" %[a-zA-Z ] \\\",\\n\"",curr_address.street);

    return curr_address;
}


int lines_counter(FILE *file){
    int lines=0;
    while (!feof(file)) {
        char c = fgetc(file);
        if (c =='\n') {
            lines++;
        }
    }
    rewind(file);
    return lines;
}