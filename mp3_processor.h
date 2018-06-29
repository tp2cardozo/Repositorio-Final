#ifndef MP3_PROCESSOR__H
#define MP3_PROCESSOR__H

#include <stdio.h>
#include "types.h"
#include "vector.h"
#include "track.h"
#include "errors.h"
#include "setup.h"

#define MAX_FORMATS 2
#define MAX_SORTS 3

#define CSV_FORMAT "csv"
#define XML_FORMAT "xml"

#define SORT_BY_NAME "name"
#define SORT_BY_ARTIST "artist"
#define SORT_BY_GENRE "genre"

#define MAX_HEADER_SIZE 128

/*Prototipos*/
status_t process_mp3_data(setup_t * setup, FILE * fi, ADT_Vector_t ** vector);
status_t get_tracks_from_mp3_files (int argc, char * argv[], ADT_Vector_t ** vector, setup_t * setup);
status_t get_mp3_header(FILE * fi, char header[]);
status_t set_vector_for_tracks (ADT_Vector_t * vector, setup_t * setup);
status_t export_tracks_vector (ADT_Vector_t * vector, char * argv[], void * context, size_t out_index, setup_t * setup);
status_t process_mp3_files (size_t out_index, void * context, int argc, char * argv[], setup_t * setup);

#endif
