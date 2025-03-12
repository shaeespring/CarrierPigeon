#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>

#include <time.h>
// for check_file
#ifdef WIN32
#include <io.h>
#define F_OK 0
#define access _access
#endif
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

int get_time(void) {

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

int check_file(char *filename) {
  if (access(filename, F_OK) != 0) {
    printf("File %s does not exist", filename);
    return 0;
  }
  if (access(filename, R_OK) != 0) {
    printf("File %s not readable", filename);
    return 0;
  }
  if (access(filename, W_OK) != 0) {
    printf("File %s cannot be written to", filename);
    return 0;
  } else {
    return 1;
  }
}

// FIXME: NEEDS DOCUMENTATION
char *read_line(FILE *file_ptr) {
  char buffer[21];
  char *s = malloc(sizeof(char) * 20);
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
