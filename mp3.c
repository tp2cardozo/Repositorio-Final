#include <stdio.h>
#include "mp3.h"

/*Diccionarios de formato, tipos de ordenes y generos*/

status_t (*track_exports[MAX_FORMATS]) (void *, const void *, FILE *) = 
{
    ADT_track_export_to_csv,
    ADT_track_export_to_xml
};

int (*track_components[MAX_SORTS]) (void *, void *) =
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



status_t set_track_from_mp3_file(FILE * fi, ADT_Track_t * track)
{
	char header[MAX_HEADER_SIZE];
    char * header_fields[MAX_HEADER_FIELDS];

	if (fi == NULL || track == NULL)
		return ERROR_NULL_POINTER;

	if((st = get_mp3_header(fi, header)) != OK) 
        return st;

    if((st = get_info_from_header(header, header_fields)) != OK)
        return st;

    if((st = ADT_track_get_info_for_fields(header_fields, track)) != OK)
        return st;

    return OK;
}

/*Lee el encabezado del archivo mp3*/
status_t get_mp3_header(FILE * fi, char header[])
{
	size_t length;

	if(fi == NULL)
		return ERROR_NULL_POINTER;
	 

	if ((fseek(fi, 0, SEEK_END)) != OK)	
		return ERROR_INVALID_MP3_FILE;

	length=ftell(fi);

	if((fseek(fi,length - MP3_HEADER_SIZE, SEEK_SET)) != OK)
		return ERROR_INVALID_MP3_FILE;

	if (fread(header, sizeof(char), MP3_HEADER_SIZE, fi) != MP3_HEADER_SIZE)
		return ERROR_INVALID_MP3_FILE;

	return OK;
}

status_t get_info_from_header(char * header, char * fields[])
{
    char buf[MP3_HEADER_SIZE];
    char tag[LEXEM_SPAN_TAG + 1];
    char title[LEXEM_SPAN_TITLE + 1];
    char artist[LEXEM_SPAN_ARTIST + 1];
    char album[LEXEM_SPAN_ALBUM + 1];
    char year[LEXEM_SPAN_YEAR + 1];
    char comment[LEXEM_SPAN_COMMENT + 1];
    unsigned char genre;

    if(header == NULL || fields == NULL || fields[MAX_HEADER_FIELDS - 1] == NULL)
        return ERROR_NULL_POINTER;

    memcpy(buf,header+LEXEM_START_TAG,LEXEM_SPAN_TAG);
    buf[LEXEM_SPAN_TAG] = '\0';
    sprintf(tag, "%s", buf);

    memcpy(buf,header+LEXEM_START_TITLE,LEXEM_SPAN_TITLE);
    buf[LEXEM_SPAN_TITLE] = '\0';
    sprintf(title,"%s",buf);

    memcpy(buf,header+LEXEM_START_ARTIST,LEXEM_SPAN_ARTIST);
    buf[LEXEM_SPAN_ARTIST] = '\0';
    sprintf(artist,"%s",buf);

    memcpy(buf,header+LEXEM_START_ALBUM,LEXEM_SPAN_ALBUM);
    buf[LEXEM_SPAN_ALBUM] = '\0';
    sprintf(album,"%s",buf);

    memcpy(buf,header+LEXEM_START_YEAR,LEXEM_SPAN_YEAR);
    buf[LEXEM_SPAN_YEAR] = '\0';
    sprintf(year,"%s",buf);

    memcpy(buf,header+LEXEM_START_COMMENT,LEXEM_SPAN_COMMENT);
    buf[LEXEM_SPAN_COMMENT] = '\0';
    sprintf(comment,"%s",buf);

    memcpy(buf,header+LEXEM_START_GENRE,LEXEM_SPAN_GENRE);
    genre = buf[0];
    
    fields[HEADER_FIELDS_TAG_INDEX] = tag;
    fields[HEADER_FIELDS_TITLE_INDEX] = title;
    fields[HEADER_FIELDS_ARTIST_INDEX] = artist;
    fields[HEADER_FIELDS_ALBUM_INDEX] = album;
    fields[HEADER_FIELDS_YEAR_INDEX] = year;
    fields[HEADER_FIELDS_COMMENT_INDEX] = comment;
    fields[HEADER_FIELDS_GENRE_INDEX] = &genre;

    return OK;
}