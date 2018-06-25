#ifndef VECTOR__H
#define VECTOR__H

#define INIT_CHOP 0

typedef status_t (*destructor_t) (void *);
typedef int (*comparator_t) (const void *, const void *);
typedef status_t (*printer_t) (void *)

typedef struct{
	void ** elements;
	size_t size;
	size_t alloc_size;
	destructor_t destructor;
	comparator_t comparator;
	printer_t printer;
}ADT_Vector_t;

#endif