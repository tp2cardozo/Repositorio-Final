#ifndef MP3__H
#define MP3__H

#include <stdio.h>
#include "types.h"

#define MAX_HEADER_SIZE 128

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

#define HEADER_FIELDS_TAG_INDEX 0
#define HEADER_FIELDS_TITLE_INDEX 1
#define HEADER_FIELDS_ARTIST_INDEX 2
#define HEADER_FIELDS_ALBUM_INDEX 3
#define HEADER_FIELDS_YEAR_INDEX 4
#define HEADER_FIELDS_COMMENT_INDEX 5
#define HEADER_FIELDS_GENRE_INDEX 6

#define MAX_HEADER_FIELDS 7

status_t set_track_from_mp3_file(FILE * fi, ADT_Track_t * track);
status_t get_info_from_header(char * header, char * fields[]);
status_t get_mp3_header(FILE * fi, char header[]);

#endif