#include <stdio.h>
#include <stdlib.h>

#include "types.h"

status_t ADT_Vector_new(ADT_Vector_t ** p) {
	size_t i;

	if (p == NULL) return ERROR_NULL_POINTER;

	if ((*p =(ADT_Vector_t*)malloc(sizeof(ADT_Vector_t))) == NULL)
		return ERROR_OUT_OF_MEMORY;

	if (((*p)->elements = (void**)malloc(INIT_CHOP*sizeof(void*))) == NULL) {
		free(*p);
		*p = NULL;
		return ERROR_OUT_OF_MEMORY;
	}

	for(i=0; i<INIT_CHOP; i++) {
		(*p)->elements[i] = NULL;
	}
	(*p)->alloc_size = INIT_CHOP;

	(*p)->size = 0;
	(*p)->destructor = NULL;
	(*p)->comparator = NULL;
	(*p)->printer = NULL;

	return OK;
}

status_t ADT_Vector_delete (ADT_Vector_t ** p) {
	status_t st;
	size_t i;

	for(i=0; i<(*p)->size; i++) {
		st = ((*p)->destructor)((*p)->elements[i]);
		if (st != OK)
			return st;
	}

	free((*p)->elements);
	(*p)->elements = NULL;
	free(*p);
	*p=NULL;
	return OK;
}

void * ADT_Vector_get_element (const ADT_Vector_t * v, int position) {
	if (v==NULL) return ERROR_NULL_POINTER;
	if(position < 0) return v->elements[v->size + position];
	return v->elements[position];
}

bool_t ADT_Vector_is_empty (const ADT_Vector_t * p) {
	return (p->size) ? FALSE:TRUE;
}

status_t ADT_Vector_set_printer(ADT_Vector_t * v, printer_t pf) {
	if(v==NULL) return ERROR_NULL_POINTER;

	v->printer = pf;
	return OK;
}

status_t ADT_Vector_set_comparator(ADT_Vector_t * v, comparator_t cf) {
	if(v==NULL) return ERROR_NULL_POINTER;

	v->comparator = cf;
	return OK;
}

status_t ADT_Vector_set_destructor(ADT_Vector_t * v, destructor_t df) {
	if(v==NULL) return ERROR_NULL_POINTER;

	v->destructor = df;
	return OK;
}

bool_t ADT_Vector_compare (const ADT_Vector_t * v1, const ADT_Vector_t *v2) {
	size_t i;

	if (v1->size != v2->size) return FALSE;

	for (i=0; i<v1->size; i++) {
		if((v1->comparator)(v1->elements[i], v2->elements[i]))
			return FALSE;
	}
	return TRUE;
}