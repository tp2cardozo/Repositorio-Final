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

	if((st = mp3_reader(fi, header)) != OK)
		return st;


	
}

status_t get_mp3_header(FILE * fi, char header[])
{
	if(fi == NULL)
		return ERROR_NULL_POINTER;


	 if ((fi = fopen(fi,"rb")) == NULL)
        return ERROR_INVALID_MP3_FILE;
	 

    fseek(fi, 0, SEEK_END);						/* manda el puntero al final del archivo 	*/

    length=ftell(fi);							/* da la distancia al comienzo 				*/

    fseek(fi,length-MP3_HEADER_SIZE,SEEK_SET);	/* se para en el header MP3 				*/

    fread(header,sizeof(char),MP3_HEADER_SIZE,fi);

    show_mp3_header(header,stdout);

}

status_t show_mp3_header (const char header[], FILE * fo)
{
    char buf[MP3_HEADER_SIZE];

    if (header == NULL)
       return ERROR_NULL_POINTER;

    memcpy(buf,header+LEXEM_START_TAG,LEXEM_SPAN_TAG);
    buf[LEXEM_SPAN_TAG] = '\0';
    

    memcpy(buf,header+LEXEM_START_TITLE,LEXEM_SPAN_TITLE);
    buf[LEXEM_SPAN_TITLE] = '\0';
   

    memcpy(buf,header+LEXEM_START_ARTIST,LEXEM_SPAN_ARTIST);
    buf[LEXEM_SPAN_ARTIST] = '\0';


    memcpy(buf,header+LEXEM_START_ALBUM,LEXEM_SPAN_ALBUM);
    buf[LEXEM_SPAN_ALBUM] = '\0';


    memcpy(buf,header+LEXEM_START_YEAR,LEXEM_SPAN_YEAR);
    buf[LEXEM_SPAN_YEAR] = '\0';


    memcpy(buf,header+LEXEM_START_COMMENT,LEXEM_SPAN_COMMENT);
    buf[LEXEM_SPAN_COMMENT] = '\0';


    memcpy(buf,header+LEXEM_START_GENRE,LEXEM_SPAN_GENRE);
    buf[LEXEM_SPAN_GENRE] = '\0';

    return OK;
}