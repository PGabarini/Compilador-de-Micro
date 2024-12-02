#ifndef SCANNER_H_
#define SCANNER_H_

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define TAMANIO_BUFFER 20
//typedef int TOKEN;

extern FILE* ArchivoDelScanner;

typedef int ESTADO;

typedef enum {
 INICIO, LEER, FIN, ESCRIBIR, ID, CONSTANTE, PARENIZQUIERDO, 
 PARENDERECHO, PUNTOYCOMA, COMA, ASIGNACION, SUMA, RESTA, FDT
} TOKEN;

void Imprimir(TOKEN token);

const char *Buffer(void);

TOKEN esReservada(void);
  
TOKEN Scanner(void);

const char* get_token_name(TOKEN token);

#endif