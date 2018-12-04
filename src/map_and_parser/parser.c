#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cJSON.c"
#include "cJSON.h"

void convert_to_array(char *text);

void parse_file();

struct tags {
    char city[30];
    char street[30];
    char country[5];
    char house_number[5];
    char muncipality[20];
    char postcode[4];
};

struct address {
    int id;
    double lat;
    double lon;
    struct tags tags;

} address;

struct address parser(struct address curr_address, FILE *paddress_file, char search[], int line);

int is_in_array(char input_streetname[], char input_housenumber[]);

int main() {

    FILE *paddress_file;
    paddress_file = fopen("addresses.json", "rb");

    parse_file();

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
    struct address addresses[20];
    int j = 0;

    json = cJSON_Parse(text);

    if (json == NULL) {
        printf("Error before: [%s]\n", cJSON_GetErrorPtr());

    } else {
        elements = cJSON_GetObjectItemCaseSensitive(json, "elements");
        cJSON_ArrayForEach(element, elements) {
            tags = cJSON_GetObjectItemCaseSensitive(element, "tags");

            if (is_in_array(cJSON_GetObjectItemCaseSensitive(tags, "addr:street")->valuestring,
                            cJSON_GetObjectItemCaseSensitive(tags, "addr:housenumber")->valuestring) == 1) {

                addresses[j].lat = cJSON_GetObjectItem(element, "lat")->valuedouble;
                addresses[j].lon = cJSON_GetObjectItem(element, "lon")->valuedouble;

                strcpy(addresses[j].tags.street,
                       cJSON_GetObjectItemCaseSensitive(tags, "addr:street")->valuestring);
                strcpy(addresses[j].tags.country,
                       cJSON_GetObjectItemCaseSensitive(tags, "addr:country")->valuestring);
                strcpy(addresses[j].tags.muncipality,
                       cJSON_GetObjectItemCaseSensitive(tags, "addr:municipality")->valuestring);
                strcpy(addresses[j].tags.city,
                       cJSON_GetObjectItemCaseSensitive(tags, "addr:city")->valuestring);
                strcpy(addresses[j].tags.house_number,
                       cJSON_GetObjectItemCaseSensitive(tags, "addr:housenumber")->valuestring);

                strcpy(addresses[j].tags.postcode,
                       cJSON_GetObjectItemCaseSensitive(tags, "addr:postcode")->valuestring);

                printf("Succes you git: Streetnam: %s \n Housenumber %s \n "
                       "Long: %lf \n"
                       "Lat: %lf \n", addresses[j].tags.street,
                       addresses[j].tags.house_number,addresses[j].lon,addresses[j].lat);
                j++;
            }
        }
    }
}
int is_in_array(char input_streetname[], char input_housenumber[]) {
    struct address searches[20];
    strcpy(searches[0].tags.street, "Abelsvej");
    strcpy(searches[0].tags.house_number, "2");
    strcpy(searches[1].tags.street, "James Tobins Alle");
    strcpy(searches[1].tags.house_number, "2");
    strcpy(searches[2].tags.street, "Jernbanegade");
    strcpy(searches[2].tags.house_number, "10");
    strcpy(searches[3].tags.street, "Borgmestervæeget");
    strcpy(searches[3].tags.house_number, "1");
    strcpy(searches[4].tags.street, "Vesterled");
    strcpy(searches[4].tags.house_number, "22");
    strcpy(searches[5].tags.street, "Kastetvej");
    strcpy(searches[5].tags.house_number, "117");
    strcpy(searches[6].tags.street, "Bobsvinvej");
    strcpy(searches[6].tags.house_number, "2");
    strcpy(searches[7].tags.street, "Brandstrupsgade");
    strcpy(searches[7].tags.house_number, "10");
    strcpy(searches[8].tags.street, "Danmarksgade");
    strcpy(searches[8].tags.house_number, "49");
    strcpy(searches[9].tags.street, "Fyensgade");
    strcpy(searches[9].tags.house_number, "54");
    strcpy(searches[10].tags.street, "Herskindsgade");
    strcpy(searches[10].tags.house_number, "20");

    for (int k = 0; k < 10; ++k) {
        if (strcmp(input_streetname, searches[k].tags.street) == 0) {
            if (strcmp(input_housenumber, searches[k].tags.house_number) == 0) {
                return 1;
            }
        }
    }
    return 0;
}
