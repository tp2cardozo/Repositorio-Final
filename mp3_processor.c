#include <stdio.h>
#include <stdlib.h>

#include "mp3_processor.h"
#include "setup.h"


status_t process_mp3_data(setup_t * setup, FILE * fi)
{

	status_t st;
	ADT_Vector_t * vector;
	char header[MAX_HEADER_SIZE];

	if(setup == NULL || fo == NULL || fi == NULL)
		return ERROR_NULL_POINTER;

	if((st = ADT_Vector_new(&vector)) != OK)
		return st;

	if((st = get_mp3_header(fi, header)) != OK)
		return st;

	



	
}

status_t get_mp3_header(FILE * fi, char header[])
{
	if(fi == NULL)
		return ERROR_NULL_POINTER;


	 if ((fi = fopen(fi,"rb")) == NULL)
        return ERROR_INVALID_MP3_FILE;
	 

    if ((fseek(fi, 0, SEEK_END)) != OK)					/* manda el puntero al final del archivo 	*/
    	return ERROR_INVALID_MP3_FILE;

    length=ftell(fi);							/* da la distancia al comienzo 				*/

    if((fseek(fi,length-MP3_HEADER_SIZE,SEEK_SET)) != OK)	/* se para en el header MP3 				*/
    	return ERROR_INVALID_MP3_FILE;

    if (fread(header, sizeof(char), MP3_HEADER_SIZE, fi) != MP3_HEADER_SIZE)
        return ERROR_INVALID_MP3_FILE;

    return OK;
}
