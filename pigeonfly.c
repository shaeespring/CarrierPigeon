/*
PIGEONFLY: Writes todo items to lists

FUNCTIONALITY:
"pigeonfly (listname) -m (message, enquoted)" to write to a file containing a to
do list. Entering a valid message should prompt user to add an optional due date
*/

#include "birdcage.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int appendTask(char *message, char *listname) {
  char *all = "lists/all_available.txt";
  FILE *ptrlists = fopen(all, "a+");

  if (ptrlists == NULL) {
    printf("Failed to open file: %s", all);
    return EXIT_FAILURE;
  }

  char *list = malloc(strlen(listname) + strlen("lists/.txt") + 1);
  sprintf(list, "lists/%s.txt", listname);
  FILE *fileptr = fopen(list, "a");

  if (fileptr == NULL) {
    perror("fopen() failed");
  }
  fprintf(fileptr, "%s", message);
  fputc('\0', fileptr);
  int contains_list = 0; // listname is not in list
  char *s = read_line(ptrlists);
  while (strlen(s) > 1) {
    printf("list: |%s|", s);
    if (!strcmp(s, listname)) {
      contains_list = 1; // listname is in list
      break;
    }
    s = read_line(ptrlists);
  }
  if (!contains_list) {
    fprintf(ptrlists, "%s", listname);
    fputc('\0', ptrlists);
  }
  fclose(ptrlists);
  fclose(fileptr);
  return 0;
}

int main(int argc, char **argv) {
  char *command = argv[2];
  if (argc < 3) {
    puts("Invalid number of arguments.\nUsage: pigeonfly (listname) (item)");
    return 0;
  }

  char *listname = argv[1];

  if (!strcmp(command, "-m")) {
    char *message = argv[3];
    appendTask(message, listname);
  }

  //    system(PIGEONFLY);
  return 0;
}
