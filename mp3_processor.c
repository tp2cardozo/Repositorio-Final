#include <stdio.h>
#include <stdlib.h>

#include "mp3_processor.h"
#include "setup.h"


status_t process_mp3_data(setup_t * setup, FILE * fi)
{

	status_t st;
	const char header[MAX_HEADER_SIZE];
	ADT_track_t * track;

	if(setup == NULL || fo == NULL || fi == NULL)
		return ERROR_NULL_POINTER;

	if((st = ADT_track_new(&track)) != OK)
		return ERROR_INVALID_TRACK;

	if((st = get_mp3_header(fi, header)) != OK)
	{	
		if((st = ADT_trak_delete(&track)) != OK)
			return st;
		
		return st;
	}

	if((st = ADT_track_set(header, track)) != OK)
		return st;



	return OK;	
}

status_t get_mp3_header(FILE * fi, const char header[])
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
