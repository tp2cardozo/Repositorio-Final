#include <stdio.h>
#include <stdlib.h>

#include "errors.h"

char * errors_dictionary[MAX_ERRORS] = {
	"",
	MSG_ERROR_INVALID_OUTPUT_FILE,
	MSG_ERROR_WRITING_TO_FILE,
	MSG_ERROR_CLOSING_FILE
};
