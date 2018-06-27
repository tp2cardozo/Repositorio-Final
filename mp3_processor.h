#ifndef MP3_PROCESSOR__H
#define MP3_PROCESSOR__H

#include <stdio.h>
#include "types.h"
#include "vector.h"
#include "track.h"
#include "errors.h"
#include "setup.h"

#define MAX_HEADER_SIZE 128

status_t process_mp3_data(setup_t * setup, FILE * fi, ADT_Vector_t * vector);
status_t get_mp3_header(FILE * fi, char header[]);

#endif
