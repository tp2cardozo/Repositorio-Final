#ifndef MAIN__H
#define MAIN__H

#include <stdio.h>

#include "types.h"
#include "mp3_processor.h"
#include "vector.h"
#include "errors.h"
#include "track.h"
#include "setup.h"
#include "contexts.h"

#define MIN_ARGUMENTS 8
#define INDEX_FIRST_MP3_FILE 7

/*Tokens*/
#define FORMAT_FLAG_TOKEN "-fmt"
#define SORT_FLAG_TOKEN "-sort"
#define OUT_FLAG_TOKEN "-out"

/*Prototipo*/
status_t validate_arguments(int argc, char * argv[], setup_t * setup, size_t * index_out_file, void ** context);
status_t set_printer_context (setup_t * setup, void ** context);

#endif