#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vector.h"
#include "types.h"
#include "contexts.h"

status_t (*vector_exporter[MAX_DOC_TYPES]) (ADT_Vector_t *, const void *, FILE *) = {
	ADT_Vector_export_as_csv,
	ADT_Vector_export_as_xml,
	ADT_Vector_export_as_html
};

/*Esta función crea un nuevo vector*/
status_t ADT_Vector_new(ADT_Vector_t ** v)
{
	size_t i;

	if (v == NULL) return ERROR_NULL_POINTER;

	if ((*v =(ADT_Vector_t*)malloc(sizeof(ADT_Vector_t))) == NULL)
		return ERROR_OUT_OF_MEMORY;

	if (((*v)->elements = (void**)malloc(ADT_VECTOR_INIT_CHOP*sizeof(void*))) == NULL)
	{
		free(*v);
		*v = NULL;
		return ERROR_OUT_OF_MEMORY;
	}

	for(i=0; i<ADT_VECTOR_INIT_CHOP; i++)
	{
		(*v)->elements[i] = NULL;
	}

	(*v)->alloc_size = ADT_VECTOR_INIT_CHOP;

	(*v)->size = 0;
	(*v)->destructor = NULL;
	(*v)->comparator = NULL;
	(*v)->printer = NULL;

	return OK;
}

/*Esta función destruye un vector*/
status_t ADT_Vector_delete (ADT_Vector_t ** v)
{
	status_t st;
	size_t i;
	for(i=0; i<(*v)->size; i++)
	{
		st = ((*v)->destructor)(&((*v)->elements[i]));
		if (st != OK)
			return st;
	}

	free((*v)->elements);
	(*v)->elements = NULL;
	free(*v);
	*v=NULL;
	return OK;
}

/*Esta función devuelve un elemento de un vector por copia, 
siempre hay que pasarle el tamaño del tipo de dato a copiar*/
void * ADT_Vector_get_element (ADT_Vector_t * v, int position, size_t size)
{
	void * copia;

	if (v == NULL) return NULL;

	if (position < 0) 
	{
		memcpy(copia, v->elements[v->size + position], size);
		return copia;
	}

	if (position > v->size) return NULL;
	
	memcpy(copia, v->elements[position], size);
	return copia;
}

/*Esta función se fija si el vector tiene elementos*/
bool_t ADT_Vector_is_empty (ADT_Vector_t * p)
{
	return (p->size) ? FALSE:TRUE;
}

/*Esta función establece una función de impresión de vector*/
status_t ADT_Vector_set_printer(ADT_Vector_t * v, printer_t pf)
{
	if(v==NULL) return ERROR_NULL_POINTER;

	v->printer = pf;
	return OK;
}

/*Esta función establece una función que compara elementos*/
status_t ADT_Vector_set_comparator(ADT_Vector_t * v, comparator_t cf)
{
	if(v==NULL) return ERROR_NULL_POINTER;

	v->comparator = cf;
	return OK;
}

/*Esta función establece una función que destruye elementos*/
status_t ADT_Vector_set_destructor(ADT_Vector_t * v, destructor_t df)
{
	if(v==NULL) return ERROR_NULL_POINTER;

	v->destructor = df;
	return OK;
}

/*Esta función exporta un Vector*/
status_t ADT_Vector_export (ADT_Vector_t * v, const void * context, FILE * file, doc_type_t doc_type)
{
	status_t st;

	if (v == NULL || file == NULL)
		return ERROR_NULL_POINTER;

	if ((st = vector_exporter[doc_type](v, context, file)) != OK)
		return st;
	
	return OK;
}

/*Esta función establece un elemento*/
status_t ADT_Vector_set_element(ADT_Vector_t ** v, size_t position, void * new_element)
{
	status_t st;

	if(v==NULL)
		return ERROR_NULL_POINTER;
	
	if(position > (*v)->size)
		return ERROR_OUT_OF_RANGE;

	if ((st = ((*v)->destructor)(&((*v)->elements[position]))) != OK)
			return st;

	(*v)->elements[position] = new_element;
	return OK;
}

/*Esta función agrega un elemento a un vector*/
status_t ADT_Vector_append_element(ADT_Vector_t ** v, void * element)
{
	size_t i;
	void ** aux;

	if(v == NULL || element == NULL)
		return ERROR_NULL_POINTER;

	i=(*v)->size;
	if(i==(*v)->alloc_size)
	{
		if((aux = realloc((*v)->elements, ((*v)->alloc_size + ADT_VECTOR_CHOP_SIZE)*sizeof(void*))) == NULL)
		{
			return ERROR_OUT_OF_MEMORY;
        }
        free((*v)->elements);
		(*v)->elements = aux;
		(*v)->alloc_size += ADT_VECTOR_CHOP_SIZE;
    }
	(*v)->elements[i] = element;
	((*v)->size)++;

	return OK;
}

/*Esta función ordena por burbujeo, dependiendo del comparador, los elementos de un vector*/
status_t  ADT_Vector_sort_elements (ADT_Vector_t * vector)
{
	size_t i, j = 1;
	void * aux;

	if (vector == NULL)
		return ERROR_NULL_POINTER;

	while (j != 0)
	{
		j = 0;
		for(i = 0; i < vector->size - 1; i++)
		{
			if((vector->comparator)(vector->elements[i], vector->elements[i+1]) > 0)
			{
				aux = vector->elements[i];
				vector->elements[i] = vector->elements[i+1];
				vector->elements[i+1] = aux;
				j++;
			}
		}
	}

	return OK;
}

status_t ADT_Vector_export_as_csv (ADT_Vector_t * v, const void * context, FILE * file) {
	status_t st;
	size_t i;

	for (i = 0; i < v->size; i++)
	{
		if ((st = (v->printer)(v->elements[i], context, file)) != OK)
			return st;
	}
	return OK;
}

status_t ADT_Vector_export_as_xml (ADT_Vector_t * v, const void * context, FILE * file) {
	char ** xml_contexts = NULL;
	status_t st;
	size_t i;

	xml_contexts = (char **)context;

	if(fprintf(file, "%s\n", xml_contexts[XML_PROCESSING_INSTRUCTOR_INDEX]) < 0)
		return ERROR_WRITING_TO_FILE;

	if(fprintf(file, "%s\n", xml_contexts[XML_TRACKS_TAG_INDEX]) < 0)
		return ERROR_WRITING_TO_FILE;

	for (i = 0; i < v->size; i++)
	{
		if ((st = (v->printer)(v->elements[i], context, file)) != OK)
			return st;
	}
	
	if(fprintf(file, "%s\n", xml_contexts[XML_TRACKS_END_TAG_INDEX]) < 0)
		return ERROR_WRITING_TO_FILE;

	return OK;
}

status_t ADT_Vector_export_as_html (ADT_Vector_t * v, const void * context, FILE * file) {
	return ERROR_NOT_IMPLEMENTED;
}