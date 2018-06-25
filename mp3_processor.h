#ifndef MP3_PROCESSOR__H
#define MP3_PROCESSOR__H

#include <stdio.h>
#include "types.h"

#define MAX_HEADER_SIZE 128


status_t process_mp3_data(setup_t * setup, FILE * fi);

status_t get_mp3_header(FILE * fi,const char header[]);

#endif