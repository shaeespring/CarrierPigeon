/*
 * A collection of helper functions for use between pigeonfly, pigeondrop, and
 * pigeonshred
 */

#include "birdcage.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
// for check_file
#ifdef WIN32
#endif

#define OUTPUT_FILE "output.txt"

Date *get_sys_time() {
  /*
   * A helper function that registers the system time when inquired by a user
   * -Currently deadcode until pigeonfly -ws is working
   */
  Date *date;

  char buf[100];
  time_t t = time(0);
  struct tm t_t = *localtime(&t);
  strftime(buf, 100, "%d-%m-%Y %H:%M:%S", &t_t);

  date->year = t_t.tm_year + 1900; // years since 1900
  date->month = t_t.tm_mon + 1;    // months since January
  date->day = t_t.tm_mday;         // day of month

  date->hour = t_t.tm_hour;
  date->minute = t_t.tm_min;
  date->second = t_t.tm_sec;

  return date;
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
  FILE *ptrlists = fopen(LISTS_AVAILABLE, "r");
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

FILE *redirect_to_file() {
  FILE *file_ptr = fopen(OUTPUT_FILE, "w");
  if (NULL == file_ptr) {
    perror("Failed to create output file for pigeondrop");
    return NULL;
  }
  return file_ptr;
}

void print_output_to_stdout() {
  FILE *file_ptr = fopen(OUTPUT_FILE, "r");
  if (NULL == file_ptr) {
    perror("Cannot read output file for pigeondrop");
    return;
  }
  char buffer[1024]; // TEN TWENTY FOUR!!!
  while (fgets(buffer, sizeof(buffer), file_ptr)) {
    fclose(file_ptr);
  }
  remove(OUTPUT_FILE);
}
