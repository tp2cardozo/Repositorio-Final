#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "track.h"
#include "errors.h"
#include "main.h"

extern char * errors_dictionary[MAX_ERRORS];

status_t (*format_output[MAX_FORMATS]) (void *, FILE *) =  {
    ADT_track_export_to_csv,
    ADT_track_export_to_xml /*falta codificar*/
};

int (*sort_output[MAX_SORTS]) (void *, void *) = {
    ADT_track_compare_by_title,
    ADT_track_compare_by_artist,
    ADT_track_compare_by_genre/*falta codificar*/
};

status_t ADT_track_new (ADT_track_t ** track) {
    if (track == NULL)
        return ERROR_NULL_POINTER;

    if ((*track =(ADT_track_t*)malloc(sizeof(ADT_track_t))) == NULL)
        return ERROR_OUT_OF_MEMORY;

    (*track)->tag[0] = '\0';
    (*track)->title[0] = '\0';
    (*track)->artist[0] = '\0';
    (*track)->album[0] = '\0';
    (*track)->year[0] = '\0';
    (*track)->comment[0] = '\0';
    (*track)->genre[0] = '\0';

    return OK;
}

status_t ADT_track_delete (void * t) {
    ADT_track_t * track;

    track = (ADT_track_t *)t; 

    if (track == NULL)
        return ERROR_NULL_POINTER;

    track->tag[0] = '\0';
    track->title[0] = '\0';
    track->artist[0] = '\0';
    track->album[0] = '\0';
    track->year[0] = '\0';
    track->comment[0] = '\0';
    track->genre[0] = '\0';

    free(track);
    track = NULL;

    return OK;
}

status_t ADT_track_set (char header[], ADT_track_t * track) {
    if (header == NULL || track == NULL)
       return ERROR_NULL_POINTER;

    memcpy(track->tag,header+LEXEM_START_TAG,LEXEM_SPAN_TAG);
    track->tag[LEXEM_SPAN_TAG] = '\0';

    memcpy(track->title,header+LEXEM_START_TITLE,LEXEM_SPAN_TITLE);
    track->title[LEXEM_SPAN_TITLE] = '\0';

    memcpy(track->artist,header+LEXEM_START_ARTIST,LEXEM_SPAN_ARTIST);
    track->artist[LEXEM_SPAN_ARTIST] = '\0';

    memcpy(track->album,header+LEXEM_START_ALBUM,LEXEM_SPAN_ALBUM);
    track->album[LEXEM_SPAN_ALBUM] = '\0';

    memcpy(track->year,header+LEXEM_START_YEAR,LEXEM_SPAN_YEAR);
    track->year[LEXEM_SPAN_YEAR] = '\0';

    memcpy(track->comment,header+LEXEM_START_COMMENT,LEXEM_SPAN_COMMENT);
    track->comment[LEXEM_SPAN_COMMENT] = '\0';

    memcpy(track->genre,header+LEXEM_START_GENRE,LEXEM_SPAN_GENRE);
    track->genre[LEXEM_SPAN_GENRE] = '\0';

    return OK;
}

status_t ADT_track_get_tag (ADT_track_t * track, char ** str) {
    size_t len;

    len = strlen(track->tag);

    if (((*str) = (char*)malloc((len+1)*sizeof(char))) == NULL) 
        return ERROR_OUT_OF_MEMORY;

    memcpy((*str), track->tag, LEXEM_SPAN_TAG);

    return OK;
}

status_t ADT_track_get_title (ADT_track_t * track, char ** str) {
    size_t len;

    len = strlen(track->title);

    if (((*str) = (char*)malloc((len+1)*sizeof(char))) == NULL) 
        return ERROR_OUT_OF_MEMORY;

    memcpy((*str), track->title, LEXEM_SPAN_TITLE);

    return OK;
}

status_t ADT_track_get_artist (ADT_track_t * track, char ** str) {
    size_t len;

    len = strlen(track->artist);

    if (((*str) = (char*)malloc((len+1)*sizeof(char))) == NULL) 
        return ERROR_OUT_OF_MEMORY;

    memcpy((*str), track->artist, LEXEM_SPAN_ARTIST);

    return OK;
}

status_t ADT_track_get_album (ADT_track_t * track, char ** str) {
    size_t len;

    len = strlen(track->album);

    if (((*str) = (char*)malloc((len+1)*sizeof(char))) == NULL) 
        return ERROR_OUT_OF_MEMORY;

    memcpy((*str), track->album, LEXEM_SPAN_ALBUM);

    return OK;
}

