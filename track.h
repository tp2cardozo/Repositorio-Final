#ifndef TRACK__H
#define TRACK__H

#include <stdio.h>
#include <stdlib.h>

#include "types.h"

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
	char [LEXEM_SPAN_TAG] tag;
	char [LEXEM_SPAN_TITLE] title;
	char [LEXEM_SPAN_ARTIST] artist;
	char [LEXEM_SPAN_ALBUM] album;
	char [LEXEM_SPAN_YEAR] year;
	char [LEXEM_SPAN_COMMENT] comment;
	char [LEXEM_SPAN_GENRE] genre;
} ADT_track_t;

#endif