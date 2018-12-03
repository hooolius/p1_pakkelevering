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
    char house_number[5];
    char muncipality[20];
    char postcode[4];
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
    const cJSON *element = NULL;
    const cJSON *elements = NULL;
    cJSON *tags = NULL;
    char *test_string;
    struct address *addresses;
    int i = 1, j = 0;
    char test[50];
    int lines = lines_counter();
    char *search_street= "Abelsvej";
    char search_number[4];

    addresses = calloc(lines, sizeof(address));

    json = cJSON_Parse(text);

    if (json == NULL) {
        printf("Error before: [%s]\n", cJSON_GetErrorPtr());

    } else {
        elements = cJSON_GetObjectItemCaseSensitive(json, "elements");
        cJSON_ArrayForEach(element, elements) {
            //printf("Adresses %s Run: %d \n",addresses[i].tags.street,i);
            addresses[i].lat = cJSON_GetObjectItem(element, "lat")->valuedouble;
            addresses[i].lon = cJSON_GetObjectItem(element, "lon")->valuedouble;
            tags = cJSON_GetObjectItemCaseSensitive(element, "tags");

            strcpy(addresses[i].tags.street, cJSON_GetObjectItemCaseSensitive(tags, "addr:street")->valuestring);
            strcpy(addresses[i].tags.country, cJSON_GetObjectItemCaseSensitive(tags, "addr:country")->valuestring);
            strcpy(addresses[i].tags.muncipality,
                   cJSON_GetObjectItemCaseSensitive(tags, "addr:municipality")->valuestring);
            strcpy(addresses[i].tags.city, cJSON_GetObjectItemCaseSensitive(tags, "addr:city")->valuestring);
            strcpy(addresses[i].tags.house_number,
                   cJSON_GetObjectItemCaseSensitive(tags, "addr:housenumber")->valuestring);
            strcpy(addresses[i].tags.postcode, cJSON_GetObjectItemCaseSensitive(tags, "addr:postcode")->valuestring);
            /*printf("\n Streetname %s \n Muncipality %s \n Country %s \n City %s \n HouseNumber %s \n Postcode %s \n",
                   addresses[i].tags.street, addresses[i].tags.muncipality, addresses[i].tags.country,
                   addresses[i].tags.city, addresses[i].tags.house_number, addresses[i].tags.postcode);
            printf("lateral: %f \n", addresses[i].lat); */
        }
    }
    strcpy(search_number, "4");
    for (int j = 0; j < lines; ++j) {
        if (strcmp(search_street, addresses[j].tags.street) == 0) {
            if (strcmp(search_number, addresses[j].tags.house_number) == 0) {
                printf("Latitude %f \n "
                       "Longtitude %f \n", addresses[j].lat, addresses[j].lon);
            } else {
                printf("Street found, not right address \n");
            }
        } else {
             printf("Reached end, no such thing \n ");
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
