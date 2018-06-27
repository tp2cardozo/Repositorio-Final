#ifndef ERRORS__H
#define ERRORS__H

#include <stdio.h>
#include "types.h"

#define MAX_ERRORS 10

#define MSG_ERROR_INVALID_OUTPUT_FILE "Error, archivo de salida inválido."
#define MSG_ERROR_WRITING_TO_FILE "Error al escribir en el archivo."
#define MSG_ERROR_CLOSING_FILE "Error al cerrar archivo."
#define MSG_ERROR_INVALID_MP3_FILE "Error, archivo mp3 inválido."
#define MSG_ERROR_INVOCATION "Error de invocación."
#define MSG_ERROR_NULL_POINTER "Error, puntero nulo."
#define MSG_ERROR_OUT_OF_MEMORY "Error, memoria insuficiente."
#define MSG_ERROR_OUT_OF_RANGE "Error, fuera de rango."
#define MSG_ERROR_INVALID_TRACK "Error, track inválido."

status_t print_errors(status_t st);

#endif