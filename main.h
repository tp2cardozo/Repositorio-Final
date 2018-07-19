#ifndef MAIN__H
#define MAIN__H

#include <stdio.h>

#include "types.h"
#include "setup.h"

#define MIN_ARGUMENTS 8
#define FIRST_MP3_FILE_INDEX 7

#define CSV_FORMAT_STR "csv"
#define XML_FORMAT_STR "xml"
#define HTML_FORMAT_STR "html"

#define SORT_BY_NAME_STR "name"
#define SORT_BY_ARTIST_STR "artist"
#define SORT_BY_GENRE_STR "genre"

/*Tokens*/
#define FORMAT_FLAG_TOKEN "-fmt"
#define SORT_FLAG_TOKEN "-sort"
#define OUT_FLAG_TOKEN "-out"

/*Prototipo*/
status_t validate_arguments(int argc, char * argv[], setup_t * setup);

#endif