/*	****************************************************************************************
	Algoritmos y Programación I - 75.02/95.11 - Curso Ing. Martín Cardozo
	Archivo:     mp3reader.c
	Descripcion: Código de ejemplo para mostrar los datos del encabezado de un archivo MP3
	(c) Martín Cardozo
	**************************************************************************************** */
#include <stdio.h>
#include <string.h>


#define MP3_HEADER_SIZE		128


#define LEXEM_START_TAG     0
#define LEXEM_SPAN_TAG      3

#define LEXEM_START_TITLE   3
#define LEXEM_SPAN_TITLE   30

#define LEXEM_START_ARTIST 33
#define LEXEM_SPAN_ARTIST  30

#define LEXEM_START_ALBUM  63
#define LEXEM_SPAN_ALBUM   30

#define LEXEM_START_YEAR   93
#define LEXEM_SPAN_YEAR     4

#define LEXEM_START_COMMENT 97
#define LEXEM_SPAN_COMMENT  30

#define LEXEM_START_GENRE  127
#define LEXEM_SPAN_GENRE     1

typedef enum { OK, ERROR_NULL_POINTER } status_t;


status_t show_mp3_header (const char *, FILE *);

int main (void)
{
    FILE *f;
	size_t length;
    char header[MP3_HEADER_SIZE];


    if ((f = fopen("track.mp3","rb")) == NULL) {
        fprintf(stderr,"%s\n","No se pudo abrir el archivo.");
        return 1;
    }

    fseek(f, 0, SEEK_END);						/* manda el puntero al final del archivo 	*/
    length=ftell(f);							/* da la distancia al comienzo 				*/
    fseek(f,length-MP3_HEADER_SIZE,SEEK_SET);	/* se para en el header MP3 				*/

    fread(header,sizeof(char),MP3_HEADER_SIZE,f);

    show_mp3_header(header,stdout);

    fclose(f);
    return 0;
}

status_t show_mp3_header (const char header[], FILE * fo)
{
    char buf[MP3_HEADER_SIZE];

    if (header == NULL)
       return ERROR_NULL_POINTER;

    memcpy(buf,header+LEXEM_START_TAG,LEXEM_SPAN_TAG);
    buf[LEXEM_SPAN_TAG] = '\0';
    fprintf(fo,"%s%s\n","tag:",buf);

    memcpy(buf,header+LEXEM_START_TITLE,LEXEM_SPAN_TITLE);
    buf[LEXEM_SPAN_TITLE] = '\0';
    fprintf(fo,"%s%s\n","title:",buf);

    memcpy(buf,header+LEXEM_START_ARTIST,LEXEM_SPAN_ARTIST);
    buf[LEXEM_SPAN_ARTIST] = '\0';
    fprintf(fo,"%s%s\n","artist:",buf);

    memcpy(buf,header+LEXEM_START_ALBUM,LEXEM_SPAN_ALBUM);
    buf[LEXEM_SPAN_ALBUM] = '\0';
    fprintf(fo,"%s%s\n","album:",buf);

    memcpy(buf,header+LEXEM_START_YEAR,LEXEM_SPAN_YEAR);
    buf[LEXEM_SPAN_YEAR] = '\0';
    fprintf(fo,"%s%s\n","year:",buf);

    memcpy(buf,header+LEXEM_START_COMMENT,LEXEM_SPAN_COMMENT);
    buf[LEXEM_SPAN_COMMENT] = '\0';
    fprintf(fo,"%s%s\n","comment:",buf);

    memcpy(buf,header+LEXEM_START_GENRE,LEXEM_SPAN_GENRE);
    buf[LEXEM_SPAN_GENRE] = '\0';
    fprintf(fo,"%s%s\n","genre:",buf);

    return OK;
}
/***************************************************archivo main.c****************************************************/
#include <stdio.h>
#include <stdlib.h>

#include "types.h"
#include "errors.h"
#include "setup.h"

#define SALIDA "salida.csv"
#define DELIMITER ','
#define MAX_NAME 100
#define MAX_ARTIST 100
#define MAX_GENRE 100

extern char * errors_dictionary[MAX_ERRORS];
extern setup_t setup;

status_t export_to_csv(char * name, char * artist, char * genre, FILE * file_out, char del);

int main(int argc, char *argv[]) {
	char name[MAX_NAME] = "Muy Punk";
	char artist[MAX_ARTIST] = "La Polla";
	char genre[MAX_GENRE] = "Punk";
	FILE * file_out;
	status_t st;


	file_out = fopen(SALIDA, "wt");
	if (file_out == NULL) {
		st = ERR_INVALID_OUTPUT_FILE;
		fprintf(stderr, "%s\n", errors_dictionary[st]);
		return st;
	}

	if(export_to_csv(name, artist, genre, file_out, DELIMITER))

	if(fclose(file_out) == EOF) {
		st = ERR_CLOSING_FILE;
		fprintf(stderr, "%s\n", errors_dictionary[st]);
		return st;
	}

	return OK;
}

