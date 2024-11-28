#include <string.h>
#include "scanner/scanner.h"
#include "parser/parser.h"

int main(void) {
    TOKEN token;

    FILE *archivoDelScanner = fopen("devolucion.del.parser", "w");

    while ((token = Scanner()) != FDT) 
    {
        fprintf(archivoDelScanner,"%s --> %s%s",Buffer(),get_token_name(token),"\n");
        //Parser(token);
    }
    

    fclose(archivoDelScanner);

    return 0;
}
