#ifndef ERRORS__H
#define ERRORS__H

#include <stdio.h>
#include "types.h"

#define MAX_ERRORS 10

#define MSG_ERROR_INVALID_OUTPUT_FILE "Archivo de salida inválido."
#define MSG_ERROR_WRITING_TO_FILE "No se pudo escribir en el archivo."
#define MSG_ERROR_DISK_SPACE "No se pudo cerrar archivo."
#define MSG_ERROR_INVALID_MP3_FILE "Archivo mp3 inválido."
#define MSG_ERROR_INVOCATION "Invocación inválida."
#define MSG_ERROR_NULL_POINTER "Puntero nulo."
#define MSG_ERROR_OUT_OF_MEMORY "Memoria insuficiente."
#define MSG_ERROR_OUT_OF_RANGE "Fuera de rango."
#define MSG_ERROR_INVALID_TRACK "Track inválido."
#define MSG_ERROR_NOT_IMPLEMENTED "Función no implementada."

status_t print_error(status_t st);

#endif