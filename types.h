#ifndef TYPES__H
#define TYPES__H

#include <stdio.h>

#define MAX_DOC_TYPES 3
#define MAX_SORTING_CRITERIA 3

/*Define el tipo status_t*/
typedef enum
{
	OK = 0,
	ERROR_INVALID_OUTPUT_FILE,
	ERROR_WRITING_TO_FILE,
	ERROR_DISK_SPACE,
	ERROR_INVALID_MP3_FILE,
	ERROR_INVOCATION,
	ERROR_NULL_POINTER,
	ERROR_OUT_OF_MEMORY,
	ERROR_OUT_OF_RANGE,
	ERROR_NOT_IMPLEMENTED,
	ERROR_INAVLID_DOC_FORMAT,	
	ERROR_INVALID_SORTING_TYPE,
	ERROR_MISSING_ARGUMENTS
} status_t;

/*Define el tipo bool_t*/
typedef enum
{
	TRUE,
	FALSE
} bool_t;

/*Define el tipo format_t*/
typedef enum
{
	DOC_TYPE_CSV,
	DOC_TYPE_XML,
	DOC_TYPE_HTML
} doc_type_t;

/*Define el tipo sort_t*/
typedef enum
{
	SORT_BY_NAME,
	SORT_BY_ARTIST,
	SORT_BY_GENRE
} sorting_criterium_t;

typedef status_t (*destructor_t) (void *);
typedef int (*comparator_t) (void *, void *);
typedef status_t (*printer_t) (void *, const void *, FILE *);

#endif