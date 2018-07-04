#ifndef TRACK__H
#define TRACK__H

#include <stdio.h>
#include <stdlib.h>

#include "types.h"
#include "main.h"
#include "mp3.h"
#include "types.h"


#define XML_TRACK_FLAG "track"
#define XML_NAME_FLAG "name"
#define XML_ARTIST_FLAG "artist"
#define XML_GENRE_FLAG "genre"

typedef struct
{
	char tag[LEXEM_SPAN_TAG + 1];
	char title[LEXEM_SPAN_TITLE + 1];
	char artist[LEXEM_SPAN_ARTIST + 1];
	char album[LEXEM_SPAN_ALBUM + 1];
	char year[LEXEM_SPAN_YEAR + 1];
	char comment[LEXEM_SPAN_COMMENT + 1];
	unsigned char genre;
} ADT_Track_t;

/****************PROTOTIPOS ADT_TRACK*****************/
status_t ADT_Track_new (ADT_Track_t ** track);
status_t ADT_Track_delete (void * track);
status_t ADT_Track_set (char header[], ADT_Track_t * track);
status_t ADT_Track_export_to_csv (void * track, const void * context, FILE * file_out);
status_t ADT_Track_export_to_xml (void * t, const void * context, FILE * file_out); /*FALTA*/
int ADT_Track_compare_by_artist (void * track1, void * track2);
int ADT_Track_compare_by_title (void * track1, void * track2);
int ADT_Track_compare_by_genre (void * t1, void * t2);
/***************FIN PROTOTIPOS ADT_TRACK***************/

#endif