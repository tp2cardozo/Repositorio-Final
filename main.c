#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"


/**********Externs**********/
extern setup_t setup;

/*Diccionario de formatos*/
char * doc_formats[MAX_FORMAT_NAMES] = {
	CSV_FORMAT_STR,
	XML_FORMAT_STR,
	HTML_FORMAT_STR
};

/*Diccionario de ordenamientos*/
char * sorting_formats[MAX_SORT_NAMES] = {
	SORT_BY_NAME_STR,
	SORT_BY_ARTIST_STR,
	SORT_BY_GENRE_STR
};

int main(int argc, char *argv[])
{
	status_t st;


	/*Se validan los argumentos*/
	if((st = validate_arguments(argc, argv, &setup)) != OK)
	{
   		print_error(st);
		return st;
	}

	if((st = process_mp3_files(argc - FIRST_MP3_FILE_INDEX, &(argv[FIRST_MP3_FILE_INDEX]), &setup)) != OK) 
	{
		print_error(st);
		return st;
	}

	return OK;
}

/*Función que valida los argumentos de la invocación*/
status_t validate_arguments(int argc, char * argv[], setup_t * setup)
{
	size_t i;
	size_t fmt_flag = 0;
	size_t sort_flag = 0;
	size_t out_flag = 0;
	
	if(argv == NULL || setup == NULL)
		return ERROR_NULL_POINTER;

	if(argc < MIN_ARGUMENTS)
		return ERROR_INVOCATION;

	for(i=1; i<MIN_ARGUMENTS; i++)
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

	for(i=0 ; i < MAX_FORMAT_NAMES; i++)
	{
		if (!(strcmp(argv[fmt_flag + 1], doc_formats[i]))) 
		{
			setup->doc_type = i;
			break;
		}
	}


	if(i == MAX_FORMAT_NAMES)
		return ERROR_INVOCATION;

	for(i=0 ; i < MAX_SORT_NAMES ; i++)
	{
		if(!(strcmp(argv[sort_flag + 1], sorting_formats[i])))
		{
			setup->sorting_criteria = i;
			break;
		}
	}

	if(i == MAX_SORT_NAMES)
		return ERROR_INVOCATION;

	setup -> output_file_path = argv[out_flag + 1];

	return OK;
}

