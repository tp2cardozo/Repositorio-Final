#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"

/*Biblioteca de formatos*/
char * format_dictionary[MAX_FORMATS] =
{
	CSV_FORMAT,
	XML_FORMAT
};


/*Biblioteca de ordenamientos*/
char * sort_dictionary[MAX_SORTS] =
{
	SORT_BY_NAME,
	SORT_BY_ARTIST,
	SORT_BY_GENRE
};

extern char context_csv;
extern char * context_xml[];
extern status_t (*format_output[MAX_FORMATS])(void *, FILE *);
extern int (*sort_output[MAX_SORTS]) (void *, void *);
extern char * errors_dictionary[MAX_ERRORS];
extern setup_t setup;

int main(int argc, char *argv[]) 
{
	size_t i;
	size_t out_index;
	FILE *file_out, *mp3_file;
	status_t st;
	ADT_Vector_t * vector;
	void * context;
/*
  	validar argumentos listo*****
  	ADT_Vector_new listo******
  	ADT_Vector_set_printer listo*****
  	ADT_Vector_set_comparator (falta validar)
  	ADT_Vector_set_destructor (falta validar)
  	abrir archivo de salida listo ******
  	FOR{
  		abrir mp3
  		procesar mp3
  		guardar mp3 en el vector
  		cerrar mp3
  	} ***listo****
  	ADT_Vector_sort_elements 
  	ADT_Vector_export
  	ADT_Vector_delete
  	return OK
*/

	if((st = validate_arguments(argc, argv, &setup, &out_index)) != OK)
	{
   		print_errors(st);
		return st;
	}

	if (setup.doc_type == CSV) {
		context = &context_csv;
	}else{
		context = &context_xml;
	}

	if((st = ADT_Vector_new(&vector)) != OK)
	{
		print_errors(st);
		return st;
	}


	if((st = ADT_Vector_set_printer (vector, format_output[setup.doc_type])) != OK)
	{
		print_errors(st);
		return st;
	}

	if((st = ADT_Vector_set_comparator(vector, sort_output[setup.sort_by])) != OK)
	{
		print_errors(st);
		return st;
	}

	if((st = ADT_Vector_set_destructor(vector, ADT_track_delete)) != OK)
	{
		print_errors(st);
		return st;
	}



	if ((file_out = fopen(argv[out_index], "wt")) == NULL)
	{
		st = ERROR_INVALID_OUTPUT_FILE;
		fprintf(stderr, "%s\n", errors_dictionary[st]);
		return st;
	}

	for(i = 0; i < argc - INDEX_FIRST_MP3; i++ ) 
	{

		if((mp3_file = fopen(argv[INDEX_FIRST_MP3 + i], "rt")) == NULL)
			return ERROR_INVALID_MP3_FILE;

		if((st = process_mp3_data(&setup, mp3_file, vector)) != OK) 
		{
			if((ADT_Vector_delete(&vector)) != OK)
			{
				print_errors(st);
				return st;
			}
			
			fclose(mp3_file);
			
			print_errors(st);

			break;	
		}

	  	fclose(mp3_file);
  	}


  	if((st = ADT_Vector_sort_elements(&vector, ADT_Vector_swap_elements)) != OK)
  	{
  		print_errors(st);
  		return st;
  	}

	if((st = ADT_Vector_export(vector, context, file_out)) != OK)
	{
		print_errors(st);
		return st;
	}

	if((st = ADT_Vector_delete(&vector)) != OK)
	{
		print_errors(st);
		return st;
	}

	return OK;
}


/*Función que valida los argumentos de la invocación*/
status_t validate_arguments(int argc, char * argv[], setup_t * setup, size_t * index_out_file) 
{
	size_t i;
	size_t fmt_flag = 0;
	size_t sort_flag = 0;
	size_t out_flag = 0;
	
	if(argv == NULL || setup == NULL)
		return ERROR_NULL_POINTER;

	if(argc < MIN_ARGUMENTS)
		return ERROR_INVOCATION;

	for(i=0; i<argc; i++)
	{
		if(strcmp(argv[i], FORMAT_FLAG_TOKEN) == 0)
			fmt_flag = i;
		if(strcmp(argv[i], SORT_FLAG_TOKEN) == 0)
			sort_flag = i;
		if(strcmp(argv[i], OUT_FLAG_TOKEN) == 0)
			out_flag = i;
	}


	if(!fmt_flag || !sort_flag || !out_flag)
		return ERROR_INVOCATION;

	for(i=0 ; i < MAX_FORMATS; i++)
	{
		if (!(strcmp(argv[fmt_flag + 1], format_dictionary[i]))) 
		{
			setup->doc_type = i;
			break;
		}
	}

	if(i == MAX_FORMATS)
		return ERROR_INVOCATION;

	for(i=0 ; i < MAX_SORTS ; i++)
	{
		if(!(strcmp(argv[sort_flag + 1], sort_dictionary[i])))
		{
			setup->sort_by = i;
			break;
		}
	}

	*index_out_file = out_flag + 1;

	if(i == MAX_SORTS)
		return ERROR_INVOCATION;

	return OK;
}