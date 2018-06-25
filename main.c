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


int main(int argc, char *argv[]) 
{

	size_t i;
	FILE * file_out, * mp3_file;
	status_t st;

	if((st = validate_arguments(int argc, char * argv[], setup_t * setup)) != OK)
  	{
   		print_errors(st);
    	return st;
  	}
  
  
	if ((file_out = fopen(argv[OUTPUT_FILE_POS], "wt")) == NULL)
	{
		st = ERR_INVALID_OUTPUT_FILE;
		fprintf(stderr, "%s\n", errors_dictionary[st]);
		return st;
	}
  

	for(i = 1; i < argc - OUTPUT_FILE_POS; i++ )
  	{
  		if((mp3_file = fopen(argv[OUTPUT_FILE_POS + i], "rt")) == NULL)
    		return ERROR_INVALID_MP3_FILE;

    	if((st = process_mp3_data()) != OK)
	  	{
	    	print_errors(st);
	    	return st;
	  	}
  	
  	}
 
	
  
	return OK;
}



status_t validate_arguments(int argc, char * argv[], setup_t * setup)
{
	size_t i;
	if(argv == NULL || setup == NULL)
		return ERROR_NULL_POINTER;

	if(argc < MIN_ARGUMENTS)
		return ERROR_INVOCATION;
																																								/*validar argumentos desorden*/
	if(strcmp(argv[FORMAT_FLAG_POSITION], FORMAT_FLAG_TOKEN))
		return ERROR_INVOCATION;

	if(strcmp(argv[SORT_FLAG_POSITION], SORT_FLAG_TOKEN))
		return ERROR_INVOCATION;

	if(strcmp(argv[OUT_FLAG_POSITION], OUT_FLAG_TOKEN))
		return ERROR_INVOCATION;
	
  for(i=0 ; i < MIN_ARGUMENTS ; i++)
  {
    if (!(strcmp(argv[FORMAT_FLAG_POSITION + 1], format_dictionary[i]))) /*Hacer diccionario de formatos*/
    {
     	setup -> doc_type = i;
      continue;
    }  
    
    if(!(strcmp(argv[SORT_FLAG_POSITION + 1], sort_dictionary[i])))/*Hacer diccionario de sort*/
    {
      setup -> sort_by = i;
      break;
    }
  }
  
  if(i = MIN_ARGUMENTS)
    return ERROR_INVOCATION;
  
 	return OK
}