#ifndef BIRDCAGE_H
#define BIRDCAGE_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#ifdef WIN32
#include <io.h>
#define F_OK 0
#define access _access
#endif

char *check_file(char *file_ptr);
char *read_line(FILE *file_ptr);
#endif // BIRDCAGE_H
