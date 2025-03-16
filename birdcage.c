/*
 * A collection of helper functions for use between pigeonfly, pigeondrop, and
 * pigeonshred
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>

#include <time.h>
// for check_file
#ifdef WIN32
#endif
typedef struct date Date;
typedef struct hour Hour;
/*A time stuct for use in pigeondrop -ws*/
struct date {
  int day;
  int month;
  int year;
  int hour;
  int minute;
  int second;
};

int get_time() {
  /*
   * A helper function that registers the time given by a user
   * -Currently deadcode until pigeonfly -ws is working
   */
  Date date;

  char buf[100];
  time_t t = time(0);
  struct tm t_t = *localtime(&t);
  strftime(buf, 100, "%d-%m-%Y %H:%M:%S", &t_t);

  date.year = t_t.tm_year + 1900; // years since 1900
  date.month = t_t.tm_mon + 1;    // months since January
  date.day = t_t.tm_mday;         // day of month

  date.hour = t_t.tm_hour;
  date.minute = t_t.tm_min;
  date.second = t_t.tm_sec;

  return 0;
}

char *read_line(FILE *file_ptr) {
  /*A helper function that returns the next line of a file pointer
   * Used in all three major command files
   */
  char buffer[21];
  char *s = calloc(20, sizeof(char));
  unsigned int cap = 20;
  size_t len;
  buffer[20] = '\0';
  while ((len = fread(buffer, sizeof(char), 20, file_ptr))) {
    if (strlen(s) + strlen(buffer) >= cap) {
      s = realloc(s, 2 * cap);
      cap *= 2;
    }
    strcat(s, buffer);

    int index = strchr(buffer, '\0') - buffer;

    if (index != 20) {
      if (fseek(file_ptr, index - len + 1, SEEK_CUR)) {
        perror("fseek() failed");
      }
      break;
    }
  }

  return s;
}

int contains_list(char *filename) {
  /* A helper function that returns if the given file is a list inside of
   * all_available.txt used in all three major command files
   */
  char *all = "lists/all_available.txt";
  FILE *ptrlists = fopen(all, "r");
  int contains_list = 0; // listname is not in list
  char *s = read_line(ptrlists);
  while (strlen(s) > 1) {
    if (!strcmp(s, filename)) {
      contains_list = 1; // listname is in list
      break;
    }
    s = read_line(ptrlists);
  }
  free(s);
  fclose(ptrlists);
  return contains_list;
}
