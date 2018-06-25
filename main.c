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


int main(int argc, char *argv[]) {
	size_t i;
	FILE * file_out, * mp3_file;
	status_t st;

	if((st = validate_arguments(argc, argv[], &setup)) != OK) {
   		print_errors(st);
		return st;
	}

	if ((file_out = fopen(argv[OUTPUT_FILE_POS], "wt")) == NULL) {
		st = ERR_INVALID_OUTPUT_FILE;
		fprintf(stderr, "%s\n", errors_dictionary[st]);
		return st;
	}

	for(i = 1; i < argc - OUTPUT_FILE_POS; i++ ) {
		if((mp3_file = fopen(argv[OUTPUT_FILE_POS + i], "rt")) == NULL)
			return ERROR_INVALID_MP3_FILE;

		if((st = process_mp3_data(&setup, out_file, mp3_file)) != OK) {
			print_errors(st);
			return st;
		}

	  	fclose(mp3_file);
  	}
  
	return OK;
}

status_t validate_arguments(int argc, char * argv[], setup_t * setup) {
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

	for(i=0 ; i < MAX_FORMATS; i++) {
		if (!(strcmp(argv[fmt_pos + 1], format_dictionary[i]))) 
		{ 														/*Hacer diccionario de formatos*/ 
			setup->doc_type = i;
			break;
		}
	}

	if(i == MAX_FORMATS)
		return ERROR_INVOCATION;

	for(i=0 ; i < MAX_SORTS ; i++) {
		if(!(strcmp(argv[sort_pos + 1], sort_dictionary[i]))) {
			setup->sort_by = i;
			break;
		}
	}

	if(i == MAX_SORTS)
		return ERROR_INVOCATION;
}