#ifndef VECTOR__H
#define VECTOR__H

#include <stdio.h>
#include <stdlib.h>

#include "types.h"
#include "errors.h"

#define INIT_CHOP 4
#define ADT_VECTOR_CHOP_SIZE 4

#define CSV_DELIMITER '|'

typedef status_t (*destructor_t) (void *);

typedef int (*comparator_t) (const void *, const void *);

typedef status_t (*printer_t) (void *, FILE *);


typedef struct{
	void ** elements;
	size_t size;
	size_t alloc_size;
	destructor_t destructor;
	comparator_t comparator;
	printer_t printer;
}ADT_Vector_t;

status_t ADT_Vector_new(ADT_Vector_t ** p);
status_t ADT_Vector_delete (ADT_Vector_t ** p);
void * ADT_Vector_get_element (ADT_Vector_t * v, int position);
status_t ADT_Vector_set_element(ADT_Vector_t ** v, size_t position, void * new_element);
bool_t ADT_Vector_is_empty (ADT_Vector_t * p);
status_t ADT_Vector_set_printer(ADT_Vector_t * v, printer_t pf);
status_t ADT_Vector_set_comparator(ADT_Vector_t * v, comparator_t cf);
status_t ADT_Vector_set_destructor(ADT_Vector_t * v, destructor_t df);
status_t ADT_Vector_export (ADT_Vector_t * v, FILE * file);
status_t ADT_Vector_append_element(ADT_Vector_t ** v, void * element, status_t (*vector_deleter)(ADT_Vector_t **));

#endif
