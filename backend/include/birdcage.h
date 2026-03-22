#ifndef BIRDCAGE_H
#define BIRDCAGE_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define LISTS_AVAILABLE "../lists/all_available.txt"
#define LISTS_DIR "../lists/"
typedef struct date Date;
typedef struct hour Hour;

struct date {
  int day;
  int month;
  int year;
  int hour;
  int minute;
  int second;
};
#ifdef WIN32
#include <io.h>
#define F_OK 0
#define access _access
#endif
Date *get_sys_time();
int contains_list(char *file_ptr);
char *read_line(FILE *file_ptr);
FILE *redirect_to_file();
void print_output_to_stdout();
#endif // BIRDCAGE_H
