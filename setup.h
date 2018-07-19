#ifndef SETUP__H
#define SETUP__H

#include <stdio.h>
#include "types.h"

typedef struct
{
	doc_type_t doc_type;
	sorting_criterium_t sorting_criteria;
	char * output_file;
}setup_t;

#endif