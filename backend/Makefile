
HEADERS = include/birdcage.h
FLAGS = -Wall -Wextra --pedantic -ggdb -Iinclude

mkdir:
	mkdir -p obj

pigeondrop: mkdir pigeondrop.o birdcage.o
	gcc $(FLAGS) -o pigeondrop obj/birdcage.o obj/pigeondrop.o

pigeonfly: mkdir pigeonfly.o birdcage.o
	gcc $(FLAGS) -o pigeonfly obj/birdcage.o obj/pigeonfly.o

pigeonshred: mkdir pigeonshred.o birdcage.o
	gcc $(FLAGS) -o pigeonshred obj/birdcage.o obj/pigeonshred.o

all: pigeondrop pigeonfly pigeonshred

pigeondrop.o: mkdir src/pigeondrop.c
	gcc $(FLAGS) -c src/pigeondrop.c -o obj/pigeondrop.o

pigeonfly.o: mkdir src/pigeonfly.c
	gcc $(FLAGS) -c src/pigeonfly.c -o obj/pigeonfly.o

birdcage.o: mkdir src/birdcage.c $(HEADERS)
	gcc $(FLAGS) -c src/birdcage.c -o obj/birdcage.o

pigeonshred.o: mkdir src/pigeonshred.c
	gcc $(FLAGS) -c src/pigeonshred.c -o obj/pigeonshred.o
	
clean:
	-rm -f pigeonshred
	-rm -f pigeonfly
	-rm -f pigeondrop
	-rm -rf obj

listclean:
	-rm -f ../lists/*
	-touch ../lists/all_available.txt

allclean: clean listclean
		
