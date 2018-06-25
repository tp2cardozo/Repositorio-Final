#ifndef TYPES__H
#define TYPES__H

#include <stdio.h>

typedef enum{
	OK = 0,
	ERROR_INVALID_OUTPUT_FILE,
	ERROR_WRITING_TO_FILE,
	ERROR_CLOSING_FILE,
	ERROR_INVALID_MP3_FILE,
	ERROR_INVOCATION,
	ERROR_NULL_POINTER,
	ERROR_OUT_OF_MEMORY,
	ERROR_OUT_OF_RANGE
} status_t;

typedef enum{
	TRUE,
	FALSE
} bool_t;

typedef enum{
	FMT_CSV = 0,
	FMT_XML = 1
} format_t;

typedef enum{
	SORT_BY_NAME = 0,
	SORT_BY_ARTIST = 1,
	SORT_BY_GENRE = 2
} sort_t;

#endif