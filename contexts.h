#ifndef CONTEXTS__H
#define CONTEXTS__H

#include <stdio.h>

#define MAX_XML_CONTEXTS 9

#define CSV_DELIMITER "|"

#define XML_VERSION_LINE "<?xml version=\"1.0\" ?>"
#define XML_OPEN_INITIAL_BRACKET "<"
#define XML_OPEN_FINISHER_BRACKET "</"
#define XML_CLOSE_BRACKET ">"

#define XML_TRACKS_FLAG "tracks"
#define XML_TRACK_FLAG "track"
#define XML_NAME_FLAG "name"
#define XML_ARTIST_FLAG "artist"
#define XML_GENRE_FLAG "genre"

#define XML_VERSION_LINE_INDEX 0
#define XML_OPEN_INITIAL_BRACKET_INDEX 1 
#define XML_OPEN_FINISHER_BRACKET_INDEX 2
#define XML_CLOSE_BRACKET_INDEX 3
#define XML_TRACKS_FLAG_INDEX 4
#define XML_TRACK_FLAG_INDEX 5
#define XML_NAME_FLAG_INDEX 6
#define XML_ARTIST_FLAG_INDEX 7 
#define XML_GENRE_FLAG_INDEX 8

#endif