HEADERS = backend/include/birdcage.h
FLAGS = -Wall -Wextra --pedantic -ggdb -Ibackend/include

mkdir:
	mkdir -p backend/obj
	mkdir -p middleware

# Backend  
pigeondrop: mkdir backend/birdcage.o backend/pigeondrop.o
	gcc $(FLAGS) -o backend/pigeondrop backend/obj/birdcage.o backend/obj/pigeondrop.o

pigeonfly: mkdir backend/birdcage.o backend/pigeonfly.o
	gcc $(FLAGS) -o backend/pigeonfly backend/obj/birdcage.o backend/obj/pigeonfly.o

pigeonshred: mkdir backend/birdcage.o backend/pigeonshred.o
	gcc $(FLAGS) -o backend/pigeonshred backend/obj/birdcage.o backend/obj/pigeonshred.o

# Middleware 
socket: mkdir middleware/socket.o backend/birdcage.o backend/pigeondrop_webserver.o
	gcc $(FLAGS) -DWEBSERVER -o middleware/socket middleware/socket.o backend/obj/birdcage.o backend/obj/pigeondrop_webserver.o

all: pigeondrop pigeonfly pigeonshred socket

# Regular
backend/pigeondrop.o: mkdir backend/src/pigeondrop.c
	gcc $(FLAGS) -c backend/src/pigeondrop.c -o backend/obj/pigeondrop.o

backend/pigeonfly.o: mkdir backend/src/pigeonfly.c
	gcc $(FLAGS) -c backend/src/pigeonfly.c -o backend/obj/pigeonfly.o

backend/pigeonshred.o: mkdir backend/src/pigeonshred.c
	gcc $(FLAGS) -c backend/src/pigeonshred.c -o backend/obj/pigeonshred.o

# Special version for webserver 
backend/pigeondrop_webserver.o: mkdir backend/src/pigeondrop.c
	gcc $(FLAGS) -DWEBSERVER -c backend/src/pigeondrop.c -o backend/obj/pigeondrop_webserver.o

backend/birdcage.o: mkdir backend/src/birdcage.c $(HEADERS)
	gcc $(FLAGS) -c backend/src/birdcage.c -o backend/obj/birdcage.o

middleware/socket.o: mkdir middleware/socket.c
	gcc $(FLAGS) -DWEBSERVER -c middleware/socket.c -o middleware/socket.o

clean:
	-rm -f backend/pigeondrop backend/pigeonfly backend/pigeonshred
	-rm -f middleware/socket
	-rm -rf backend/obj

listclean:
	-rm -f lists/*
	-touch lists/all_available.txt

allclean: clean listclean
