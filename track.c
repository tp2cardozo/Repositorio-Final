#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "track.h"
#include "errors.h"
#include "main.h"

extern char * errors_dictionary[MAX_ERRORS];


/*Diccionarios de formato, tipos de ordenes y generos*/

status_t (*format_output[MAX_FORMATS]) (void *, const void *, FILE *) = 
{
    ADT_track_export_to_csv,
    ADT_track_export_to_xml
};

int (*sort_output[MAX_SORTS]) (void *, void *) =
{
    ADT_track_compare_by_title,
    ADT_track_compare_by_artist,
    ADT_track_compare_by_genre
};

char * genres_dictionary[MAX_GENRES] = 
{
    "Blues", "Classic Rock", "Country", "Dance", "Disco", "Funk", "Grunge", 
    "Hip-Hop", "Jazz", "Metal", "New Age", "Oldies", "Other", "Pop", 
    "R&B", "Rap", "Reggae", "Rock", "Techno", "Industrial", "Alternative", 
    "Ska", "Death Metal", "Pranks", "Soundtrack", "Euro-Techno", "Ambient", "Trip-Hop", 
    "Vocal", "Jazz+Funk", "Fusion", "Trance", "Classical", "Instrumental", "Acid", 
    "House", "Game", "Sound Clip", "Gospel", "Noise", "AlternRock", "Bass", 
    "Soul", "Punk", "Space", "Meditative", "Instrumental Pop", "Instrumental Rock", "Ethnic", 
    "Gothic", "Darkwave", "Techno-Industrial", "Electronic", "Pop-Folk", "Eurodance", "Dream", 
    "Southern Rock", "Comedy", "Cult", "Gangsta", "Top 40", "Christian Rap", "Pop/Funk", 
    "Jungle", "Native American", "Cabaret", "New Wave", "Psychadelic", "Rave", "Showtunes", 
    "Trailer", "Lo-Fi", "Tribal", "Acid Punk", "Acid Jazz", "Polka", "Retro", 
    "Musical", "Rock & Roll", "Hard Rock", "Folk", "Folk-Rock", "National Folk", "Swing", 
    "Fast Fusion", "Bebob", "Latin", "Revival", "Celtic", "Bluegrass", "Avantgarde", 
    "Gothic Rock", "Progressive Rock", "Psychedelic Rock", "Symphonic Rock", "Slow Rock", "Big Band", "Chorus", 
    "Easy Listening", "Acoustic", "Humour", "Speech", "Chanson", "Opera", "Chamber Music", 
    "Sonata", "Symphony", "Booty Brass", "Primus", "Porn Groove", "Satire", "Slow Jam", 
    "Club", "Tango", "Samba", "Folklore", "Ballad", "Poweer Ballad", "Rhytmic Soul", 
    "Freestyle", "Duet", "Punk Rock", "Drum Solo", "A Capela", "Euro-House", "Dance Hall"
};

/*Esta función crea una nueva pista*/
status_t ADT_track_new (ADT_track_t ** track)
{
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
    (*track)->genre = 0;

    return OK;
}

/*Esta funcion destruye una pista*/
status_t ADT_track_delete (void * t)
{
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
    track->genre = 0;

    free(track);
    track = NULL;

    return OK;
}

/*Esta función establece una pista*/
status_t ADT_track_set (char header[], ADT_track_t * track)
{
    char aux[2];

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

    memcpy(aux,header+LEXEM_START_GENRE,LEXEM_SPAN_GENRE);
    track->genre = aux[0];

    return OK;
}

/*Esta función exporta una pista a un archivo csv*/
status_t ADT_track_export_to_csv (void * t, const void * context, FILE * file_out)
{
    char del;
    ADT_track_t * track;

    del = *((char *)context);
    track = (ADT_track_t *)t;

    if(fprintf(file_out, "%s", track->title) < 0)
        return ERROR_WRITING_TO_FILE;
    
    if (fputc(del, file_out) == EOF)
        return ERROR_WRITING_TO_FILE;
  
    if(fprintf(file_out, "%s", track->artist) < 0)
        return ERROR_WRITING_TO_FILE;

    if(fputc(del, file_out) == EOF)
        return ERROR_WRITING_TO_FILE;
    
    if(fprintf(file_out, "%s\n", genres_dictionary[track->genre]) < 0)
        return ERROR_WRITING_TO_FILE;

    return OK;
}

