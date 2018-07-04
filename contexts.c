#include <stdio.h>

#include "contexts.h"

/*Variables que contienen el contexto para la exportacion*/

char * context_csv = CSV_DELIMITER;

char * context_xml[MAX_XML_CONTEXTS] =
{
	XML_DECLARATION,
	XML_OPEN_INITIAL_TAG,
	XML_OPEN_FINISHER_TAG,
	XML_CLOSE_TAG,
	XML_TRACKS_FLAG,
	XML_TRACK_FLAG,
	XML_NAME_FLAG,
	XML_ARTIST_FLAG,
	XML_GENRE_FLAG
};