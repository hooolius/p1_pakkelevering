#ifndef MAP_AND_PARSER_ADDRESSES_PROMPT_H
#define MAP_AND_PARSER_ADDRESSES_PROMPT_H

#include "parser_addresses.h"
#include "../libs/dynamic_array.h"
/**
*@brief In this function the user can input the addresse he or she has to visit - This can happen through a file or manually typing them
*@param[in] dyn_array_address *searches Is an empty array that is going to be filld up with adresses
*/
void addresses_prompt(dyn_array_address *searches, FILE *input);

#endif //MAP_AND_PARSER_ADDRESSES_PROMPT_H