/*Esta función exporta una pista a un archivo csv*/
status_t ADT_track_export_to_xml (void * t, const void * context, FILE * file_out)
{
    char ** xml_contexts;
    ADT_track_t * track;

    xml_contexts = (char **)context;
    track = (ADT_track_t *)t;

    if(fprintf(file_out, "\t%s%s%s\n", xml_contexts[XML_OPEN_INITIAL_BRACKET_INDEX], xml_contexts[XML_TRACK_FLAG_INDEX], xml_contexts[XML_CLOSE_BRACKET_INDEX]) < 0)
        return ERROR_WRITING_TO_FILE;

    if(fprintf(file_out, "\t\t%s%s%s", xml_contexts[XML_OPEN_INITIAL_BRACKET_INDEX], xml_contexts[XML_NAME_FLAG_INDEX], xml_contexts[XML_CLOSE_BRACKET_INDEX]) < 0)
        return ERROR_WRITING_TO_FILE;

    if(fprintf(file_out, "%s", track->title) < 0)
        return ERROR_WRITING_TO_FILE;

    if(fprintf(file_out, "%s%s%s\n", xml_contexts[XML_OPEN_FINISHER_BRACKET_INDEX], xml_contexts[XML_NAME_FLAG_INDEX], xml_contexts[XML_CLOSE_BRACKET_INDEX]) < 0)
        return ERROR_WRITING_TO_FILE;

    if(fprintf(file_out, "\t\t%s%s%s", xml_contexts[XML_OPEN_INITIAL_BRACKET_INDEX], xml_contexts[XML_ARTIST_FLAG_INDEX], xml_contexts[XML_CLOSE_BRACKET_INDEX]) < 0)
        return ERROR_WRITING_TO_FILE;

    if(fprintf(file_out, "%s", track->artist) < 0)
        return ERROR_WRITING_TO_FILE;

    if(fprintf(file_out, "%s%s%s\n", xml_contexts[XML_OPEN_FINISHER_BRACKET_INDEX], xml_contexts[XML_ARTIST_FLAG_INDEX], xml_contexts[XML_CLOSE_BRACKET_INDEX]) < 0)
        return ERROR_WRITING_TO_FILE;

    if(fprintf(file_out, "\t\t%s%s%s", xml_contexts[XML_OPEN_INITIAL_BRACKET_INDEX], xml_contexts[XML_GENRE_FLAG_INDEX], xml_contexts[XML_CLOSE_BRACKET_INDEX]) < 0)
        return ERROR_WRITING_TO_FILE;

    if(fprintf(file_out, "%s", genres_dictionary[track->genre]) < 0)
        return ERROR_WRITING_TO_FILE;

    if(fprintf(file_out, "%s%s%s\n", xml_contexts[XML_OPEN_FINISHER_BRACKET_INDEX], xml_contexts[XML_GENRE_FLAG_INDEX], xml_contexts[XML_CLOSE_BRACKET_INDEX]) < 0)
        return ERROR_WRITING_TO_FILE;

    if(fprintf(file_out, "\t%s%s%s\n", xml_contexts[XML_OPEN_FINISHER_BRACKET_INDEX], xml_contexts[XML_TRACK_FLAG_INDEX], xml_contexts[XML_CLOSE_BRACKET_INDEX]) < 0)
        return ERROR_WRITING_TO_FILE;

    return OK;
}

/*Esta función compara dos pistas según el artista*/
int ADT_track_compare_by_artist (void * t1, void * t2)
{
    size_t i;
    ADT_track_t *track1, *track2;

    track1 = (ADT_track_t *)t1;
    track2 = (ADT_track_t *)t2;

    if (track1 == NULL || track2 == NULL)
        return 0;

    for(i=0; track1->artist[i] && track2->artist[i]; i++)
    {
        if (track1->artist[i] != track2->artist[i])
        {
            return (track1->artist[i] - track2->artist[i]);
        }
    }
    if (!track1->artist[i] && track2->artist[i])
    {
        return 1;
    }
    if (track1->artist[i] && !track2->artist[i])
    {
        return -1;
    }
    return 0;
}

/*Esta función compara dos pistas segun el nombre*/
int ADT_track_compare_by_title (void * t1, void * t2)
{
    size_t i;
    ADT_track_t *track1, *track2;

    if (t1 == NULL || t2 == NULL)
        return 0;

    track1 = (ADT_track_t *)t1;
    track2 = (ADT_track_t *)t2;


    for(i=0; track1->title[i] && track2->title[i]; i++)
    {
        if (track1->title[i] != track2->title[i])
        {
            return (track1->title[i] - track2->title[i]);
        }
    }
    if (!track1->title[i] && track2->title[i])
    {
        return 1;
    }
    if (track1->title[i] && !track2->title[i])
    {
        return -1;
    }
    return 0;
}

/*Esta función compara dos pistas segun el género*/
int ADT_track_compare_by_genre (void * t1, void * t2)
{
    ADT_track_t *track1, *track2;

    if (t1 == NULL || t2 == NULL)
        return 0;

    track1 = (ADT_track_t *)t1;
    track2 = (ADT_track_t *)t2;

    return track1->genre - track2->genre;
}