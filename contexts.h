#ifndef CONTEXTS__H
#define CONTEXTS__H

#include <stdio.h>
#include "types.h"
#include "track.h"

#define MAX_XML_CONTEXTS 11

#define CSV_DELIMITER "|"

#define XML_PROCESSING_INSTRUCTOR "<?xml version=\"1.0\" ?>"

#define XML_TRACKS_TAG "<tracks>"
#define XML_TRACKS_END_TAG "</tracks>"

#define XML_PROCESSING_INSTRUCTOR_INDEX 0 
#define XML_TRACKS_TAG_INDEX 1 
#define XML_TRACKS_END_TAG_INDEX 2 
#define XML_TRACK_TAG_INDEX 3 
#define XML_TRACK_END_TAG_INDEX 4 
#define XML_NAME_TAG_INDEX 5 
#define XML_NAME_END_TAG_INDEX 6 
#define XML_ARTIST_TAG_INDEX 7 
#define XML_ARTIST_END_TAG_INDEX 8 
#define XML_GENRE_TAG_INDEX 9 
#define XML_GENRE_END_TAG_INDEX 10 

#endif