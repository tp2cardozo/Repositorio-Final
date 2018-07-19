#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "track.h"

status_t (*track_exports[MAX_DOC_TYPES]) (void *, const void *, FILE *) = 
{
    ADT_Track_export_to_csv,
    ADT_Track_export_to_xml,
    ADT_Track_export_to_html
};

int (*track_comparators[MAX_SORTING_CRITERIA]) (void *, void *) =
{
    ADT_Track_compare_by_title,
    ADT_Track_compare_by_artist,
    ADT_Track_compare_by_genre
};

/*Esta función crea una nueva pista*/
status_t ADT_Track_new (ADT_Track_t ** track)
{
    if (track == NULL)
        return ERROR_NULL_POINTER;

    if ((*track =(ADT_Track_t*)malloc(sizeof(ADT_Track_t))) == NULL)
        return ERROR_OUT_OF_MEMORY;

    (*track)->tag[0] = '\0';
    (*track)->title[0] = '\0';
    (*track)->artist[0] = '\0';
    (*track)->album[0] = '\0';
    (*track)->year[0] = '\0';
    (*track)->comment[0] = '\0';
    (*track)->genre = 0;

    return OK;
}

/*Esta funcion destruye una pista*/
status_t ADT_Track_delete (void * track)
{
    ADT_Track_t ** track_p;

    if (track == NULL)
        return ERROR_NULL_POINTER;

    track_p = (ADT_Track_t **)track; 

    free(*track_p);
    track = NULL;

    return OK;
}

/*Esta función establece una pista desde un archivo MP3*/
status_t ADT_Track_get_info_for_fields (FILE * file, ADT_Track_t * track)
{
    char header[MAX_HEADER_SIZE];
    status_t st;

    /*ante una ampliación se debería agregar un switch acá con los distintos 
    formatos de archivos de música, en este trabajo sólo utilizamos archivos
    MP3 ID3v1*/

    if (file == NULL || track == NULL)
        return ERROR_NULL_POINTER;

    if((st = get_mp3_header(file, header)) != OK) 
        return st;

    if ((st = parse_mp3_header(header, track->tag, track->title, track->artist, track->album, track->year, track->comment, &(track->genre))) != OK)
        return st;

    return OK;
}

/*Esta función exporta una pista a un archivo csv*/
status_t ADT_Track_export_to_csv (void * t, const void * context, FILE * file_out)
{
    char * del;
    ADT_Track_t * track;

    del = (char *)context;
    track = (ADT_Track_t *)t;

    if(fprintf(file_out, "%s%c", track->title, *del) < 0)
        return ERROR_WRITING_TO_FILE;
  
    if(fprintf(file_out, "%s%c", track->artist, *del) < 0)
        return ERROR_WRITING_TO_FILE;

    if(fprintf(file_out, "%s\n", get_genre_name(track->genre)) < 0)
        return ERROR_WRITING_TO_FILE;

    return OK;
}

/*Esta función exporta una pista a un archivo csv*/
status_t ADT_Track_export_to_xml (void * t, const void * context, FILE * file_out)
{
    char ** xml_context;
    ADT_Track_t * track;

    xml_context = (char**)context;
    track = (ADT_Track_t *)t;

    if(fprintf(file_out, "\t%s\n", xml_context[XML_TRACK_TAG_INDEX]) < 0)
        return ERROR_WRITING_TO_FILE;

    if(fprintf(file_out, "\t\t%s", xml_context[XML_NAME_TAG_INDEX]) < 0)
        return ERROR_WRITING_TO_FILE;

    if(fprintf(file_out, "%s", track->title) < 0)
        return ERROR_WRITING_TO_FILE;

    if(fprintf(file_out, "%s\n", xml_context[XML_NAME_END_TAG_INDEX]) < 0)
        return ERROR_WRITING_TO_FILE;

    if(fprintf(file_out, "\t\t%s", xml_context[XML_ARTIST_TAG_INDEX]) < 0)
        return ERROR_WRITING_TO_FILE;

    if(fprintf(file_out, "%s", track->artist) < 0)
        return ERROR_WRITING_TO_FILE;

    if(fprintf(file_out, "%s\n", xml_context[XML_ARTIST_END_TAG_INDEX]) < 0)
        return ERROR_WRITING_TO_FILE;

    if(fprintf(file_out, "\t\t%s", xml_context[XML_GENRE_TAG_INDEX]) < 0)
        return ERROR_WRITING_TO_FILE;

    if(fprintf(file_out, "%s", get_genre_name(track->genre)) < 0)
        return ERROR_WRITING_TO_FILE;

    if(fprintf(file_out, "%s\n", xml_context[XML_GENRE_END_TAG_INDEX]) < 0)
        return ERROR_WRITING_TO_FILE;

    if(fprintf(file_out, "\t%s\n", xml_context[XML_TRACK_END_TAG_INDEX]) < 0)
        return ERROR_WRITING_TO_FILE;

    return OK;
}

status_t ADT_Track_export_to_html (void * t, const void * context, FILE * file_out) {
    return ERROR_NOT_IMPLEMENTED;
}

/*Esta función compara dos pistas según el artista*/
int ADT_Track_compare_by_artist (void * t1, void * t2)
{
    ADT_Track_t *track1, *track2;

    track1 = (ADT_Track_t *)t1;
    track2 = (ADT_Track_t *)t2;

    if (track1 == NULL || track2 == NULL)
        return 0;

    return strcmp(track1->artist, track2->artist);
}

/*Esta función compara dos pistas segun el nombre*/
int ADT_Track_compare_by_title (void * t1, void * t2)
{
    ADT_Track_t *track1, *track2;

    track1 = (ADT_Track_t *)t1;
    track2 = (ADT_Track_t *)t2;

    if (t1 == NULL || t2 == NULL)
        return 0;
    
    return strcmp(track1->title, track2->title);
}

/*Esta función compara dos pistas segun el género*/
int ADT_Track_compare_by_genre (void * t1, void * t2)
{
    ADT_Track_t *track1, *track2;

    if (t1 == NULL || t2 == NULL)
        return 0;

    track1 = (ADT_Track_t *)t1;
    track2 = (ADT_Track_t *)t2;

    return track1->genre - track2->genre;
}