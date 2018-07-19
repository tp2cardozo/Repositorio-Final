#include <stdio.h>
#include <string.h>
#include "mp3.h"

/*Diccionarios de formato, tipos de ordenes y generos*/
char * genres_dictionary[MAX_GENRES] = 
{
    "Blues",
    "Classic Rock",
    "Country",
    "Dance",
    "Disco",
    "Funk",
    "Grunge",
    "Hip-Hop",
    "Jazz",
    "Metal",
    "New Age",
    "Oldies",
    "Other",
    "Pop",
    "R&B",
    "Rap",
    "Reggae",
    "Rock",
    "Techno",
    "Industrial",
    "Alternative",
    "Ska",
    "Death Metal",
    "Pranks",
    "Soundtrack",
    "Euro-Techno",
    "Ambient",
    "Trip-Hop",
    "Vocal",
    "Jazz+Funk",
    "Fusion",
    "Trance",
    "Classical",
    "Instrumental",
    "Acid",
    "House",
    "Game",
    "Sound Clip",
    "Gospel",
    "Noise",
    "AlternRock",
    "Bass",
    "Soul",
    "Punk",
    "Space",
    "Meditative",
    "Instrumental Pop",
    "Instrumental Rock",
    "Ethnic",
    "Gothic",
    "Darkwave",
    "Techno-Industrial",
    "Electronic",
    "Pop-Folk",
    "Eurodance",
    "Dream",
    "Southern Rock",
    "Comedy",
    "Cult",
    "Gangsta",
    "Top 40",
    "Christian Rap",
    "Pop/Funk",
    "Jungle",
    "Native American",
    "Cabaret",
    "New Wave",
    "Psychadelic",
    "Rave",
    "Showtunes",
    "Trailer",
    "Lo-Fi",
    "Tribal",
    "Acid Punk",
    "Acid Jazz",
    "Polka",
    "Retro",
    "Musical",
    "Rock & Roll",
    "Hard Rock",
    "Folk",
    "Folk-Rock",
    "National Folk",
    "Swing",
    "Fast Fusion",
    "Bebob",
    "Latin",
    "Revival",
    "Celtic",
    "Bluegrass",
    "Avantgarde",
    "Gothic Rock",
    "Progressive Rock",
    "Psychedelic Rock",
    "Symphonic Rock",
    "Slow Rock",
    "Big Band",
    "Chorus",
    "Easy Listening",
    "Acoustic",
    "Humour",
    "Speech",
    "Chanson",
    "Opera",
    "Chamber Music",
    "Sonata",
    "Symphony",
    "Booty Brass",
    "Primus",
    "Porn Groove",
    "Satire",
    "Slow Jam",
    "Club",
    "Tango",
    "Samba",
    "Folklore",
    "Ballad",
    "Poweer Ballad",
    "Rhytmic Soul",
    "Freestyle",
    "Duet",
    "Punk Rock",
    "Drum Solo",
    "A Capela",
    "Euro-House",
    "Dance Hall"
};

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

status_t parse_mp3_header(char header[], char * artist, char * tag, char * title, char * artist, char * album, char * year, char * comment, unsigned char * genre) {

    if (header == NULL || artist == NULL || tag == NULL || title == NULL || artist == NULL || album == NULL || year == NULL || comment == NULL || genre) {
        return ERROR_NULL_POINTER;
    }

    memcpy(tag,header+LEXEM_START_TAG,LEXEM_SPAN_TAG);
    tag[LEXEM_SPAN_TAG] = '\0';

    memcpy(title,header+LEXEM_START_TITLE,LEXEM_SPAN_TITLE);
    title[LEXEM_SPAN_TITLE] = '\0';

    memcpy(artist,header+LEXEM_START_ARTIST,LEXEM_SPAN_ARTIST);
    artist[LEXEM_SPAN_ARTIST] = '\0';

    memcpy(album,header+LEXEM_START_ALBUM,LEXEM_SPAN_ALBUM);
    album[LEXEM_SPAN_ALBUM] = '\0';

    memcpy(year,header+LEXEM_START_YEAR,LEXEM_SPAN_YEAR);
    year[LEXEM_SPAN_YEAR] = '\0';

    memcpy(comment,header+LEXEM_START_COMMENT,LEXEM_SPAN_COMMENT);
    comment[LEXEM_SPAN_COMMENT] = '\0';

    memcpy(genre,header+LEXEM_START_GENRE,LEXEM_SPAN_GENRE);

    return OK;
}