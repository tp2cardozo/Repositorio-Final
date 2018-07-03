#include <stdio.h>

#include "types.h"
#include "contexts.h"

/*Variables que contienen el contexto para la exportacion*/

char * context_csv = CSV_DELIMITER;

char * context_xml[MAX_XML_CONTEXTS] =
{
	XML_VERSION_LINE,
	XML_OPEN_INITIAL_BRACKET,
	XML_OPEN_FINISHER_BRACKET,
	XML_CLOSE_BRACKET,
	XML_TRACKS_FLAG,
	XML_TRACK_FLAG,
	XML_NAME_FLAG,
	XML_ARTIST_FLAG,
	XML_GENRE_FLAG
};