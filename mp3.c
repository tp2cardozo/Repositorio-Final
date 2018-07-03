
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

	if (fi == NULL || track == NULL)
		return ERROR_NULL_POINTER;

	if((st = get_mp3_header(fi, header)) != OK) 
        return st;

    if((st = ADT_track_get_info_from_file(header, track)) != OK)
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