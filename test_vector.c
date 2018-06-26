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
	ADT_track_t *track1, *track2;

	size_t length;
	FILE * f;
	char header[MP3_HEADER_SIZE];

	if ((f = fopen("track1.mp3","rb")) == NULL) {
        fprintf(stderr,"%s\n","No se pudo abrir el archivo.");
        return 1;
    }

    fseek(f, 0, SEEK_END);						/* manda el puntero al final del archivo 	*/
    length=ftell(f);							/* da la distancia al comienzo 				*/
    fseek(f,length-MP3_HEADER_SIZE,SEEK_SET);	/* se para en el header MP3 				*/

    fread(header,sizeof(char),MP3_HEADER_SIZE,f);

	fclose(f);

	st = ADT_track_new (&track1);
	if (st != OK) {
		fprintf(stderr, "%s\n", errors_dictionary[st]);
		return st;
	}
	printf("Creamos track1 OK\n");

	st = ADT_track_set (header, track1);
	if (st != OK) {
		fprintf(stderr, "%s\n", errors_dictionary[st]);
		return st;
	}
	printf("Seteamos track1 OK\n");

	if ((f = fopen("track2.mp3","rb")) == NULL) {
        fprintf(stderr,"%s\n","No se pudo abrir el archivo.");
        return 1;
    }

    fseek(f, 0, SEEK_END);						/* manda el puntero al final del archivo 	*/
    length=ftell(f);							/* da la distancia al comienzo 				*/
    fseek(f,length-MP3_HEADER_SIZE,SEEK_SET);	/* se para en el header MP3 				*/

    fread(header,sizeof(char),MP3_HEADER_SIZE,f);

	fclose(f);

	st = ADT_track_new (&track2);
	if (st != OK) {
		fprintf(stderr, "%s\n", errors_dictionary[st]);
		return st;
	}
	printf("Creamos track2 OK\n");

	st = ADT_track_set (header, track2);
	if (st != OK) {
		fprintf(stderr, "%s\n", errors_dictionary[st]);
		return st;
	}
	printf("Seteamos track2 OK\n");

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

	st = ADT_Vector_append_element(&test, track1, ADT_Vector_delete);
	if (st != OK) {
		fprintf(stderr, "%s\n", errors_dictionary[st]);
		return st;
	}
	printf("\n");
	printf("Le damos 1er valor a el array\n");
	printf("tag: %s\n", ((ADT_track_t *)(test->elements[0]))->tag);
	printf("title: %s\n", ((ADT_track_t *)(test->elements[0]))->title);
	printf("artist: %s\n", ((ADT_track_t *)(test->elements[0]))->artist);
	printf("album: %s\n", ((ADT_track_t *)(test->elements[0]))->album);
	printf("year: %s\n", ((ADT_track_t *)(test->elements[0]))->year);
	printf("comment: %s\n", ((ADT_track_t *)(test->elements[0]))->comment);
	printf("year: %s\n", ((ADT_track_t *)(test->elements[0]))->year);

	st = ADT_Vector_append_element(&test, track2, ADT_Vector_delete);
	if (st != OK) {
		fprintf(stderr, "%s\n", errors_dictionary[st]);
		return st;
	}
	printf("\n");
	printf("Le damos 2do valor a el array\n");
	printf("tag: %s\n", ((ADT_track_t *)(test->elements[1]))->tag);
	printf("title: %s\n", ((ADT_track_t *)(test->elements[1]))->title);
	printf("artist: %s\n", ((ADT_track_t *)(test->elements[1]))->artist);
	printf("album: %s\n", ((ADT_track_t *)(test->elements[1]))->album);
	printf("year: %s\n", ((ADT_track_t *)(test->elements[1]))->year);
	printf("comment: %s\n", ((ADT_track_t *)(test->elements[1]))->comment);
	printf("genre: %s\n", ((ADT_track_t *)(test->elements[1]))->genre);

	qsort(test->elements[0], test->size, sizeof(ADT_track_t *), test->comparator);

	printf("nuevo orden\n");
	printf("artist: %s\n", ((ADT_track_t *)(test->elements[0]))->artist);
	printf("artist: %s\n", ((ADT_track_t *)(test->elements[1]))->artist);

	st = ADT_Vector_delete (&test);
	if (st != OK) {
		fprintf(stderr, "%s\n", errors_dictionary[st]);
		return st;
	}

	printf("Borramos Vector OK\n");
	return OK;
}