#include "parser_addresses.h"
#include "cJSON.c"
#include "cJSON.h"


int is_in_array(char input_streetname[], char input_housenumber[], dyn_array_address *searches);

void convert_to_array(char *data, dyn_array_address*searches);

void parser_addreses(dyn_array_address *searches) {
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
    convert_to_array(data, searches);
}

void convert_to_array(char *data, dyn_array_address *searches) {
    cJSON *json = NULL;
    const cJSON *element = NULL;
    const cJSON *elements = NULL;
    cJSON *tags = NULL;
    struct address addresses[searches->items];
    int j = 0;

    json = cJSON_Parse(data);

    if (json == NULL) {
        printf("Error before: [%s]\n", cJSON_GetErrorPtr());

    } else {
        elements = cJSON_GetObjectItemCaseSensitive(json, "elements");
        cJSON_ArrayForEach(element, elements) {
            tags = cJSON_GetObjectItemCaseSensitive(element, "tags");

            if (is_in_array(cJSON_GetObjectItemCaseSensitive(tags, "addr:street")->valuestring,
                            cJSON_GetObjectItemCaseSensitive(tags, "addr:housenumber")->valuestring, searches) == 1) {

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
                j++;
            }
        }
    }
    for (int i = 0; i < searches->items; ++i) {
        strcpy(searches->addresses[i].tags.street, addresses[i].tags.street);
        strcpy(searches->addresses[i].tags.house_number, addresses[i].tags.house_number);
        strcpy(searches->addresses[i].tags.country, addresses[i].tags.country);
        strcpy(searches->addresses[i].tags.muncipality, addresses[i].tags.muncipality);
        strcpy(searches->addresses[i].tags.postcode, addresses[i].tags.postcode);
        searches->addresses[i].lat = addresses[i].lat;
        searches->addresses[i].lon = addresses[i].lon;
    }
}

int is_in_array(char input_streetname[], char input_housenumber[], dyn_array_address *searches) {
    for (int k = 0; k < searches->items; k++) {
        if (strcmp(input_streetname, searches->addresses[k].tags.street) == 0) {
            if (strcmp(input_housenumber, searches->addresses[k].tags.house_number) == 0) {
                return 1;
            }
        }
    }
    return 0;
}
