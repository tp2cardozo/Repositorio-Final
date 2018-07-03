#ifndef SETUP__H
#define SETUP__H

#include <stdio.h>
#include "types.h"

typedef struct
{
	doc_type_t doc_type;
	sorting_criteria_t sorting_criteria;
	char * output_file_path;
}setup_t;

#endif