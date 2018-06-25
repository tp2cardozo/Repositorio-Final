#ifndef LIST__H
#define LIST__H

#include <stdio.h>
#include "types.h"

typedef struct list_node_t {
	void * data;
	struct list_node_t * next;
}list_node_t, *ADT_list_t;

#endif