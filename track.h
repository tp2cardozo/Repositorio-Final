#ifndef TRACK__H
#define TRACK__H

#include <stdio.h>
#include <stdlib.h>

#include "types.h"

#define CSV_DELIMITER '|'

#define MP3_HEADER_SIZE		128

#define LEXEM_START_TAG     0
#define LEXEM_SPAN_TAG      3

#define LEXEM_START_TITLE   3
#define LEXEM_SPAN_TITLE   30

#define LEXEM_START_ARTIST 33
#define LEXEM_SPAN_ARTIST  30

#define LEXEM_START_ALBUM  63
#define LEXEM_SPAN_ALBUM   30

#define LEXEM_START_YEAR   93
#define LEXEM_SPAN_YEAR     4

#define LEXEM_START_COMMENT 97
#define LEXEM_SPAN_COMMENT  30

#define LEXEM_START_GENRE  127
#define LEXEM_SPAN_GENRE     1

typedef struct
{
	char tag[LEXEM_SPAN_TAG];
	char title[LEXEM_SPAN_TITLE];
	char artist[LEXEM_SPAN_ARTIST];
	char album[LEXEM_SPAN_ALBUM];
	char year[LEXEM_SPAN_YEAR];
	char comment[LEXEM_SPAN_COMMENT];
	char genre[LEXEM_SPAN_GENRE];
	
} ADT_track_t;

/****************PROTOTIPOS ADT****************/
status_t ADT_track_new (ADT_track_t ** track);
status_t ADT_track_delete (void * track);
status_t ADT_track_set (char header[], ADT_track_t * track);
status_t ADT_track_get_tag (ADT_track_t * track, char ** str);
status_t ADT_track_get_title (ADT_track_t * track, char ** str);
status_t ADT_track_get_artist (ADT_track_t * track, char ** str);
status_t ADT_track_get_album (ADT_track_t * track, char ** str);
status_t ADT_track_get_year (ADT_track_t * track, char ** str);
status_t ADT_track_get_comment (ADT_track_t * track, char ** str);
status_t ADT_track_get_genre (ADT_track_t * track, char ** str);
status_t ADT_track_export_to_csv (void * track, FILE * file_out);
int ADT_track_compare_by_artist (const void * track1, const void * track2);
int ADT_track_compare_by_title (const void * track1, const void * track2);
/***************FIN PROTOTIPOS ADT***************/

#endif