status_t ADT_track_get_year (ADT_track_t * track, char ** str) {
    size_t len;

    len = strlen(track->year);

    if (((*str) = (char*)malloc((len+1)*sizeof(char))) == NULL) 
        return ERROR_OUT_OF_MEMORY;

    memcpy((*str), track->year, LEXEM_SPAN_YEAR);

    return OK;
}

status_t ADT_track_get_comment (ADT_track_t * track, char ** str) {
    size_t len;

    len = strlen(track->comment);

    if (((*str) = (char*)malloc((len+1)*sizeof(char))) == NULL) 
        return ERROR_OUT_OF_MEMORY;

    memcpy((*str), track->comment, LEXEM_SPAN_COMMENT);

    return OK;
}

status_t ADT_track_get_genre (ADT_track_t * track, char ** str) {
    size_t len;

    len = strlen(track->genre);

    if (((*str) = (char*)malloc((len+1)*sizeof(char))) == NULL) 
        return ERROR_OUT_OF_MEMORY;

    memcpy((*str), track->genre, LEXEM_SPAN_GENRE);

    return OK;
}

status_t ADT_track_export_to_xml (void * t, FILE * file_out) {
    /*EDITAR*/
    char del = CSV_DELIMITER;
    char end_line = '\n';
    ADT_track_t * track;

    track = (ADT_track_t *)t;

    if(fprintf(file_out, "%s", track->title) < 0)
        return ERROR_WRITING_TO_FILE;
    

    if (fputc(del, file_out) == EOF)
        return ERROR_WRITING_TO_FILE;
  

    if(fprintf(file_out, "%s", track->artist) < 0)
        return ERROR_WRITING_TO_FILE;
    

    if(fputc(del, file_out) == EOF)
        return ERROR_WRITING_TO_FILE;
    

    if(fprintf(file_out, "%s", track->genre) < 0)
        return ERROR_WRITING_TO_FILE;


    if (fputc(end_line, file_out) == EOF)
        return ERROR_WRITING_TO_FILE;
    

    return OK;
}

status_t ADT_track_export_to_csv (void * t, FILE * file_out) {
    char del = CSV_DELIMITER;
    char end_line = '\n';
    ADT_track_t * track;

    track = (ADT_track_t *)t;

    if(fprintf(file_out, "%s", track->title) < 0)
        return ERROR_WRITING_TO_FILE;
    

    if (fputc(del, file_out) == EOF)
        return ERROR_WRITING_TO_FILE;
  

    if(fprintf(file_out, "%s", track->artist) < 0)
        return ERROR_WRITING_TO_FILE;
    

    if(fputc(del, file_out) == EOF)
        return ERROR_WRITING_TO_FILE;
    

    if(fprintf(file_out, "%s", track->genre) < 0)
        return ERROR_WRITING_TO_FILE;


    if (fputc(end_line, file_out) == EOF)
        return ERROR_WRITING_TO_FILE;
    

    return OK;
}

int ADT_track_compare_by_artist (void * t1, void * t2) {
    size_t i;
    ADT_track_t *track1, *track2;

    track1 = (ADT_track_t *)t1;
    track2 = (ADT_track_t *)t2;

    if (track1 == NULL || track2 == NULL)
        return 0;

    for(i=0; track1->artist[i] && track2->artist[i]; i++) {
        if (track1->artist[i] != track2->artist[i]) {
            return (track1->artist[i] - track2->artist[i]);
        }
    }
    if (!track1->artist[i] && track2->artist[i]) {
        return 1;
    }
    if (track1->artist[i] && !track2->artist[i]) {
        return -1;
    }
    return 0;
}

int ADT_track_compare_by_title (void * t1, void * t2) {
    size_t i;
    ADT_track_t *track1, *track2;

    track1 = (ADT_track_t *)t1;
    track2 = (ADT_track_t *)t2;

    if (track1 == NULL || track2 == NULL)
        return 0;

    for(i=0; track1->title[i] && track2->title[i]; i++) {
        if (track1->title[i] != track2->title[i]) {
            return (track1->title[i] - track2->title[i]);
        }
    }
    if (!track1->title[i] && track2->title[i]) {
        return 1;
    }
    if (track1->title[i] && !track2->title[i]) {
        return -1;
    }
    return 0;
}


int ADT_track_compare_by_genre (void * t1, void * t2) {

    /*EDIT*/
   /*ADT_track_t *track1, *track2;

    track1 = (ADT_track_t *)t1;
    track2 = (ADT_track_t *)t2;*/
    return 1;
}