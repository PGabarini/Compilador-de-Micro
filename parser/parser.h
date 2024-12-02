#ifndef PARSER_H_
#define PARSER_H_

#include "../scanner/scanner.h"
#include <string.h>
#include <stdio.h>
#include <ctype.h>

void Parser(void);

void Programa(void);

void Match(TOKEN token);

void ListaDeSentencias(void);

void Sentencia(void);

void Expresion(void);

void ListaExpresiones(void);

void ListaIdentificadores(void);

void Primaria(void);

void OperadorAditivo(void);

void RepararErrorSintactico(void);


#endif