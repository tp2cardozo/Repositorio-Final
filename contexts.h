#ifndef CONTEXTS__H
#define CONTEXTS__H

#include <stdio.h>
#include "types.h"
#include "track.h"

#define MAX_XML_CONTEXTS 9

#define CSV_DELIMITER "|"

#define XML_DECLARATION "<?xml version=\"1.0\" ?>"
#define XML_OPEN_INITIAL_TAG "<"
#define XML_OPEN_FINISHER_TAG "</"
#define XML_CLOSE_TAG ">"

#define XML_TRACKS_FLAG "tracks"

#define XML_DECLARATION_INDEX 0
#define XML_OPEN_INITIAL_TAG_INDEX 1 
#define XML_OPEN_FINISHER_TAG_INDEX 2
#define XML_CLOSE_TAG_INDEX 3
#define XML_TRACKS_FLAG_INDEX 4
#define XML_TRACK_FLAG_INDEX 5
#define XML_NAME_FLAG_INDEX 6
#define XML_ARTIST_FLAG_INDEX 7 
#define XML_GENRE_FLAG_INDEX 8

#endif