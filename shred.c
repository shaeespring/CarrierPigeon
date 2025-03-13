/*
 * SHRED: todo list shredder
 * Functionality:
 *
 * "shred (listname)" should destroy the filepath to the todo list
 * which will remove all items inside of the list, as well as removing it from
 * the list of all available lists
 */

#include "birdcage.h"
#include <string.h>

int shred(char *listname) {
  if (contains_list(listname)) {
    printf("list: %s not available", listname);
    return EXIT_FAILURE;
  } else {
    FILE *all = fopen("lists/all_available.txt", "r");
    char *s = read_line(all);
    FILE *new = fopen("all_available.txt.new", "a");
    while (!feof(all)) {
      char *line = read_line(all);
      if (!strlen(line)) {
        break;
      } else if (strcmp(line, listname)) {
        printf("%s\n", line);
      }
    }
    fclose(all);
    fclose(new);
    remove("lists/all_available.txt");
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
    shred(command);
  }
}
