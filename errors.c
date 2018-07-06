#include <stdio.h>
#include <stdlib.h>

#include "errors.h"

char * errors_dictionary[MAX_ERRORS] =
{
	"",
	MSG_ERROR_INVALID_OUTPUT_FILE,
	MSG_ERROR_WRITING_TO_FILE,
	MSG_ERROR_DISK_SPACE,
	MSG_ERROR_INVALID_MP3_FILE,
	MSG_ERROR_INVOCATION,
	MSG_ERROR_NULL_POINTER,
	MSG_ERROR_OUT_OF_MEMORY,
	MSG_ERROR_OUT_OF_RANGE,
	MSG_ERROR_NOT_IMPLEMENTED
};

status_t print_error(status_t st)
{
	fprintf(stderr, "%s%s\n", "ERROR: ", errors_dictionary[st]);
	return OK;
}