#include <stdio.h>
#include <stdlib.h>

#include "types.h"
#include "errors.h"
#include "setup.h"

#define SALIDA "salida.csv"
#define DELIMITER ','
#define MAX_NAME 100
#define MAX_ARTIST 100
#define MAX_GENRE 100

extern char * errors_dictionary[MAX_ERRORS];
extern setup_t setup;

status_t export_to_csv(char * name, char * artist, char * genre, FILE * file_out, char del);

int main(int argc, char *argv[]) {
	char name[MAX_NAME] = "Muy Punk";
	char artist[MAX_ARTIST] = "La Polla";
	char genre[MAX_GENRE] = "Punk";
	FILE * file_out;
	status_t st;


	file_out = fopen(SALIDA, "wt");
	if (file_out == NULL) {
		st = ERR_INVALID_OUTPUT_FILE;
		fprintf(stderr, "%s\n", errors_dictionary[st]);
		return st;
	}

	if(export_to_csv(name, artist, genre, file_out, DELIMITER))

	if(fclose(file_out) == EOF) {
		st = ERR_CLOSING_FILE;
		fprintf(stderr, "%s\n", errors_dictionary[st]);
		return st;
	}

	return OK;
}

status_t export_to_csv(char * name, char * artist, char * genre, FILE * file_out, char del) {
	status_t st;

	if(fprintf(file_out, "%s", name) < 0) {
		st = ERR_WRITING_TO_FILE; 
		fprintf(stderr, "%s\n", errors_dictionary[st]);
		return st;
	}
	if (fputc(del, file_out) == EOF) {
		st = ERR_WRITING_TO_FILE; 
		fprintf(stderr, "%s\n", errors_dictionary[st]);
		return st;
	}
	if(fprintf(file_out, "%s", artist) < 0) {
		st = ERR_WRITING_TO_FILE; 
		fprintf(stderr, "%s\n", errors_dictionary[st]);
		return st;
	}
	if (fputc(del, file_out) == EOF) {
		st = ERR_WRITING_TO_FILE; 
		fprintf(stderr, "%s\n", errors_dictionary[st]);
		return st;
	}
	if(fprintf(file_out, "%s", genre) < 0) {
		st = ERR_WRITING_TO_FILE; 
		fprintf(stderr, "%s\n", errors_dictionary[st]);
		return st;
	}
	return OK;
}


status_t validate_arguments(int argc, char * argv[], setup_t * setup)
{
	size_t i, fmt_pos, sort_pos, out_pos;
	if(argv == NULL || setup == NULL)
		return ERROR_NULL_POINTER;

	if(argc < MIN_ARGUMENTS)
		return ERROR_INVOCATION;

	for(i=0; i<argc; i++) {
		if(strcmp(argv[i], FORMAT_FLAG_TOKEN) == 0)
			fmt_pos = i;
		if(strcmp(argv[i], SORT_FLAG_TOKEN) == 0)
			sort_pos = i;
		if(strcmp(argv[i], OUT_FLAG_TOKEN) == 0)
			out_pos = i;
	}
	if(!fmt_pos || !sort_pos || !out_pos)
		return ERROR_INVOCATION;

/*
	if(strcmp(argv[FORMAT_FLAG_POSITION], FORMAT_FLAG_TOKEN))
		return ERROR_INVOCATION;

	if(strcmp(argv[SORT_FLAG_POSITION], SORT_FLAG_TOKEN))
		return ERROR_INVOCATION;

	if(strcmp(argv[OUT_FLAG_POSITION], OUT_FLAG_TOKEN))
		return ERROR_INVOCATION;
*/
	for(i=0 ; i < MAX_FORMATS/*MIN_ARGUMENTS*/ ; i++)/*NO ES MIN_ARGUMENTS, ES MAX_FORMATS*/
	{
		if (!(strcmp(/*argv[FORMAT_FLAG_POSITION + 1]*/argv[fmt_pos + 1], format_dictionary[i]))) /*Hacer diccionario de formatos*/
    	{
	     	setup->doc_type = i;
	        break;
		}    
	}
  
	if(i == /*MIN_ARGUMENTS*/MAX_FORMATS)
		return ERROR_INVOCATION;
  
	for(i=0 ; i < MAX_FORMATS ; i++)
	{
		if(!(strcmp(argv[sort_pos + 1], sort_dictionary[i])))
		{
			setup->sort_by = i;
			break;
    	}
	}

	if(i == MAX_FORMATS)
		return ERROR_INVOCATION;
}