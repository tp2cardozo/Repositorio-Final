#ifndef TRACK__H
#define TRACK__H

#include <stdio.h>
#include <stdlib.h>

#include "types.h"
#include "main.h"
#include "errors.h"

#define MAX_GENRES 126

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

typedef struct{
	char tag[LEXEM_SPAN_TAG + 1];
	char title[LEXEM_SPAN_TITLE + 1];
	char artist[LEXEM_SPAN_ARTIST + 1];
	char album[LEXEM_SPAN_ALBUM + 1];
	char year[LEXEM_SPAN_YEAR + 1];
	char comment[LEXEM_SPAN_COMMENT + 1];
	unsigned int genre;
} ADT_track_t;

/****************PROTOTIPOS ADT_TRACK*****************/
status_t ADT_track_new (ADT_track_t ** track);
status_t ADT_track_delete (void * track);
status_t ADT_track_set (char header[], ADT_track_t * track);
status_t ADT_track_export_to_csv (void * track, const void * context, FILE * file_out);
status_t ADT_track_export_to_xml (void * t, const void * context, FILE * file_out); /*FALTA*/
int ADT_track_compare_by_artist (void * track1, void * track2);
int ADT_track_compare_by_title (void * track1, void * track2);
int ADT_track_compare_by_genre (void * t1, void * t2);
/***************FIN PROTOTIPOS ADT_TRACK***************/

#endif