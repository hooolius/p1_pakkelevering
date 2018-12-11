#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define MAX_NUMBER_OF_NODES 20
#define SENTINEL 'end'

struct address {
	int id;
	double lat;
	double lon;
    char city[30];
    char country[10];
    char house_number[5];
    char muncipality[25];
    char postcode[5];
    char street[30];
};


int main(void){
	int i=0, number_of_packages=0, j=1;
	struct address arr_number_addresses[MAX_NUMBER_OF_NODES];
	char check_for_end[50], end[]="END", input_choice[2], manual_check[]="1", document_check[]="2", newline_find, location_check[25], aalborg_check[]="Aalborg", different_check[]="different";

	printf("Hello there! - I need to know if you want to insert the addresses manually or using a document."
		"\nPress (1) for typing them in yourself and press (2) for using a document\n");
	scanf("%s", input_choice);

	do{
	printf("If you would like to use the geodata of the city Aalborg please type 'Aalborg' and if you would like to use the geodata of a different location please type 'different'");
	scanf("%s", location_check);
	} while(strcmp(location_check, aalborg_check)!=0 && strcmp(location_check, different_check)!=0);



	if(strcmp(input_choice, manual_check)==0){
		printf("You have chosen to type in the addresses yourself\nWhen you are done typing your addresses type 'END' to end the proces of typing in addresses\n");

		while(strcmp(check_for_end, end)!=0){
			printf("Please enter the streetname (Element number %d)\n", j);
			scanf("%s", check_for_end);

			if(0!=strcmp(check_for_end, end)){
				strcpy(arr_number_addresses[i].street, check_for_end);
				printf("Please enter the housenumber (Element number %d)\n", j);
				scanf("%d", &arr_number_addresses[i].house_number);
				i++;
				number_of_packages++;
				j++;
		    }
		}

	}else if(strcmp(input_choice, document_check)==0){

		FILE *pinput_file;
		pinput_file=fopen("leveringsfil.txt", "r");
	
	/*Cound the number of lines in the txt file*/
	while(!feof(pinput_file)){
		newline_find=fgetc(pinput_file);
		if(newline_find == '\n'){
			++number_of_packages;
		}
	}

	rewind(pinput_file);

	for( i = 0; i < number_of_packages; i++){
		fscanf(pinput_file, " %[A-Za-z ], %[A-Za-z], %[0-9], %[A-Za-z-], %[0-9], %[A-Za-z].", 
			arr_number_addresses[i].city, arr_number_addresses[i].country, 
			arr_number_addresses[i].house_number, arr_number_addresses[i].muncipality, 
			arr_number_addresses[i].postcode, arr_number_addresses[i].street);
	}

	}else{
		printf("Invalid input - Try again\n");
	}

	for(i=0 ; i<number_of_packages ; i++){
		printf("%s, %s, %s, %s, %s, %s\n", arr_number_addresses[i].city, arr_number_addresses[i].country, 
			arr_number_addresses[i].house_number, arr_number_addresses[i].muncipality, 
			arr_number_addresses[i].postcode, arr_number_addresses[i].street);
	}

return 0;
}
