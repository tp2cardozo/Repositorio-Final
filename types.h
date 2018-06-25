#ifndef TYPES__H
#define TYPES__H

#include <stdio.h>

typedef enum {
	OK = 0,
	ERROR_INVALID_OUTPUT_FILE,
	ERROR_WRITING_TO_FILE,
	ERROR_CLOSING_FILE,
	ERROR_INVALID_MP3_FILE,
	ERROR_INVOCATION,
	ERROR_NULL_POINTER,
	ERROR_OUT_OF_MEMORY
} status_t;

typedef bool {
	TRUE,
	FALSE
} bool_t;

typedef enum {
	DOC_TYPE_CSV = 0,
	DOC_TYPE_XML = 1
} doc_type_t;

typedef enum {
	SORT_TYPE_NAME = 0,
	SORT_TYPE_ARTIST = 1,
	SORT_TYPE_GENRE = 2
} sort_type_t;

typedef struct{
	char * tag;
	char * title;
	char * artist;
	char * album;
	char * year;
	char * comment;
	char * genre;
}mp3_header_t;

#endif