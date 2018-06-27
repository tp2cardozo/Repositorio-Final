#include <stdio.h>
#include <stdlib.h>

#include "errors.h"

char * errors_dictionary[MAX_ERRORS] =
{
	"",
	MSG_ERROR_INVALID_OUTPUT_FILE,
	MSG_ERROR_WRITING_TO_FILE,
	MSG_ERROR_CLOSING_FILE,
	MSG_ERROR_INVALID_MP3_FILE,
	MSG_ERROR_INVOCATION,
	MSG_ERROR_NULL_POINTER,
	MSG_ERROR_OUT_OF_MEMORY,
	MSG_ERROR_OUT_OF_RANGE,
	MSG_ERROR_INVALID_TRACK
};

status_t print_errors(status_t st)
{
	fprintf(stderr, "%s\n", errors_dictionary[st]);
	return OK;
}