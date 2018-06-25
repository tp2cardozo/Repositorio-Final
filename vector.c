#include <stdio.h>
#include <stdlib.h>

#include "types.h"
#include "vector.h"
#include "errors.h"

extern char * errors_dictionary[MAX_ERRORS];

status_t ADT_Vector_new(ADT_Vector_t ** v) {
	size_t i;

	if (v == NULL) return ERROR_NULL_POINTER;

	if ((*v =(ADT_Vector_t*)malloc(sizeof(ADT_Vector_t))) == NULL)
		return ERROR_OUT_OF_MEMORY;

	if (((*v)->elements = (void**)malloc(INIT_CHOP*sizeof(void*))) == NULL) {
		free(*v);
		*v = NULL;
		return ERROR_OUT_OF_MEMORY;
	}

	for(i=0; i<INIT_CHOP; i++) {
		(*v)->elements[i] = NULL;
	}
	(*v)->alloc_size = INIT_CHOP;

	(*v)->size = 0;
	(*v)->destructor = NULL;
	(*v)->comparator = NULL;
	(*v)->printer = NULL;

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
	if (v == NULL) return NULL;

	if (position < 0) return v->elements[v->size + position];
	if (position > v->size) return NULL;
	
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

status_t ADT_Vector_export (const ADT_Vector_t * v, FILE * file) {
	size_t i;
	status_t st;

	if (v == NULL || file == NULL)
		return ERROR_NULL_POINTER;

	for (i = 0; i < v->size; i++) {
		if ((st = (v->printer)(v->elements[i], file)) != OK)
			return st;
	}
	return OK;
}

status_t ADT_Vector_set_element(ADT_Vector_t ** v, size_t position, void * new_element) {
	if(v==NULL)
		return ERROR_NULL_POINTER;
	
	if(position > (*v)->size)
		return ERROR_OUT_OF_RANGE;
	
	if ((*v)->alloc_size == (*v)->size - 1) {
		(*v)->alloc_size++;
		if (((*v)->elements = (void**)realloc((*v)->alloc_size*sizeof(void*))) == NULL) {
			free(*v);
			*v = NULL;
			return ERROR_OUT_OF_MEMORY;
		}
	}

	if(position < 0) {
		(*v)->elements[(*v)->size + position] = new_element;
		return OK;
	}
	
	(*v)->elements[position]=new_element;
	return OK;
}

status_t print_mp3_to_csv(void * record, FILE * file_out) {
	char del = CSV_DELIMITER;
	char end_line = '\n';
	mp3_header_t * mp3_rec;
	status_t st;

	mp3_rec = (mp3_header_t *)record;

	if(fprintf(file_out, "%s", mp3_rec->title) < 0) {
		st = ERROR_WRITING_TO_FILE; 
		fprintf(stderr, "%s\n", errors_dictionary[st]);
		return st;
	}
	if (fputc(del, file_out) == EOF) {
		st = ERROR_WRITING_TO_FILE; 
		fprintf(stderr, "%s\n", errors_dictionary[st]);
		return st;
	}
	if(fprintf(file_out, "%s", mp3_rec->artist) < 0) {
		st = ERROR_WRITING_TO_FILE; 
		fprintf(stderr, "%s\n", errors_dictionary[st]);
		return st;
	}
	if (fputc(del, file_out) == EOF) {
		st = ERROR_WRITING_TO_FILE; 
		fprintf(stderr, "%s\n", errors_dictionary[st]);
		return st;
	}
	if(fprintf(file_out, "%s", mp3_rec->genre) < 0) {
		st = ERROR_WRITING_TO_FILE; 
		fprintf(stderr, "%s\n", errors_dictionary[st]);
		return st;
	}
	if (fputc(end_line, file_out) == EOF) {
		st = ERROR_WRITING_TO_FILE; 
		fprintf(stderr, "%s\n", errors_dictionary[st]);
		return st;
	}

	return OK;
}

int compare_mp3_by_artist (const void * record1, const void * record2) {
	size_t i;
	mp3_header_t *r1, *r2;

	r1 = (mp3_header_t *)record1;
	r2 = (mp3_header_t *)record2;

	if (record1 == NULL || record2 == NULL)
		return 0;

	for(i=0; r1->artist[i] && r2->artist[i]; i++) {
		if (r1->artist[i] != r2->artist[i]) {
			return (r1->artist[i] - r2->artist[i]);
		}
	}
	if (!r1->artist[i] && r2->artist[i]) {
		return 1;
	}
	if (r1->artist[i] && !r2->artist[i]) {
		return -1;
	}
	return 0;
}

int compare_mp3_by_title (const void * record1, const void * record2) {
	size_t i;
	mp3_header_t *r1, *r2;

	r1 = (mp3_header_t *)record1;
	r2 = (mp3_header_t *)record2;

	if (record1 == NULL || record2 == NULL)
		return 0;

	for(i=0; r1->title[i] && r2->title[i]; i++) {
		if (r1->title[i] != r2->title[i]) {
			return (r1->title[i] - r2->title[i]);
		}
	}
	if (!r1->title[i] && r2->title[i]) {
		return 1;
	}
	if (r1->title[i] && !r2->title[i]) {
		return -1;
	}
	return 0;
}
/*
int compare_mp3_by_genre (const void * record1, const void * record2) {
	mp3_header_t *r1, *r2;

	r1 = (mp3_header_t *)record1;
	r2 = (mp3_header_t *)record2;
	return 0;
}
*/