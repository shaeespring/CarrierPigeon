/*
 * PIGEONSHRED: todo list shredder
 * Functionality:
 *
 * "pigeonshred (listname)" should destroy the filepath to the todo list
 * which will remove all items inside of the list, as well as removing it from
 * the list of all available lists
 */

#include "birdcage.h"
#include <string.h>

int pigeonshred(char *listname) {
  if (!contains_list(listname)) {
    printf("list: %s not available\n", listname);
    return EXIT_FAILURE;
  } else {
    FILE *all = fopen("lists/all_available.txt", "r");
    FILE *new = fopen("all_available.txt.new", "a");
    while (!feof(all)) {
      char *line = read_line(all);
      if (strcmp(line, listname)) {
        fprintf(new, "%s", line);
      }
    }
    fclose(all);
    fclose(new);
    remove("lists/all_available.txt");
    char *list = malloc(strlen(listname) + strlen("lists/.txt") + 1);
    sprintf(list, "lists/%s.txt", listname);
    remove(list);
    printf("%s completed! Congrats!", list);
    rename("all_available.txt.new", "lists/all_available.txt");
    return 0;
  }
}

int main(int argc, char **argv) {
  if (argc < 2) {
    puts("Invalid number of arguments.\nUsage: \n\"shred (listname)\" will "
         "remove the given list");
    return 0;
  } else {
    char *command = argv[1];
    pigeonshred(command);
  }
}
