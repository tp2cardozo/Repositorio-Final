#ifndef TYPES__H
#define TYPES__H

#include <stdio.h>

typedef enum {
	OK = 0,
	ERR_INVALID_OUTPUT_FILE,
	ERR_WRITING_TO_FILE,
	ERR_CLOSING_FILE
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

#endif