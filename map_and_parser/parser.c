#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cJSON.c"
#include "cJSON.h"

int lines_counter(FILE *paddress_file);

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

struct address parser(struct address curr_address,FILE *paddress_file,char search[],int line);

int main() {
    const cJSON *id     = NULL;
    const cJSON *lat    = NULL;
    const cJSON *lon    = NULL;
    const cJSON *city   = NULL;


    FILE *paddress_file;
    paddress_file = fopen("../src/map_and_parser/addresses.json","r");
    int lines = lines_counter(paddress_file);
    printf("Number of lines: %d \n",lines);
    struct address* addresses = malloc(lines * sizeof(struct address));

    if (paddress_file == NULL) {
        printf("ERROR ON LOADING FILE");
        return 0;
    }

    //printf("Number of lines: %d",lines);
    rewind(paddress_file);

    cJSON *json = cJSON_Parse(paddress_file);

    city = cJSON_GetObjectItemCaseSensitive(json, "city");
    if (cJSON_IsString(city) && (city->valuestring != NULL))
    {
        printf("Checking monitor \"%s\"\n", city->valuestring);
    }

    printf("%s",city);

    //for (int j = 0; j < lines; ++j) {
    //    parser(addresses[j],paddress_file,"James Tobins Alle",j);
    //}

    printf("Test of one %s",addresses[1].street);

    return 0;
}







struct address parser(struct address curr_address,FILE *paddress_file, char search[],int line) {
        fscanf(paddress_file,"      \"type\": \"node\",\n"
                             "      \"id\": %d,\n"
                             "      \"lat\": %lf,\n"
                             "      \"lon\": %lf,\n"
                             "      \"tags\": {\n"
                             "        \"addr:city\": \" %[a-zA-Z ] \",\n"
                             "        \"addr:country\": \" %s\",\n"
                             "        \"addr:housenumber\": \" %d\",\n"
                             "        \"addr:municipality\": \" %[a-zA-Z ]\",\n"
                             "        \"addr:postcode\": \" %d\",\n"
                             "        \"addr:street\": \" %[a-zA-Z ] \"",&curr_address.id,&curr_address.lat,&curr_address.lon,curr_address.city,curr_address.country,&curr_address.house_number,curr_address.muncipality,&curr_address.postcode,curr_address.street);

    //fscanf(paddress_file, "id\": %d,\n",&curr_address.id);
    //fscanf(paddress_file, "lat\": %lf,\n",&curr_address.lat);
    //fscanf(paddress_file, "lon\": %lf,\n",&curr_address.lat);
    //fscanf(paddress_file, "addr:city\": \" %[a-zA-Z ]\",\n",curr_address.country);
    //fscanf(paddress_file, "addr:country\": \" %s\",\n",curr_address.city);
    //fscanf(paddress_file, "addr:housenumber\": \" %d \",\n",&curr_address.house_number);
    //fscanf(paddress_file, "addr:municipality\": \" %s \",\n",curr_address.muncipality);
    //fscanf(paddress_file, "addr:postcode\": \" %d\" ,\n",&curr_address.postcode);
    //fscanf(paddress_file, "addr:street\": \" %[a-zA-Z ] \",\n\"",curr_address.street);

    //printf("Test: %s",curr_address.street);
    return curr_address;
}


int lines_counter(FILE *paddress_file){
    int lines=0;
    while (!feof(paddress_file)) {
        char c = fgetc(paddress_file);
        if (c =='\n') {
            lines++;
        }
    }
    return lines;
}