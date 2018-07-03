#ifndef MP3_PROCESSOR__H
#define MP3_PROCESSOR__H

#include <stdio.h>
#include "types.h"
#include "vector.h"
#include "track.h"
#include "errors.h"
#include "setup.h"
#include "mp3.h"



/*Prototipos*/
status_t process_mp3_files(setup_t * setup, FILE * fi, ADT_Vector_t ** vector);
status_t process_mp3_file(setup_t * setup, FILE * fi, ADT_Vector_t ** vector);
status_t vector_set (ADT_Vector_t * vector, setup_t * setup);
status_t set_printer_context (doc_type_t doc_type, void ** context);

#endif
