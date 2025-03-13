
HEADERS = birdcage.h
FLAGS = -Wall -Wextra --pedantic -ggdb

pigeondrop: pigeondrop.o birdcage.o
	gcc $(FLAGS) -o pigeondrop birdcage.o pigeondrop.o

pigeonfly: pigeonfly.o birdcage.o
	gcc $(FLAGS) -o pigeonfly birdcage.o pigeonfly.o

pigeonshred: pigeonshred.o birdcage.o
	gcc $(FLAGS) -o pigeonshred birdcage.o pigeonshred.o

all: pigeondrop pigeonfly pigeonshred

pigeondrop.o: pigeondrop.c
	gcc $(FLAGS) -c pigeondrop.c

pigeonfly.o: pigeonfly.c
	gcc $(FLAGS) -c pigeonfly.c

birdcage.o: birdcage.c $(HEADERS)
	gcc $(FLAGS) -c birdcage.c

pigeonshred.o: pigeonshred.c
	gcc $(FLAGS) -c pigeonshred.c
	
clean:
	-rm -f pigeonshred.o
	-rm -f birdcage.o
	-rm -f pigeonfly.o
	-rm -f pigeondrop.o
	-rm -f pigeonshred
	-rm -f pigeonfly
	-rm -f pigeondrop

listclean:
	-rm -f lists/*
	-touch lists/all_available.txt

allclean: clean listclean
		
