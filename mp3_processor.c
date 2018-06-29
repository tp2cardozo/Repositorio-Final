#include <stdio.h>
#include <stdlib.h>

#include "mp3_processor.h"

extern status_t (*format_output[MAX_FORMATS])(void *, const void *, FILE *);
extern int (*sort_output[MAX_SORTS]) (void *, void *);

/*Diccionario de formatos*/
char * format_dictionary[MAX_FORMATS] = {
	CSV_FORMAT,
	XML_FORMAT
};

/*Diccionario de ordenamientos*/
char * sort_dictionary[MAX_SORTS] = {
	SORT_BY_NAME,
	SORT_BY_ARTIST,
	SORT_BY_GENRE
};

/*Esta función se ocupa de insertar un track en un vector*/
status_t process_mp3_data(setup_t * setup, FILE * fi, ADT_Vector_t ** vector)
{
	status_t st;
	char header[MAX_HEADER_SIZE];
	ADT_track_t * track;

	if(setup == NULL || fi == NULL || vector == NULL)
		return ERROR_NULL_POINTER;

	if((st = ADT_track_new(&track)) != OK)
		return ERROR_INVALID_TRACK;

	if((st = get_mp3_header(fi, header)) != OK) {	
		if((st = ADT_track_delete(&track)) != OK)
			return st;

		return st;
	}

	if((st = ADT_track_set(header, track)) != OK)
		return st;

	if((st = ADT_Vector_append_element(vector, track)) != OK)
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

status_t get_tracks_from_mp3_files (int argc, char * argv[], ADT_Vector_t ** vector, setup_t * setup) 
{
	FILE * mp3_file;
	size_t i;
	status_t st;

	for(i = 0; i < argc - INDEX_FIRST_MP3_FILE; i++ )
	{

		if((mp3_file = fopen(argv[INDEX_FIRST_MP3_FILE + i], "rt")) == NULL)
		{
			st = ERROR_INVALID_MP3_FILE;
			return st;
		}

		if((st = process_mp3_data(setup, mp3_file, vector)) != OK)
		{
			fclose(mp3_file);
			return st;	
		}

	  	if((fclose(mp3_file)) == EOF)
	  	{
	  		st = ERROR_CLOSING_FILE;
			return st;
	  	}
  	}
  	return OK;
}

status_t set_vector_for_tracks (ADT_Vector_t * vector, setup_t * setup) 
{
	status_t st;

	if((st = ADT_Vector_set_printer (vector, format_output[setup->doc_type])) != OK) 
		return st;
	
	if((st = ADT_Vector_set_comparator (vector, sort_output[setup->sort_by])) != OK)
		return st;

	if((st = ADT_Vector_set_destructor(vector, ADT_track_delete)) != OK)
		return st;

	return OK;
}

status_t export_tracks_vector (ADT_Vector_t * vector, char * argv[], void * context, size_t out_index, setup_t * setup) 
{
	FILE * file_out;
	status_t st;

	if ((file_out = fopen(argv[out_index], "wt")) == NULL)
	{
		st = ERROR_INVALID_OUTPUT_FILE;
		ADT_Vector_delete(&vector);
		return st;
	}
	if((st = ADT_Vector_export(vector, context, file_out, setup)) != OK)
	{
		ADT_Vector_delete(&vector);
		fclose(file_out);
		return st;
	}
	if((st = ADT_Vector_delete(&vector)) != OK)
	{
		fclose(file_out);
		return st;
	}
	if((fclose(file_out)) == EOF)
	{
		st = ERROR_CLOSING_FILE;
		return st;
	}
	return OK;
}

status_t process_mp3_files (size_t out_index, void * context, int argc, char * argv[], setup_t * setup) 
{
	ADT_Vector_t * vector;
	status_t st;

	if((st = ADT_Vector_new(&vector)) != OK)
		return st;
	if((st = set_vector_for_tracks (vector, setup)) != OK) 
	{
		ADT_Vector_delete(&vector);
		return st;
	}
	if((st = get_tracks_from_mp3_files(argc, argv, &vector, setup)) != OK) 
	{
		ADT_Vector_delete(&vector);
		return st;
	}
  	if((st = ADT_Vector_sort_elements(&vector, ADT_Vector_swap_elements)) != OK)
  	{
  		ADT_Vector_delete(&vector);
  		return st;
  	}
  	if((st = export_tracks_vector (vector, argv, context, out_index, setup)) != OK) 
		return st;

	return OK;
}
