#include <stdio.h>

#include "contexts.h"

/*Variables que contienen el contexto para la exportacion*/

char * context_csv = CSV_DELIMITER; /*Se requiere su uso como cadena de caracteres*/

char * context_xml[MAX_XML_CONTEXTS] =
{
	XML_PROCESSING_INSTRUCTOR,
	XML_TRACKS_TAG,
	XML_TRACKS_END_TAG,
	XML_TRACK_TAG,
	XML_TRACK_END_TAG,
	XML_NAME_TAG,
	XML_NAME_END_TAG,
	XML_ARTIST_TAG,
	XML_ARTIST_END_TAG,
	XML_GENRE_TAG,
	XML_GENRE_END_TAG
};