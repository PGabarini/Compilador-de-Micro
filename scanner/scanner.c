#include "scanner.h"
#include <string.h>


char _buffer[TAMANIO_BUFFER+1];
int  _posicion = 0;

void LimpiarBuffer(void) {
    _buffer[0] = '\0';
    _posicion = 0;
}

void AgregarCaracter(int caracter) {
    _buffer[_posicion++] = caracter;
}

const char *Buffer(void) {
    _buffer[_posicion] = '\0';
    return _buffer;
}

TOKEN esReservada(void) {
 if(!strcmp(Buffer(), "inicio")){
    return INICIO;
 }
 if(!strcmp(Buffer(), "fin")){
    return FIN;
 }
 if(!strcmp(Buffer(), "leer")){
    return LEER;
 }
 if(!strcmp(Buffer(), "escribir")){
    return ESCRIBIR;
 }
 return ID;
}
 

int ObtenerColumna(int simbolo) {
   if(isspace(simbolo)) return 11;
    if(isdigit(simbolo)) return 1;
    if(isalpha(simbolo)) return 0;

    switch (simbolo)
    {
        case '+':
            return 2;
       
        case '-':
            return 3;
       
        case EOF:
            return 10;
       
        case ':':
            return 8;
       
        case '=':
            return 9;
       
        case ';':
            return 7;
       
        case  '(':
            return 4;
       
        case ')':
            return 5;
        case ',':
            return 6;
        default:
            return 12;
    }
}


ESTADO Transicion(ESTADO estado, int simbolo) {
    static ESTADO TT[15][13] = {
        /*L   D   +   -   (   )   ,   ;   :   =  fdt  sp otro */
        {1,3,5,6,7,8,9,10,11,99,13,0,99},
		{1,1,2,2,2,2,2,2,2,2,2,2,2},
		{99,99,99,99,99,99,99,99,99,99,99,99,99},
		{4,3,4,4,4,4,4,4,4,4,4,4,4},
		{99,99,99,99,99,99,99,99,99,99,99,99,99},
		{99,99,99,99,99,99,99,99,99,99,99,99,99},
		{99,99,99,99,99,99,99,99,99,99,99,99,99},
		{99,99,99,99,99,99,99,99,99,99,99,99,99},
		{99,99,99,99,99,99,99,99,99,99,99,99,99},
		{99,99,99,99,99,99,99,99,99,99,99,99,99},
		{99,99,99,99,99,99,99,99,99,99,99,99,99},
		{99,99,99,99,99,99,99,99,99,12,99,99,99},
		{99,99,99,99,99,99,99,99,99,99,99,99,99},
		{99,99,99,99,99,99,99,99,99,99,99,99,99},
        {99,99,99,99,99,99,99,99,99,99,99,99,99}
    };
    int columna = ObtenerColumna(simbolo);
    return TT[estado][columna];
}

TOKEN Scanner(void) {
    TOKEN token = 0;
    int caracter, posicion = 0;
    ESTADO estado = 0;
    LimpiarBuffer();
    while (caracter=getchar()) {
        estado = Transicion(estado, caracter);
        switch (estado) {
            case 1:
                AgregarCaracter(caracter);
                break;
                
            case 3:
                AgregarCaracter(caracter);
                break;
            case 2:
                ungetc(caracter, stdin);
                return esReservada();
            case 4:
                ungetc(caracter, stdin);
                return CONSTANTE; /* CONSTANTE */
            case 5:
                AgregarCaracter(caracter);
                return SUMA; /* SUMA */
            case 6:
                AgregarCaracter(caracter);
                return RESTA; /* RESTA */
            case 7:
                AgregarCaracter(caracter);
                return PARENIZQUIERDO;  /* PARENIZQUIERDO */
            case 8:
                AgregarCaracter(caracter);
                return PARENDERECHO;  /* PARENDERECHO */
            case 9:
                AgregarCaracter(caracter);
                return COMA;  /* COMA */
            case 10:
                AgregarCaracter(caracter);
                return PUNTOYCOMA;  /* PUNTOYCOMA */
            case 11:
                AgregarCaracter(caracter);
                break;
            case 12:
                AgregarCaracter(caracter);
                return ASIGNACION; /* ASIGNACION */
            case 99:
                /* situacion rara. ¿cómo la podemos resolver? */
                AgregarCaracter(caracter);
                printf("ERROR_LEXICO: secuencia no reconocida: \"%s\"\n", Buffer()); // Muestro error lexico y se ignora para que siga el escaneo.
                LimpiarBuffer(); //limpio buffer para que no quede la secuencia en el mismo
                estado = 0;
                break;
            case 13:
                return FDT; /* FDT */
        }
    }
}

const char* get_token_name(TOKEN token) {

    const char* token_names[] = {
    "INICIO", "LEER", "FIN", "ESCRIBIR", "ID", "CONSTANTE", 
    "PARENIZQUIERDO", "PARENDERECHO", "PUNTOYCOMA", "COMA", 
    "ASIGNACION", "SUMA", "RESTA", "FDT"
    };

    if (token >= INICIO && token <= FDT) {
        return token_names[token];
    }
    return "TOKEN INVALIDO"; 
}
