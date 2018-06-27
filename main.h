#ifndef MAIN__H
#define MAIN__H

#include <stdio.h>

#include "types.h"
#include "mp3_processor.h"
#include "vector.h"
#include "errors.h"
#include "track.h"
#include "setup.h"

#define MIN_ARGUMENTS 8
#define INDEX_FIRST_MP3 7
#define MAX_FORMATS 2
#define MAX_SORTS 3

#define CSV_FORMAT "csv"
#define XML_FORMAT "xml"

#define SORT_BY_NAME "name"
#define SORT_BY_ARTIST "artist"
#define SORT_BY_GENRE "genre"

#define FORMAT_FLAG_TOKEN "-fmt"
#define SORT_FLAG_TOKEN "-sort"
#define OUT_FLAG_TOKEN "-out"

status_t validate_arguments(int argc, char * argv[], setup_t * setup, size_t * index_out_file);

#endif