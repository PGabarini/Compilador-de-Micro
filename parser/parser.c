#include "../scanner/scanner.h"
#include "parser.h"
#include <string.h>

TOKEN tokenActual, tokenSiguiente;

void Parser(TOKEN token)
{
    /* INICIO <listaSentencias> FIN */

    if (token == INICIO)

    {
        ListaDeSentencias();

        Match(FIN);
    }
}


void ListaDeSentencias(void)
{
    /* <listaSentencias> -> <sentencia> {<sentencia>} */
    tokenActual = Scanner();
    Sentencia(); /* la primera de la lista de sentencias */

    while (1) 
    { 
        switch (tokenActual = Scanner()) 
        {
        

        case ID: case LEER: case ESCRIBIR: /* detectó token correcto */ 
            Sentencia(); /* procesa la secuencia opcional */
            break;

        default:
            return;
        }   
    }

}

void Sentencia(void)
{
    switch (tokenActual)
    {
    case ID: 
        /* <sentencia> -> ID := <expresion>; */
         Match(ASIGNACION); Expresion(); Match(PUNTOYCOMA);
        break;

    case LEER: 
        /* <sentencia> -> LEER ( <listaIdentificadores> ); */
        Match(PARENIZQUIERDO); ListaIdentificadores(); Match(PARENDERECHO); Match(PUNTOYCOMA);
        break;

    case ESCRIBIR: 
        /* <sentencia> -> ESCRIBIR (<listaExpresiones>); */
         Match(PARENIZQUIERDO); ListaExpresiones(); Match(PARENDERECHO); Match(PUNTOYCOMA);
        break;

    default:
        RepararErrorSintactico(tokenActual);
        break;
    }

}

void Expresion(void)
{
   
    Primaria();

    /* <expresion> -> <primaria> {<operadorAditivo> <primaria>} */
    for (tokenActual = Scanner(); tokenActual == SUMA || tokenActual == RESTA; tokenActual = Scanner())
    {
        OperadorAditivo(); Primaria();
    }
}

void ListaExpresiones(void)
{
    tokenActual = Scanner();
    Expresion();

    /* <listaExpresiones> -> <expresión> {COMA <expresión>} */

    while(1)

    {
        switch (tokenActual = Scanner()) 
        {

            case ID: 
                Match(COMA); Expresion();
                break;

            default:
                return;
        }
    }
}

void ListaIdentificadores(void)
{ 
    /* <listaIdentificadores> -> ID {COMA ID} */

    while(1)
    {
        switch (tokenActual = Scanner()) 
        {
            
            case ID: 
                Match(COMA);
                break;

            default:
                return;
        }
    }
}

void Primaria(void)
{   
    tokenActual = Scanner();

    /* <primaria> -> ID | CONSTANTE | PARENIZQUIERDO <expresión> PARENDERECHO */

    switch (tokenActual)
    {
    case ID: 
        break;

    case CONSTANTE:  
        break;

    case PARENIZQUIERDO:
        Expresion(); Match(PARENDERECHO);
        break;

    default:
        RepararErrorSintactico(tokenActual);
        break;
    }
}

void OperadorAditivo(void)
{
    /* <operadorAditivo> -> uno de SUMA RESTA */
    switch (tokenActual)
    {
        case SUMA: case RESTA:
            break;
        
        default:
            RepararErrorSintactico(tokenActual);
            break;
    }
    
}

void Match(TOKEN tokenEsperado)
{   
    tokenSiguiente = Scanner();

    if(tokenEsperado == tokenSiguiente)
    {
        tokenActual = tokenSiguiente;
        printf("%s"," correcto ");
    }
    else
    {
        RepararErrorSintactico(tokenActual);
    }

    
}

void RepararErrorSintactico(TOKEN tokenInvalido) //Por ahora solo avisa
{
    printf("%s%s","ERROR: ", tokenInvalido);
}