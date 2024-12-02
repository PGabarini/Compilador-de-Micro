#include <string.h>
#include "scanner/scanner.h"
#include "parser/parser.h"

FILE *ArchivoDelScanner = NULL;


int main(void) {
    
    ArchivoDelScanner = fopen("devolucion.del.parser", "w");
      
    Parser();
    
    return 0;
}
