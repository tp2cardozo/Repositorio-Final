#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"


/**********Externs**********/
extern char context_csv;
extern char * context_xml[MAX_XML_CONTEXTS];
extern setup_t setup;
extern char * format_dictionary[MAX_FORMATS];
extern char * sort_dictionary[MAX_SORTS];

int main(int argc, char *argv[])
{
	size_t out_index;
	status_t st;
	void * context;

	/*Se validan los argumentos*/
	if((st = validate_arguments(argc, argv, &setup, &out_index, &context)) != OK)
	{
   		print_error(st);
		return st;
	}

	if((st = process_mp3_files (out_index, context, argc, argv, &setup)) != OK) 
	{
		print_error(st);
		return st;
	}

	return OK;
}

/*Función que valida los argumentos de la invocación*/
status_t validate_arguments(int argc, char * argv[], setup_t * setup, size_t * index_out_file, void ** context)
{
	size_t i;
	size_t fmt_flag = 0;
	size_t sort_flag = 0;
	size_t out_flag = 0;
	status_t st;
	
	if(argv == NULL || setup == NULL)
		return ERROR_NULL_POINTER;

	if(argc < MIN_ARGUMENTS)
	{
		return ERROR_INVOCATION;
	}

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
	if((st = set_printer_context(setup, context)) != OK)
		return st;

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

	if(i == MAX_SORTS)
		return ERROR_INVOCATION;

	*index_out_file = out_flag + 1;

	return OK;
}

status_t set_printer_context (setup_t * setup, void ** context) 
{
	if (setup == NULL || context == NULL)
		return ERROR_NULL_POINTER;

	switch (setup->doc_type) 
	{
		case (FMT_XML) :
			*context = &context_xml;
			break;

		case (FMT_CSV) :
			*context = &context_csv;
			break;
	}
	return OK;
}