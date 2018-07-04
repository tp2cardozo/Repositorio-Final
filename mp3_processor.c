#include <stdio.h>
#include <stdlib.h>

#include "mp3_processor.h"

extern status_t (*format_output[MAX_FORMATS])(void *, const void *, FILE *);
extern int (*sort_output[MAX_SORTS]) (void *, void *);
extern char * context_csv;
extern char * context_xml[MAX_XML_CONTEXTS];

/*Diccionario de formatos*/
char * doc_formats[MAX_FORMATS] = {
	CSV_FORMAT,
	XML_FORMAT
};

/*Diccionario de ordenamientos*/
char * sorting_formats[MAX_SORTS] = {
	SORT_BY_NAME,
	SORT_BY_ARTIST,
	SORT_BY_GENRE
};

status_t process_mp3_files (int argc, char * argv[], setup_t * setup) 
{
	ADT_Vector_t * vector;
	size_t i;
	void * context;
	FILE * file_out, * mp3_file;
	status_t st;


	if((st = ADT_Vector_new(&vector)) != OK)
		return st;
	
	if((st = set_printer_context(setup->doc_type, &context)) != OK)
	{
		ADT_Vector_delete(&vector);
		return st;
	}

	if((st = ADT_Vector_set_printer (vector, format_output[setup->doc_type])) != OK) 
	{
		ADT_Vector_delete(&vector);
		return st;
	}
	
	if((st = ADT_Vector_set_comparator (vector, sort_output[setup->sorting_criterium])) != OK)
	{
		ADT_Vector_delete(&vector);
		return st;
	}

	if((st = ADT_Vector_set_destructor(vector, ADT_track_delete)) != OK)
	{
		ADT_Vector_delete(&vector);
		return st;
	}


	for(i = 0; i < argc - INDEX_FIRST_MP3_FILE; i++ )
	{

		if((mp3_file = fopen(argv[INDEX_FIRST_MP3_FILE + i], "rt")) == NULL)
		{
			ADT_Vector_delete(&vector);
			return ERROR_INVALID_MP3_FILE;
		}
		

		if((st = process_mp3_file(setup, mp3_file, vector)) != OK)
		{
			ADT_Vector_delete(&vector);
			fclose(mp3_file);
			return st;	
		}

	  	if((fclose(mp3_file)) == EOF)
	  	{
	  		ADT_Vector_delete(&vector);
	  
			return ERROR_DISK_SPACE;
	  	}
  	}

  	if((st = ADT_Vector_sort_elements(&vector, ADT_Vector_swap_elements)) != OK)
  	{
  		ADT_Vector_delete(&vector);
  		return st;
  	}

  	if ((file_out = fopen(setup->output_file_path, "wt")) == NULL)
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
		return ERROR_DISK_SPACE;


	return OK;
}



/*Esta función se ocupa de insertar un track en un vector*/
status_t process_mp3_file(setup_t * setup, FILE * fi, ADT_Vector_t ** vector)
{
	status_t st;
	ADT_track_t * track;

	if(setup == NULL || fi == NULL || vector == NULL)
		return ERROR_NULL_POINTER;

	if((st = ADT_track_new(&track)) != OK)
		return ERROR_INVALID_TRACK;

	if((st = set_track_from_mp3_file(fi, track)) != OK)
	{
		ADT_track_delete(&track);
		return st;
	}

	if((st = ADT_Vector_append_element(vector, track)) != OK)
		return st;

	return OK;	
}

status_t vector_set (ADT_Vector_t * vector, setup_t * setup) 
{
	status_t st;

	if((st = ADT_Vector_set_printer (vector, format_output[setup->doc_type])) != OK) 
		return st;
	
	if((st = ADT_Vector_set_comparator (vector, sort_output[setup->sorting_criterium])) != OK)
		return st;

	if((st = ADT_Vector_set_destructor(vector, ADT_track_delete)) != OK)
		return st;

	return OK;
}

status_t set_printer_context (doc_type_t doc_type, void ** context) 
{
	if (setup == NULL || context == NULL)
		return ERROR_NULL_POINTER;

	switch (doc_type) 
	{
		case FMT_XML :
			*context = &context_xml;
			break;

		case FMT_CSV :
			*context = &context_csv;
			break;

		case FMT_HTML :
			return ERROR_NOT_IMPLEMENTED;
	}
	return OK;
}