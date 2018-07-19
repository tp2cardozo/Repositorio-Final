#include <stdio.h>
#include <stdlib.h>

#include "mp3_processor.h"

extern status_t (*track_exports[MAX_FORMAT_TYPES]) (void *, const void *, FILE *);
extern int (*track_comparators[MAX_SORTING_CRITERIA]) (void *, void *);
extern char * context_csv;
extern char * context_xml[MAX_XML_CONTEXTS];

status_t process_mp3_files(int max_input_files, char * input_files[], setup_t * setup) 
{
	ADT_Vector_t * tracks;
	size_t i;
	void * context = NULL;
	FILE * file_out, * mp3_file;
	status_t st;


	if((st = ADT_Vector_new(&tracks)) != OK)
		return st;
	
	if((st = set_printer_context(setup->doc_type, &context)) != OK)
	{
		ADT_Vector_delete(&tracks);
		return st;
	}

	if((st = ADT_Vector_set_printer (tracks, track_exports[setup->doc_type])) != OK) 
	{
		ADT_Vector_delete(&tracks);
		return st;
	}
	
	if((st = ADT_Vector_set_comparator (tracks, track_comparators[setup->sorting_criteria])) != OK)
	{
		ADT_Vector_delete(&tracks);
		return st;
	}

	if((st = ADT_Vector_set_destructor(tracks, ADT_Track_delete)) != OK)
	{
		ADT_Vector_delete(&tracks);
		return st;
	}


	for(i = 0; i < max_input_files; i++ )
	{

		if((mp3_file = fopen(input_files[i], "rt")) == NULL)
		{
			ADT_Vector_delete(&tracks);
			return ERROR_INVALID_MP3_FILE;
		}
		

		if((st = process_mp3_file(setup, mp3_file, tracks)) != OK)
		{
			ADT_Vector_delete(&tracks);
			fclose(mp3_file);
			return st;	
		}

	  	if((fclose(mp3_file)) == EOF)
	  	{
	  		ADT_Vector_delete(&tracks);
	  
			return ERROR_DISK_SPACE;
	  	}
  	}

  	if((st = ADT_Vector_sort_elements(&tracks)) != OK)
  	{
  		ADT_Vector_delete(&tracks);
  		return st;
  	}

  	if ((file_out = fopen(setup->output_file_path, "wt")) == NULL)
	{
		st = ERROR_INVALID_OUTPUT_FILE;
		ADT_Vector_delete(&tracks);
		return st;
	}

  	if((st = ADT_Vector_export(tracks, context, file_out, setup->doc_type)) != OK)
	{
		ADT_Vector_delete(&tracks);
		fclose(file_out);
		return st;
	}


  	if((st = ADT_Vector_delete(&tracks)) != OK)
	{
		fclose(file_out);
		return st;
	}

	if((fclose(file_out)) == EOF)
		return ERROR_DISK_SPACE;


	return OK;
}

/*Esta función se ocupa de insertar un track en un vector de tracks*/
status_t process_mp3_file(setup_t * setup, FILE * fi, ADT_Vector_t * tracks)
{
	status_t st;
	ADT_Track_t * track;

	if(setup == NULL || fi == NULL || tracks == NULL)
		return ERROR_NULL_POINTER;

	if((st = ADT_Track_new(&track)) != OK)
		return st;

	if((st = set_track_from_mp3_file(fi, track)) != OK)
	{
		ADT_Track_delete(&track);
		return st;
	}

	if((st = ADT_Vector_append_element(&tracks, track)) != OK)
		return st;

	return OK;	
}

status_t set_printer_context (doc_type_t doc_type, void ** context) 
{
	if (context == NULL)
		return ERROR_NULL_POINTER;

	switch (doc_type) 
	{
		case DOC_TYPE_XML :
			*context = context_xml;
			break;

		case DOC_TYPE_CSV :
			*context = context_csv;
			break;

		case DOC_TYPE_HTML :
			return ERROR_NOT_IMPLEMENTED;
	}
	return OK;
}

status_t set_track_from_mp3_file(FILE * fi, ADT_Track_t * track)
{
	char header[MAX_HEADER_SIZE];
    status_t st;

	if (fi == NULL || track == NULL)
		return ERROR_NULL_POINTER;

	if((st = get_mp3_header(fi, header)) != OK) 
        return st;

    if((st = ADT_Track_get_info_for_fields(header, track)) != OK)
        return st;

    return OK;
}
