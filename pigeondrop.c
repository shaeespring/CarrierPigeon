/*
PIGEONDROP: todo list reader
Functionality:

"pigeondrop -a" should show all available lists
"pigeondrop (listname)" should read all items from list
"pigeondrop -ws (or windowsill)" should read all items across all lists due in
the next 2 days
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int due_soon() {
  /*
  pigeondrop -ws or pigeondrop windowsill
  Functionality:
  -reads all items across all current lists due in 2 days
  -takes no arguments
  -Future Updates:
  -user customization to hide certain lists from windowsill
  -user customization to choose times of windowsill catch
  */
  time_t t = time(NULL);
  struct tm time = *localtime(&t);
  FILE *file_ptr;
  char file_lists[] = "lists/all_available.txt";
  file_ptr = fopen(realpath(file_lists, NULL), "r");
  if (NULL == file_ptr) {
    printf("file can't be opened \n- Please report error for troubleshooting");
    return EXIT_FAILURE;
  }

  char list_path[100];
  char buffer[20];
  char *s = malloc(sizeof(char) * 20);
  int cap = 20;
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

    // open each list and read things due in 2 days
  }
  return 0;
}
char *read_line(FILE *file_ptr) {

  char buffer[20];
  char *s = malloc(sizeof(char) * 20);
  int cap = 20;

  while (fgets(buffer, 20, file_ptr)) {
    if (strlen(s) + strlen(buffer) >= cap) {
      s = realloc(s, 2 * cap);
      cap *= 2;
    }

    strcat(s, buffer);

    if (buffer[strlen(buffer) - 1] == '\n') {
      break;
    }
  }

  return s;
}
int all_lists() {
  /*
  pigeondrop -a
  Functionality:
  -should show all available lists
  -takes no arguments*/

  FILE *file_ptr;

  char file_lists[] = "lists/all_available.txt";
  file_ptr = fopen(realpath(file_lists, NULL), "r");
  if (NULL == file_ptr) {
    printf("file can't be opened \n");
    perror("");
    return EXIT_FAILURE;
  }

  char buffer[20];
  char *s = malloc(sizeof(char) * 20);
  int cap = 20;

  // A no magic number solution for fgets
  while (!feof(file_ptr)) {
    if (strlen(s) + strlen(buffer) >= cap) {
      s = realloc(s, 2 * cap);
      cap *= 2;
    }
    strcat(s, buffer);

    printf("%s", read_line(file_ptr));
  }
  // Closing the file
  fclose(file_ptr);
  return 0;
}

int main(int argc, char **argv) {
  if (argc < 2) {
    puts("Invalid number of arguments.\nUsage: \n\"pigeondrop -a\" should show "
         "all available lists\n\"pigeondrop (listname)\" should read all items "
         "from list\n\"pigeondrop -ws (or windowsill)\" should read all items "
         "across all lists due in the next 2 days");
    return 0;
  } else {
    char *command = argv[1];
    if (!strcmp(command, "-a")) {
      all_lists();
    } else if (!strcmp(command, "-ws") | !strcmp(command, "-windowsill")) {
      due_soon();
      // FUTURE UPDATE: having settings to make the windowsill set to more than
      // / less than 2 days
    }
  }
}
