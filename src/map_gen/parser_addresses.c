#include "parser_addresses.h"
#include "cJSON.c"
#include "cJSON.h"


int is_in_array(char input_streetname[], char input_housenumber[], dyn_array_address *searches);


void convert_to_array(char *data, dyn_array_address *searches);

/**
*@brief Passes addresses from the adresses file using cJSON
*@param[in] "dyn_array_address *searches" These are the addresses asked for in the command prompt if chosen to manually type them
*/
void parser_addreses(dyn_array_address *searches) {
  long len = 0;
  char *data = NULL;
  FILE *paddress_file;
  paddress_file = fopen("addresses.json", "rb");
  /* get the length */
  if (paddress_file == NULL) {
    printf("File not found - Parser adddresses");
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
  free(data);
}

/**
*@brief Takes all the information from the JSON file that is needed and puts it into an array of structs
*@param[in] *data A sting that contains all the information from the input file
*@param[out] "dyn_array_address *searches" An array with the adresses wanted by the user 
*/
void convert_to_array(char *data, dyn_array_address *searches) {
  cJSON *json = NULL;
  const cJSON *element = NULL;
  const cJSON *elements = NULL;
  cJSON *tags = NULL;
  struct address addresses[searches->items];
  dyn_array_address *results = make_dyn_array_a(searches->items);
  int j = 0;

  json = cJSON_Parse(data);

  if (json == NULL) {
    printf("Error before: [%s]\n", cJSON_GetErrorPtr());

  }
  else {
    elements = cJSON_GetObjectItemCaseSensitive(json, "elements");
    cJSON_ArrayForEach(element, elements) {
      tags = cJSON_GetObjectItemCaseSensitive(element, "tags");

      if (is_in_array(cJSON_GetObjectItemCaseSensitive(tags, "addr:street")->valuestring,
                      cJSON_GetObjectItemCaseSensitive(tags, "addr:housenumber")->valuestring, searches) == 1) {
        struct address curr_address;

        curr_address.lat = cJSON_GetObjectItem(element, "lat")->valuedouble;
        curr_address.lon = cJSON_GetObjectItem(element, "lon")->valuedouble;
        //addresses[j].lat = cJSON_GetObjectItem(element, "lat")->valuedouble;
        //addresses[j].lon = cJSON_GetObjectItem(element, "lon")->valuedouble;
/*
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
  */
        strcpy(curr_address.tags.street,
               cJSON_GetObjectItemCaseSensitive(tags, "addr:street")->valuestring);
        strcpy(curr_address.tags.country,
               cJSON_GetObjectItemCaseSensitive(tags, "addr:country")->valuestring);
        strcpy(curr_address.tags.muncipality,
               cJSON_GetObjectItemCaseSensitive(tags, "addr:municipality")->valuestring);
        strcpy(curr_address.tags.city,
               cJSON_GetObjectItemCaseSensitive(tags, "addr:city")->valuestring);
        strcpy(curr_address.tags.house_number,
               cJSON_GetObjectItemCaseSensitive(tags, "addr:housenumber")->valuestring);

        strcpy(curr_address.tags.postcode,
               cJSON_GetObjectItemCaseSensitive(tags, "addr:postcode")->valuestring);

        j++;
        add_address_to_end_a(results, curr_address);
      }
    }
  }
  int q=0;
  for (int i = 0; i < searches->items; ++i) {
    if (i < results->items) {
      if (find_address_a(searches, results->addresses[i]) == 1) {
        //strcpy(searches->addresses[q].tags.street, addresses[q].tags.street);
        //strcpy(searches->addresses[q].tags.house_number, addresses[q].tags.house_number);
        //strcpy(searches->addresses[q].tags.country, addresses[q].tags.country);
        //strcpy(searches->addresses[q].tags.muncipality, addresses[q].tags.muncipality);
        //strcpy(searches->addresses[q].tags.postcode, addresses[q].tags.postcode);
        //searches->addresses[q].lat = addresses[q].lat;
        //searches->addresses[q].lon = addresses[q].lon;
        //q++;
      }
      else {
        printf("The address %s %s was not found. \n", searches->addresses[i].tags.street,
               searches->addresses[i].tags.house_number);
      }
    }
    else {
      printf("The address %s %s was not found. \n", searches->addresses[i].tags.street,
             searches->addresses[i].tags.house_number);
    }
  }
  searches = results;
}

/**
*@brief Checks if a certain address is in the array passed to JSON through manual typing 
*@param[in] input_streetname[] Checks for the certain streetname
*@param[in] input_housenumber[] Checks for the certain housenumber
*@param[out] "dyn_array_address *searches" Contains the information the user provied 
*/
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

/**
*@brief Checks if a certain addrss is in the string to JSON trough the input file
*@param[in] input_streetname[] Checks for the certain streetname
*@param[in] input_housenumber[] Checks for the certain housenumber
*@param[out] "address input_array[]" An array that contains the addresses of the houses that have to be visited
*@param[in] number_of_addresses The number of addesses registered in the command prompt
*/
int is_in_searches(char input_streetname[], char input_housenumber[], struct address input_array[], int number_of_adresses) {
  for (int i = 0; i < number_of_adresses; ++i) {
    if (strcmp(input_streetname, input_array[i].tags.street) == 0) {
      if (strcmp(input_housenumber, input_array[i].tags.house_number) == 0) {
        return 1;
      }
    }
  }
  return 0;
}