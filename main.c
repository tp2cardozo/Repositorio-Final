#include <stdio.h>
#include <stdlib.h>

#include "main.h"

/*Biblioteca de formatos*/
char * format_dictionary[MAX_FORMATS] =
{
	CSV_FORMAT,
	XML_FORMAT
}


/*Biblioteca de ordenamientos*/
char * sort_dictionary[MAX_SORTS] =
{
	SORT_BY_NAME,
	SORT_BY_ARTIST,
	SORT_BY_GENRE
}


extern char * errors_dictionary[MAX_ERRORS];
extern setup_t setup;

int main(int argc, char *argv[]) 
{

	size_t i;
	size_t out_index;
	FILE *file_out, *mp3_file;
	status_t st;
	ADT_Vector_t * vector;

	if((st = validate_arguments(argc, argv[], &setup, &out_index)) != OK)
	{
   		print_errors(st);
		return st;
	}

	if((st = ADT_Vector_new(&vector)) != OK)
		return st;

	if ((file_out = fopen(argv[out_index], "wt")) == NULL)
	{
		st = ERR_INVALID_OUTPUT_FILE;
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
				return st;
			
			fclose(mp3_file);
			break;	
		}

	  	fclose(mp3_file);
  	}

/*



falta ordenar el vector

falta imprimir el vector en en el archivo



*/

	return OK;
}


/*Función que valida los argumentos de la invocación*/
status_t validate_arguments(int argc, char * argv[], setup_t * setup, size_t * index_out_file) 
{
	size_t i, fmt_flag, sort_flag, out_flag;
	
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