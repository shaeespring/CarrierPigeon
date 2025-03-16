/*
PIGEONFLY: Writes todo items to lists

FUNCTIONALITY:
"pigeonfly (listname) -m (message)" to write to a file containing a to
do list. Entering a valid message should prompt user to add an optional due date
*/

#include "birdcage.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int appendTask(char *message, char *listname) {
  /*
   * pigeonfly (listname) -m (message)
   * FUNCTIONALITY:
   * -adds a given task to a given list
   * -will not add the list to the list of all lists if the list already exists
   *
   * */
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
    return EXIT_FAILURE;
  }
  fprintf(fileptr, "%s", message);
  fputc('\0', fileptr);
  if (!contains_list(listname)) {
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

  return 0;
}
