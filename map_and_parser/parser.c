#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cJSON.c"
#include "cJSON.h"

int lines_counter();

void convert_to_array(char *text);

void parse_file();

struct tags {
    char city[30];
    char country[5];
    int house_number;
    char muncipality[20];
    int postcode;
    char street[30];
};

struct address {
    int id;
    double lat;
    double lon;
    struct tags tags;

} address;

struct address parser(struct address curr_address, FILE *paddress_file, char search[], int line);

int main() {

    FILE *paddress_file;
    paddress_file = fopen("addresses.json", "rb");

    parse_file();
    int lines = lines_counter(paddress_file);
    printf("Number of lines: %d \n", lines);

    if (paddress_file == NULL) {
        printf("ERROR ON LOADING FILE");
        exit(-1);
    }

    //printf("Number of lines: %d",lines);
    rewind(paddress_file);

    //cJSON *json = cJSON_Parse(paddress_file);

    return 0;
}

void parse_file() {
    long len = 0;
    char *data = NULL;
    FILE *paddress_file;
    paddress_file = fopen("addresses.json", "rb");
    /* get the length */
    if (paddress_file == NULL) {
        printf("SHIT");
        exit(-1);
    }
    fseek(paddress_file, 0, SEEK_END);
    len = ftell(paddress_file);
    fseek(paddress_file, 0, SEEK_SET);


    data = (char *) malloc(len + 1);
    fread(data, 1, len, paddress_file);
    data[len] = '\0';
    fclose(paddress_file);


    convert_to_array(data);
}

void convert_to_array(char *text) {
    cJSON *json = NULL;
    cJSON *element = NULL;
    cJSON *elements = NULL;
    cJSON *tags = NULL;
    char *test_string;
    struct address *addresses;
    int i;
    char test[50];
    int lines = lines_counter();
    char search_street[100];
    int search_number;

    addresses = calloc(lines, sizeof(address));
    json = cJSON_Parse(text);

    if (!json) {
        printf("Error before: [%s]\n", cJSON_GetErrorPtr());

    } else {
        for (i = 0; i < lines; i++) {
            addresses[i].lat = cJSON_GetObjectItem(json, "lat")->valuedouble;
            addresses[i].lon = cJSON_GetObjectItem(json, "lon")->valuedouble;
            tags = cJSON_GetObjectItem(json, "tags");
            strcpy(addresses[i].tags.street, cJSON_GetObjectItem(tags, "addr:street")->valuestring);
            strcpy(addresses[i].tags.country, cJSON_GetObjectItem(tags, "addr:country")->valuestring);
            strcpy(addresses[i].tags.muncipality, cJSON_GetObjectItem(tags, "addr:municipality")->valuestring);
            strcpy(addresses[i].tags.city, cJSON_GetObjectItem(tags, "addr:city")->valuestring);
            addresses[i].tags.house_number = cJSON_GetObjectItem(tags, "addr:housenumber")->valueint;
            addresses[i].tags.postcode = cJSON_GetObjectItem(tags, "addr:postcode")->valueint;
        }
    }
    
    strcpy(search_street, "Abelsvej");
    search_number = 4;
    for (int j = 0; j < lines; ++j) {
        if (strcmp(search_street, addresses[j].tags.street) == 0 ) {
            if (search_number == addresses[j].tags.house_number) {
                printf("Latitude %f \n "
                       "Longtitude %f \n", addresses[j].lat, addresses[j].lon);
            } else{
                printf("Street found, not right address \n");
            }
        } else {
          //  printf("Reached end, no such thing");
        }
    }
}

int lines_counter() {
    FILE *paddress_file;
    paddress_file = fopen("addresses.json", "rb");
    int lines = 0;
    while (!feof(paddress_file)) {
        char c = fgetc(paddress_file);
        if (c == '\n') {
            lines++;
        }
    }
    return lines;
}


/*struct address parser(struct address curr_address, FILE *paddress_file, char search[], int line) {
    fscanf(paddress_file, "      \"type\": \"node\",\n"
                          "      \"id\": %d,\n"
                          "      \"lat\": %lf,\n"
                          "      \"lon\": %lf,\n"
                          "      \"tags\": {\n"
                          "        \"addr:city\": \" %[a-zA-Z ] \",\n"
                          "        \"addr:country\": \" %s\",\n"
                          "        \"addr:housenumber\": \" %d\",\n"
                          "        \"addr:municipality\": \" %[a-zA-Z ]\",\n"
                          "        \"addr:postcode\": \" %d\",\n"
                          "        \"addr:street\": \" %[a-zA-Z ] \"", &curr_address.id, &curr_address.lat,
           &curr_address.lon, curr_address.city, curr_address.country, &curr_address.house_number,
           curr_address.muncipality, &curr_address.postcode, curr_address.street);

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

}*/