status_t export_to_csv(char * name, char * artist, char * genre, FILE * file_out, char del) {
	status_t st;

	if(fprintf(file_out, "%s", name) < 0) {
		st = ERR_WRITING_TO_FILE; 
		fprintf(stderr, "%s\n", errors_dictionary[st]);
		return st;
	}
	if (fputc(del, file_out) == EOF) {
		st = ERR_WRITING_TO_FILE; 
		fprintf(stderr, "%s\n", errors_dictionary[st]);
		return st;
	}
	if(fprintf(file_out, "%s", artist) < 0) {
		st = ERR_WRITING_TO_FILE; 
		fprintf(stderr, "%s\n", errors_dictionary[st]);
		return st;
	}
	if (fputc(del, file_out) == EOF) {
		st = ERR_WRITING_TO_FILE; 
		fprintf(stderr, "%s\n", errors_dictionary[st]);
		return st;
	}
	if(fprintf(file_out, "%s", genre) < 0) {
		st = ERR_WRITING_TO_FILE; 
		fprintf(stderr, "%s\n", errors_dictionary[st]);
		return st;
	}
	return OK;
}


status_t validate_arguments(int argc, char * argv[], setup_t * setup)
{
	size_t i;
	if(argv == NULL || setup == NULL)
		return ERROR_NULL_POINTER;

	if(argc < MIN_ARGUMENTS)
		return ERROR_INVOCATION;
																																								/*validar argumentos desorden*/
	if(strcmp(argv[FORMAT_FLAG_POSITION], FORMAT_FLAG_TOKEN))
		return ERROR_INVOCATION;

	if(strcmp(argv[SORT_FLAG_POSITION], SORT_FLAG_TOKEN))
		return ERROR_INVOCATION;

	if(strcmp(argv[OUT_FLAG_POSITION], OUT_FLAG_TOKEN))
		return ERROR_INVOCATION;
	
  for(i=0 ; i < MIN_ARGUMENTS ; i++)
  {
    if (!(strcmp(argv[FORMAT_FLAG_POSITION + 1], format_dictionary[i]))) /*Hacer diccionario de formatos*/
    {
     		setup -> doc_type = i;
        break;
    }
    
  }
  
  if(i == MIN_ARGUMENTS)
    return ERRROR_INVOCATION;
  
  for(i=0 ; i < MIN_ARGUMENTS ; i++)
  {
    if(!(strcmp(argv[SORT_FLAG_POSITION + 1], sort_dictionary[i])))
    {
      setup -> sort_by = i;
      break;
    }
  }
	
   if(i == MIN_ARGUMENTS)
    return ERRROR_INVOCATION;

}
/**************************************************errors.c***************************************************/
#include <stdio.h>
#include <stdlib.h>

#include "errors.h"

char * errors_dictionary[MAX_ERRORS] = {
	"",
	MSG_ERROR_INVALID_OUTPUT_FILE,
	MSG_ERROR_WRITING_TO_FILE,
	MSG_ERROR_CLOSING_FILE
};

/**************************************************errors.h***************************************************/

#ifndef ERRORS__H
#define ERRORS__H

#define MAX_ERRORS 4	

#define MSG_ERROR_INVALID_OUTPUT_FILE "Error, archivo de salida inválido."
#define MSG_ERROR_WRITING_TO_FILE "Error al escribir en el archivo."
#define MSG_ERROR_CLOSING_FILE "Error al cerrar archivo."

#endif
/**************************************************types.h***************************************************/
#ifndef TYPES__H
#define TYPES__H

#include <stdio.h>

typedef enum
{
	OK = 0,
	ERR_INVALID_OUTPUT_FILE,
	ERR_WRITING_TO_FILE,
	ERR_CLOSING_FILE

} status_t;

typedef bool
{
	TRUE,
	FALSE

} bool_t;

typedef enum
{
	DOC_TYPE_CSV = 0,
	DOC_TYPE_XML = 1

} doc_type_t;

typedef enum
{
	SORT_TYPE_NAME = 0,
	SORT_TYPE_ARTIST = 1,
	SORT_TYPE_GENRE = 2
	
} sort_type_t;



#endif
/**************************************************setup.h***************************************************/
#ifndef SETUP__H
#define SETUP__H

#include <stdio.h>
#include "types.h"

typedef struct
{
	doc_type_t doc_type;
	sort_type_t sort_by;
	
}setup_t;
/**************************************************setup.c***************************************************/
#include <stdio.h>
#include "setup.h"

setup_t setup
/****************************************************archivo list.h****************************************************/
#ifndef LIST__H
#define LIST__H

#include <stdio.h>
#include "types.h"

typedef struct list_node_t {
	void * data;
	struct list_node_t * next;
}list_node_t, *ADT_list_t;

typedef struct{
	char * tag;
	char * title;
	char * artist;
	char * album;
	char * year;
	char * comment;
	char * genre;
}mp3_record_t;

#endif
/****************************************************archivo list.c****************************************************/
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
/***************************************************archivo vector.h***************************************************/
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
/***************************************************archivo vector.c***************************************************/
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

status_t ADT_Vector_compare (const ADT_Vector_t * v1, const ADT_Vector_t *v2) {
	size_t i;

	if (v1 == NULL || v2 == NULL) return ERROR_NULL_POINTER;
	if (v1->size != v2->size) return ERROR_NOT_EQUAL_VECTOR_TYPE;

	for (i=0; i<v1->size; i++) {
		if()
	}
}
