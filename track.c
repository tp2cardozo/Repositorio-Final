#include <stdio.h>
#include <stdlib.h>

#include "types.h"
#include "track.h"

status_t ADT_track_set (const char header[], ADT_track_t * track)
{
    char buf[MP3_HEADER_SIZE];

    if (header == NULL || track == NULL)
       return ERROR_NULL_POINTER;

    memcpy(buf,header+LEXEM_START_TAG,LEXEM_SPAN_TAG);
    buf[LEXEM_SPAN_TAG] = '\0';
    sprintf(track,"%s\n", buf);

    memcpy(buf,header+LEXEM_START_TITLE,LEXEM_SPAN_TITLE);
    buf[LEXEM_SPAN_TITLE] = '\0';
    sprintf(track,"%s\n", buf);

    memcpy(buf,header+LEXEM_START_ARTIST,LEXEM_SPAN_ARTIST);
    buf[LEXEM_SPAN_ARTIST] = '\0';
    sprintf(track,"%s\n", buf);

    memcpy(buf,header+LEXEM_START_ALBUM,LEXEM_SPAN_ALBUM);
    buf[LEXEM_SPAN_ALBUM] = '\0';
    sprintf(track,"%s\n", buf);

    memcpy(buf,header+LEXEM_START_YEAR,LEXEM_SPAN_YEAR);
    buf[LEXEM_SPAN_YEAR] = '\0';
    sprintf(track,"%s\n", buf);

    memcpy(buf,header+LEXEM_START_COMMENT,LEXEM_SPAN_COMMENT);
    buf[LEXEM_SPAN_COMMENT] = '\0';
    sprintf(track,"%s\n", buf);

    memcpy(buf,header+LEXEM_START_GENRE,LEXEM_SPAN_GENRE);
    buf[LEXEM_SPAN_GENRE] = '\0';
    sprintf(track,"%s\n", buf);

    return OK;
}