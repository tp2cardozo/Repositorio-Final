#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"

/*Biblioteca de formatos*/
char * format_dictionary[MAX_FORMATS] =
{
	CSV_FORMAT,
	XML_FORMAT
};


/*Biblioteca de ordenamientos*/
char * sort_dictionary[MAX_SORTS] =
{
	SORT_BY_NAME,
	SORT_BY_ARTIST,
	SORT_BY_GENRE
};


/**********Externs**********/
extern char context_csv;
extern char * context_xml[MAX_XML_CONTEXTS];
extern status_t (*format_output[MAX_FORMATS])(void *, const void *, FILE *);
extern int (*sort_output[MAX_SORTS]) (void *, void *);
extern char * errors_dictionary[MAX_ERRORS];
extern setup_t setup;
/**********Externs**********/

int main(int argc, char *argv[]) {
	size_t i;
	size_t out_index;
	FILE *file_out, *mp3_file;
	status_t st;
	ADT_Vector_t * vector;
	void * context;

	if((st = validate_arguments(argc, argv, &setup, &out_index)) != OK) {
   		print_errors(st);
		return st;
	}

	if (setup.doc_type == FMT_CSV) {
		context = &context_csv;
	}else{
		context = &context_xml;
	}

	if((st = ADT_Vector_new(&vector)) != OK) {
		print_errors(st);
		return st;
	}


	if((st = ADT_Vector_set_printer (vector, format_output[setup.doc_type])) != OK) {
		print_errors(st);
		return st;
	}

	if((st = ADT_Vector_set_comparator (vector, sort_output[setup.sort_by])) != OK) {
		print_errors(st);
		return st;
	}

	if((st = ADT_Vector_set_destructor(vector, ADT_track_delete)) != OK) {
		print_errors(st);
		return st;
	}

	/*Se abre el archivo de salida*/

	if ((file_out = fopen(argv[out_index], "wt")) == NULL) {
		st = ERROR_INVALID_OUTPUT_FILE;
		fprintf(stderr, "%s\n", errors_dictionary[st]);
		return st;
	}


	/*Aquí se abren los archivos mp3, se processan los datos y luego se cierran*/
	for(i = 0; i < argc - INDEX_FIRST_MP3; i++ ) {

		if((mp3_file = fopen(argv[INDEX_FIRST_MP3 + i], "rt")) == NULL) {
			st = ERROR_INVALID_MP3_FILE;
			print_errors(st);
			return st;
		}

		if((st = process_mp3_data(&setup, mp3_file, vector)) != OK) {
			if((ADT_Vector_delete(&vector)) != OK) {
				print_errors(st);
				return st;
			}

			fclose(mp3_file);
			print_errors(st);

			break;	
		}
	  	fclose(mp3_file);
  	}


  	/*Se ordena el vector donde se ingresaron los datos de los archivos mp3*/
  	if((st = ADT_Vector_sort_elements(&vector, ADT_Vector_swap_elements)) != OK) {
  		print_errors(st);
  		return st;
  	}

  	/*Se imprimen los elementos en el orden y formato elegido*/
	if((st = ADT_Vector_export(vector, context, file_out, setup)) != OK) {
		print_errors(st);
		return st;
	}

	/*Se destruye el vector utilizado*/
	if((st = ADT_Vector_delete(&vector)) != OK) {
		print_errors(st);
		return st;
	}
	/*Se cierra el archivo de salida*/
	fclose(file_out);

	return OK;
}


/*Función que valida los argumentos de la invocación*/
status_t validate_arguments(int argc, char * argv[], setup_t * setup, size_t * index_out_file) {
	size_t i;
	size_t fmt_flag = 0;
	size_t sort_flag = 0;
	size_t out_flag = 0;
	
	if(argv == NULL || setup == NULL)
		return ERROR_NULL_POINTER;

	if(argc < MIN_ARGUMENTS) {
		return ERROR_INVOCATION;
	}

	for(i=0; i<argc; i++)
	{
		if(strcmp(argv[i], FORMAT_FLAG_TOKEN) == 0)
			fmt_flag = i;
		if(strcmp(argv[i], SORT_FLAG_TOKEN) == 0)
			sort_flag = i;
		if(strcmp(argv[i], OUT_FLAG_TOKEN) == 0)
			out_flag = i;
	}

	if(!fmt_flag || !sort_flag || !out_flag)
		return ERROR_INVOCATION;

	for(i=0 ; i < MAX_FORMATS; i++)
	{
		if (!(strcmp(argv[fmt_flag + 1], format_dictionary[i]))) 
		{
			setup->doc_type = i;
			break;
		}
	}

	if(i == MAX_FORMATS)
		return ERROR_INVOCATION;

	for(i=0 ; i < MAX_SORTS ; i++)
	{
		if(!(strcmp(argv[sort_flag + 1], sort_dictionary[i])))
		{
			setup->sort_by = i;
			break;
		}
	}

	if(i == MAX_SORTS)
		return ERROR_INVOCATION;

	*index_out_file = out_flag + 1;

	return OK;
}