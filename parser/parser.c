#include "../scanner/scanner.h"
#include "parser.h"
#include <string.h>

TOKEN  tokenActual;

void Parser(void)
{
    /* <objetivo> -> <programa> FDT  */
        Programa();
        Match(FDT);
        puts("FINAAAAL");
    
}

void Programa(void)
{
    /*<programa> -> INICIO <listaSentencias> FIN*/
    tokenActual = Scanner();
    Match(INICIO);
    ListaDeSentencias();
    Match(FIN);

}

void ListaDeSentencias(void)
{
    /* <listaSentencias> -> <sentencia> {<sentencia>} */
    
    Sentencia(); /* la primera de la lista de sentencias */

    while (1) 
    { 
        switch (tokenActual) 
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
         Match(ID); Match(ASIGNACION); Expresion(); Match(PUNTOYCOMA);
        break;

    case LEER: 
        /* <sentencia> -> LEER ( <listaIdentificadores> ); */
        Match(LEER); Match(PARENIZQUIERDO); ListaIdentificadores(); Match(PARENDERECHO); Match(PUNTOYCOMA);
        break;

    case ESCRIBIR: 
        /* <sentencia> -> ESCRIBIR (<listaExpresiones>); */
         Match(ESCRIBIR); Match(PARENIZQUIERDO); ListaExpresiones(); Match(PARENDERECHO); Match(PUNTOYCOMA);
        break;

    default:
        RepararErrorSintactico();
        break;
    }

}

void Expresion(void)
{
   
    Primaria();

    /* <expresion> -> <primaria> {<operadorAditivo> <primaria>} */
    for (; tokenActual == SUMA || tokenActual == RESTA; )
    {
        OperadorAditivo(); Primaria();
    }
    
}

void ListaExpresiones(void)
{
    
    Expresion();

    /* <listaExpresiones> -> <expresión> {COMA <expresión>} */

    while(1)

    {
        switch (tokenActual) 
        {

            case COMA: 
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
    Match(ID);

    while(1)
    {
        switch (tokenActual) 
        {
            
            case COMA: 
                Match(COMA); Match(ID);
                break;

            default:
                return;
        }
    }
}

void Primaria(void)
{  
    /* <primaria> -> ID | CONSTANTE | PARENIZQUIERDO <expresión> PARENDERECHO */

    switch (tokenActual)
    {
    case ID:
        Match(ID);
        break;

    case CONSTANTE:
        Match(CONSTANTE);  
        break;

    case PARENIZQUIERDO:

        Match(PARENIZQUIERDO);Expresion(); Match(PARENDERECHO);
        break;

    default:
        RepararErrorSintactico();
        break;
    }
}

void OperadorAditivo(void)
{
    /* <operadorAditivo> -> uno de SUMA RESTA */
    
    if (tokenActual == SUMA || tokenActual == RESTA)
        Match(tokenActual);
        else
        RepararErrorSintactico();

}
    


void Match(TOKEN tokenEsperado)
{   
   

    if(tokenEsperado == tokenActual)
    {
        if(tokenActual== FDT)
        {   
            printf("%s"," Finaaal");
            return;
        }
        printf("%s%s", get_token_name(tokenActual)," ");

        if(tokenActual== PUNTOYCOMA)
        {
            printf(" \n ");
        }
    }
    else
    {
        RepararErrorSintactico();
    }

    tokenActual = Scanner();
    
}

void RepararErrorSintactico(void) //Por ahora solo avisa
{
    printf("%s","-ErrorSintactico- ");
}
