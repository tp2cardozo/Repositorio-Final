#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "track.h"

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
status_t ADT_Track_delete (void * t)
{
    ADT_Track_t * track;

    track = (ADT_Track_t *)t; 

    if (track == NULL)
        return ERROR_NULL_POINTER;

    free(*track);
    *track = NULL;

    return OK;
}

/*Esta función establece una pista*/
status_t ADT_Track_get_info_for_fields (char * header[], ADT_Track_t * track)
{
    if (header == NULL || track == NULL)
       return ERROR_NULL_POINTER;

    strcpy(track->tag, header[HEADER_FIELDS_TAG_INDEX]);
    strcpy(track->title, header[HEADER_FIELDS_TITLE_INDEX]);
    strcpy(track->artist, header[HEADER_FIELDS_ARTIST_INDEX]);
    strcpy(track->album, header[HEADER_FIELDS_ALBUM_INDEX]);
    strcpy(track->year, header[HEADER_FIELDS_YEAR_INDEX]);
    strcpy(track->comment, header[HEADER_FIELDS_COMMENT_INDEX]);
    track->genre = *(header[HEADER_FIELDS_GENRE_INDEX]);

    return OK;
}

/*Esta función exporta una pista a un archivo csv*/
status_t ADT_Track_export_to_csv (void * t, const void * context, FILE * file_out)
{
    char * del;
    ADT_Track_t * track;

    del = (char *)context;
    track = (ADT_Track_t *)t;

    if(fprintf(file_out, "%s%s", track->title, del) < 0)
        return ERROR_WRITING_TO_FILE;
  
    if(fprintf(file_out, "%s%s", track->artist, del) < 0)
        return ERROR_WRITING_TO_FILE;

    if(fprintf(file_out, "%s\n", genres_dictionary[track->genre]) < 0)
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

    if(fprintf(file_out, "\t%s%s%s\n", xml_context[XML_OPEN_INITIAL_BRACKET_INDEX], xml_context[XML_TRACK_FLAG_INDEX], xml_context[XML_CLOSE_BRACKET_INDEX]) < 0)
        return ERROR_WRITING_TO_FILE;

    if(fprintf(file_out, "\t\t%s%s%s", xml_context[XML_OPEN_INITIAL_BRACKET_INDEX], xml_context[XML_NAME_FLAG_INDEX], xml_context[XML_CLOSE_BRACKET_INDEX]) < 0)
        return ERROR_WRITING_TO_FILE;

    if(fprintf(file_out, "%s", track->title) < 0)
        return ERROR_WRITING_TO_FILE;

    if(fprintf(file_out, "%s%s%s\n", xml_context[XML_OPEN_FINISHER_BRACKET_INDEX], xml_context[XML_NAME_FLAG_INDEX], xml_context[XML_CLOSE_BRACKET_INDEX]) < 0)
        return ERROR_WRITING_TO_FILE;

    if(fprintf(file_out, "\t\t%s%s%s", xml_context[XML_OPEN_INITIAL_BRACKET_INDEX], xml_context[XML_ARTIST_FLAG_INDEX], xml_context[XML_CLOSE_BRACKET_INDEX]) < 0)
        return ERROR_WRITING_TO_FILE;

    if(fprintf(file_out, "%s", track->artist) < 0)
        return ERROR_WRITING_TO_FILE;

    if(fprintf(file_out, "%s%s%s\n", xml_context[XML_OPEN_FINISHER_BRACKET_INDEX], xml_context[XML_ARTIST_FLAG_INDEX], xml_context[XML_CLOSE_BRACKET_INDEX]) < 0)
        return ERROR_WRITING_TO_FILE;

    if(fprintf(file_out, "\t\t%s%s%s", xml_context[XML_OPEN_INITIAL_BRACKET_INDEX], xml_context[XML_GENRE_FLAG_INDEX], xml_context[XML_CLOSE_BRACKET_INDEX]) < 0)
        return ERROR_WRITING_TO_FILE;

    if(fprintf(file_out, "%s", genres_dictionary[track->genre]) < 0)
        return ERROR_WRITING_TO_FILE;

    if(fprintf(file_out, "%s%s%s\n", xml_context[XML_OPEN_FINISHER_BRACKET_INDEX], xml_context[XML_GENRE_FLAG_INDEX], xml_context[XML_CLOSE_BRACKET_INDEX]) < 0)
        return ERROR_WRITING_TO_FILE;

    if(fprintf(file_out, "\t%s%s%s\n", xml_context[XML_OPEN_FINISHER_BRACKET_INDEX], xml_context[XML_TRACK_FLAG_INDEX], xml_context[XML_CLOSE_BRACKET_INDEX]) < 0)
        return ERROR_WRITING_TO_FILE;

    return OK;
}

/*Esta función compara dos pistas según el artista*/
int ADT_Track_compare_by_artist (void * t1, void * t2)
{
    size_t i;
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
    size_t i;
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