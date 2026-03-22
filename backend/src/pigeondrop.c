/*
PIGEONDROP: todo list reader
Functionality:

"pigeondrop -a" shows all available lists
"pigeondrop (listname)" reads all items from the given list
"pigeondrop -ws (or windowsill)" should read all items across all lists due in
the next 2 days
*/
#include "birdcage.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int due_soon(FILE *output) {

  /*
  pigeondrop -ws or pigeondrop windowsill
  Functionality:
  -reads all items across all current lists due in 2 days
  -takes no arguments
  -Future Updates:
  -user customization to hide certain lists from windowsill
  -user customization to choose times of windowsill catch
  */

  Date *time = get_sys_time();
  // Get the string of local time
  fprintf(output, "Items due by %d/%d/%d\n", time->month, time->day + 2,
          time->year);
  FILE *file_ptr;
  file_ptr = fopen(realpath(LISTS_AVAILABLE, NULL), "r");
  if (NULL == file_ptr) {
    perror("file can't be opened\n");
    return EXIT_FAILURE;
  }

  char list_path[100];
  char buffer[20];
  char *s = malloc(sizeof(char) * 20);
  unsigned int cap = 20;
  int idx = 0;
  char *list_paths[100];

  // A no magic number solution for fgets
  while (fgets(buffer, 20, file_ptr)) {
    if (strlen(s) + strlen(buffer) >= cap) {
      s = realloc(s, 2 * cap);
      cap *= 2;
    }
    strcat(s, buffer);
    list_paths[idx] = list_path;
    idx += 1;
  }

  // Closing the file
  fclose(file_ptr);
  int i;

  for (i = 0; i < 100; i++) {

    file_ptr = fopen(realpath(LISTS_AVAILABLE, NULL), "r");
    // open each list and read things due in 2 days
  }
  return 0;
}

int given_list(FILE *output, char *listname) {
  /*
   * pigeondrop (listname)
   * Functionality:
   * -Shows the tasks in the given list
   * -Throws an exit failure if the given list hasn't been created yet
   * */
  char *list =
      malloc(strlen(listname) + strlen(LISTS_DIR) + strlen(".txt") + 1);
  sprintf(list, LISTS_DIR "%s.txt", listname);
  FILE *file_ptr = fopen(list, "r");

  if (!contains_list(listname)) {
    fprintf(output, "list:%s not available", listname);
    return EXIT_FAILURE;
  } else {
    while (!feof(file_ptr)) {
      char *line = read_line(file_ptr);
      if (!strlen(line)) {
        fclose(file_ptr);
        break;
      }
      fprintf(output, "%s\n", line);
    }
  }
  return 0;
}

int all_lists(FILE *output) {
  /*
  pigeondrop -a
  Functionality:
  -Shows all available lists
  -takes no arguments*/

  FILE *file_ptr;
  file_ptr = fopen(realpath(LISTS_AVAILABLE, NULL), "r");
  if (NULL == file_ptr) {
    perror("file can't be opened");
    return EXIT_FAILURE;
  }

  // A no magic number solution for fgets
  while (!feof(file_ptr)) {
    char *line = read_line(file_ptr);
    if (!strlen(line)) {
      break;
    }
    fprintf(output, "%s\n", line);
  }
  fclose(file_ptr);
  return 0;
}

int main(int argc, char **argv) {
  int result;
  if (argc < 2) {
    puts("Invalid number of arguments.\nUsage: \n\"pigeondrop -a\" should "
         "show "
         "all available lists\n\"pigeondrop (listname)\" should read all "
         "items "
         "from list\n\"pigeondrop -ws (or windowsill)\" should read all items "
         "across all lists due in the next 2 days");
    return 0;
  } else {
    char *command = argv[1];
    if (!strcmp(command, "-a")) {
      result = all_lists(stdout);
    } else if (!strcmp(command, "-ws") | !strcmp(command, "-windowsill")) {
      result = due_soon(stdout);
      // TODO: having settings to make the windowsill set to more/less than 2
      // days
    } else {
      result = given_list(stdout, command);
    }
  }
}
