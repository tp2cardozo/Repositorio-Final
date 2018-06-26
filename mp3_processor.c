#include <stdio.h>
#include <stdlib.h>

#include "mp3_processor.h"
#include "setup.h"

status_t process_mp3_data(setup_t * setup, FILE * fo, FILE * fi)
{
	status_t st;
	ADT_Vector_t * vector;
	char header[MAX_HEADER_SIZE];



	if(setup == NULL || fo == NULL || fi == NULL)
		return ERROR_NULL_POINTER;

	if((st = ADT_Vector_new(&vector)) != OK)
		return st;

	if((st = mp3_reader(fi, header)) != OK)
		return st;
}