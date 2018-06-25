#include <stdio.h>

#include "types.h"

void ADT_destroy_list (ADT_list_t * l, void (*destroy)(void**)) {
	ADT_list_t tmp;

	while (*l != NULL) {
		destroy(&((*l)->data));
		tmp=(*l)->next;
		free(*l);
		*l=tmp;
	}
}

bool_t ADT_list_is_empty (ADT_list_t l) {
	return (l == NULL) ? TRUE:FALSE;
}

status_t ADT_list_create_empty_list (ADT_list_t * l) {
	if(l == NULL) {
		*l = NULL;
		return OK;
	}
	return ERROR_EXISTING_LIST;
}

status_t ADT_list_create_node (list_node_t ** node, const void * data) {
	
	if (data == NULL || node == NULL) return ERROR_NULL_POINTER;
	
	if((*node = (list_node_t *)malloc(sizeof(list_node_t))) == NULL) return ERROR_OUT_OF_MEMORY;
	
	(*node)->data = data;
	(*node)->next = NULL;
	
	return OK;
}

status_t ADT_list_destroy_node (list_node_t ** node, status_t (*pf) (void*)) {
	if(node == NULL) return ERROR_NULL_POINTER;
	
}