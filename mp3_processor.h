#ifndef MP3_PROCESSOR__H
#define MP3_PROCESSOR__H

#include <stdio.h>
#include "types.h"
#include "errors.h"
#include "setup.h"
#include "mp3.h"
#include "track.h"
#include "vector.h"

/*Prototipos*/
status_t process_mp3_files(int argc, char * argv[], setup_t * setup);
status_t process_mp3_file(setup_t * setup, FILE * fi, ADT_Vector_t * vector);
status_t vector_set (ADT_Vector_t * vector, setup_t * setup);
status_t set_printer_context (doc_type_t doc_type, void ** context);
status_t set_track_from_mp3_file(FILE * fi, ADT_Track_t * track);

#endif
