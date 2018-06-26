#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "vector.h"
#include "errors.h"
#include "track.h"

extern char * errors_dictionary[MAX_ERRORS];

int main(int argc, char *argv[]) {
	status_t st;
	bool_t vacio;
	ADT_Vector_t * test;
	ADT_track_t * track;

	size_t length;
	FILE * f;
	char header[MP3_HEADER_SIZE];

	if ((f = fopen("track.mp3","rb")) == NULL) {
        fprintf(stderr,"%s\n","No se pudo abrir el archivo.");
        return 1;
    }

    fseek(f, 0, SEEK_END);						/* manda el puntero al final del archivo 	*/
    length=ftell(f);							/* da la distancia al comienzo 				*/
    fseek(f,length-MP3_HEADER_SIZE,SEEK_SET);	/* se para en el header MP3 				*/

    fread(header,sizeof(char),MP3_HEADER_SIZE,f);

	st = ADT_track_new (&track);
	if (st != OK) {
		fprintf(stderr, "%s\n", errors_dictionary[st]);
		return st;
	}
	printf("Creamos track OK\n");

	st = ADT_track_set (header, track);
	if (st != OK) {
		fprintf(stderr, "%s\n", errors_dictionary[st]);
		return st;
	}
	printf("Seteamos track OK\n");

	st = ADT_Vector_new (&test);
	if (st != OK) {
		fprintf(stderr, "%s\n", errors_dictionary[st]);
		return st;
	}
	printf("Creamos Vector OK\n");

	if ((vacio = ADT_Vector_is_empty(test)) == TRUE) {
		printf("El vector está vacío\n");
	}

	st = ADT_Vector_set_printer(test, ADT_track_export_to_csv);
	if (st != OK) {
		fprintf(stderr, "%s\n", errors_dictionary[st]);
		return st;
	}
	printf("Seteamos printer a \"ADT_track_export_to_csv\"\n");

	st = ADT_Vector_set_comparator(test, ADT_track_compare_by_artist);
	if (st != OK) {
		fprintf(stderr, "%s\n", errors_dictionary[st]);
		return st;
	}
	printf("Seteamos comparator a \"ADT_track_compare_by_artist\"\n");

	st = ADT_Vector_set_destructor(test, ADT_track_delete);
	if (st != OK) {
		fprintf(stderr, "%s\n", errors_dictionary[st]);
		return st;
	}
	printf("Seteamos destructor a \"ADT_track_delete\"\n");

	st = ADT_Vector_append_element(&test, track, ADT_Vector_delete);
	if (st != OK) {
		fprintf(stderr, "%s\n", errors_dictionary[st]);
		return st;
	}
	printf("Le damos 1 valor a el array\n");
	printf("title: %s\n", ((ADT_track_t *)(test->elements[0]))->title);

	st = ADT_Vector_delete (&test);
	if (st != OK) {
		fprintf(stderr, "%s\n", errors_dictionary[st]);
		return st;
	}

	fclose(f);
	printf("Borramos Vector OK\n");
	return OK;
}