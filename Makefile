#all: mmc

#mmc: main.c scanner.h scanner.o
#	cc -c main.c
#	cc -o mmc main.o scanner.o

#test: mmc
#	./mmc < test.ok.micro
#	./mmc < test.error-lex.micro

#clean:
#	rm -rf *.o mmc

all: mmc

mmc: main.c scanner/scanner.h scanner/scanner.o parser/parser.h parser/parser.o
	gcc -c main.c
	gcc -o mmc main.o scanner/scanner.o parser/parser.o

test: mmc

	@printf "\nToken ---> Nombre\n"

	@printf "\n Ejecutando test: ok.micro \n\n"
	./mmc < test.ok.micro
	
	@printf "\n Ejecutando test: error lexico \n\n"
	./mmc < test.error-lex.micro
	
	@printf "\n Ejecutando test: constantes \n\n"
	./mmc < test.constantes
	
	@printf "\n Ejecutando test: Reservadas \n\n"
	./mmc < test.reservada

	@printf "\n Ejecutando test: identificadores \n\n"
	./mmc < test.id

	@printf "\n Ejecutando test: simbolos y puntuacion \n\n"
	./mmc < test.puntuacion

	@printf "\n Ejecutando test: Error Sintactico y Lexico\n\n"
	./mmc < test.error-sintacticoyLexico.micro

clean:
#	del /Q *.o mmc.exe
	rm -rf *.o mmc
	rm -rf scanner/*.o 
	rm -rf parser/*.o 