#include <stdio.h>
#include <stdlib.h>

#include "mp3_processor.h"

/*Esta función se ocupa de insertar un track en un vector*/
status_t process_mp3_data(setup_t * setup, FILE * fi, ADT_Vector_t * vector)
{

	status_t st;
	char header[MAX_HEADER_SIZE];
	ADT_track_t * track;

	if(setup == NULL || fi == NULL || vector == NULL)
		return ERROR_NULL_POINTER;

	if((st = ADT_track_new(&track)) != OK)
		return ERROR_INVALID_TRACK;

	if((st = get_mp3_header(fi, header)) != OK)
	{	
		if((st = ADT_track_delete(&track)) != OK)
			return st;

		return st;
	}

	if((st = ADT_track_set(header, track)) != OK)
		return st;

	if((st = ADT_Vector_append_element(&vector, track)) != OK)
		return st;


	return OK;	
}
/*Lee el "header" del archivo mp3*/
status_t get_mp3_header(FILE * fi, char header[])
{
	size_t length;

	if(fi == NULL)
		return ERROR_NULL_POINTER;
	 

	if ((fseek(fi, 0, SEEK_END)) != OK)	
		return ERROR_INVALID_MP3_FILE;

	length=ftell(fi);

	if((fseek(fi,length - MP3_HEADER_SIZE, SEEK_SET)) != OK)
		return ERROR_INVALID_MP3_FILE;

	if (fread(header, sizeof(char), MP3_HEADER_SIZE, fi) != MP3_HEADER_SIZE)
		return ERROR_INVALID_MP3_FILE;

	return OK;
}
