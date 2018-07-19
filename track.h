#ifndef TRACK__H
#define TRACK__H

#include <stdio.h>
#include <stdlib.h>

#include "types.h"
#include "mp3.h"
#include "contexts.h"

#define XML_TRACK_TAG "<track>"
#define XML_TRACK_END_TAG "</track>"
#define XML_NAME_TAG "<name>"
#define XML_NAME_END_TAG "</name>"
#define XML_ARTIST_TAG "<artist>"
#define XML_ARTIST_END_TAG "</artist>"
#define XML_GENRE_TAG "<genre>"
#define XML_GENRE_END_TAG "</genre>"

typedef struct {
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
status_t ADT_Track_get_info_for_fields (FILE * file, ADT_Track_t * track);
status_t ADT_Track_export_to_csv (void * t, const void * context, FILE * file_out);
status_t ADT_Track_export_to_xml (void * t, const void * context, FILE * file_out);
status_t ADT_Track_export_to_html (void * t, const void * context, FILE * file_out);
int ADT_Track_compare_by_artist (void * t1, void * t2);
int ADT_Track_compare_by_title (void * t1, void * t2);
int ADT_Track_compare_by_genre (void * t1, void * t2);
/***************FIN PROTOTIPOS ADT_TRACK***************/

#endif