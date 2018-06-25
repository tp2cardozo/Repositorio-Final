#include <stdio.h>
#include <stdlib.h>

#include "types.h"
#include "vector.h"
#include "errors.h"

extern char * errors_dictionary[MAX_ERRORS];

int main(int argc, char *argv[]) {
	status_t st;
	ADT_Vector_t * test;
	bool_t vacio;

	st = ADT_Vector_new (&test);
	if (st != OK) {
		fprintf(stderr, "%s\n", errors_dictionary[st]);
		return st;
	}
	printf("Creamos Vector OK\n");

	if ((vacio = ADT_Vector_is_empty(test)) == TRUE) {
		printf("El vector está vacío\n");
	}

	st = ADT_Vector_set_printer(test, print_mp3_to_csv);
	if (st != OK) {
		fprintf(stderr, "%s\n", errors_dictionary[st]);
		return st;
	}
	printf("Seteamos printer a \"print_mp3_to_csv\"\n");

	st = ADT_Vector_set_comparator(test, compare_mp3_by_artist);
	if (st != OK) {
		fprintf(stderr, "%s\n", errors_dictionary[st]);
		return st;
	}
	printf("Seteamos comparator a \"compare_mp3_by_artist\"\n");

	st = ADT_Vector_delete (&test);
	if (st != OK) {
		fprintf(stderr, "%s\n", errors_dictionary[st]);
		return st;
	}

	printf("Borramos Vector OK\n");
	return OK;
}