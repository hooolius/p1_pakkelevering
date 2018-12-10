#include "parser_addresses.h"
#include "cJSON.c"
#include "cJSON.h"

void parser_addreses(struct address *searches) {
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
    printf("Searches : 1 %d",searches[0].id);
    convert_to_array(data, searches);
}

void convert_to_array(char *text, struct address *searches) {
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
                printf("address: %s",addresses[j].tags.street);
            }
        }
    }
}

int is_in_array(char input_streetname[], char input_housenumber[], struct address *searches) {
    for (int k = 0; k < 20; ++k) {
        if (strcmp(input_streetname, searches[k].tags.street) == 0) {
            if (strcmp(input_housenumber, searches[k].tags.house_number) == 0) {
                return 1;
            }
        }
    }
    return 0;
}
