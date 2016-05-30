CC = gcc

CLIBS = `pkg-config libxml-2.0 --cflags --libs`

all : fenetre2


fenetre2.o : fenetre2.c
	$(CC) -c fenetre2.c -lSDL2

fenetre2 : fenetre2.o Parserproj.o 
	$(CC) Parserproj.o fenetre2.o -lxml2 -lSDL2 -lSDL2_gfx -o fenetre2 $(CLIB)

Parserproj.o : Parserproj.c
	$(CC) -c Parserproj.c -lxml2

clean: 
	rm -f *.o *.bin
