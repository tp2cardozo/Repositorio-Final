#ifndef MP3_PROCESSOR__H
#define MP3_PROCESSOR__H

#include <stdio.h>
#include "types.h"

status_t process_mp3_data(setup_t * setup, FILE * fo, FILE * fi);