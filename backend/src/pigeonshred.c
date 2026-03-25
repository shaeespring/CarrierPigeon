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

extern int pigeonshred(FILE *output, char *listname) {
  /*
   * pigeonshred (listname)
   * Functionality:
   * -removes an entire list of tasks
   * -prints a congratulatory message
   * -returns an Exit Failure if the list doesn't exist*/
  if (!contains_list(listname)) {
    fprintf(output, "list: %s not available\n", listname);
    return EXIT_FAILURE;
  } else {
    FILE *all = fopen(LISTS_AVAILABLE, "r");
    FILE *new = fopen("all_available.txt.new", "w");
    while (!feof(all)) {
      char *line = read_line(all);
      if (strcmp(line, listname)) {
        fprintf(new, "%s", line);
      }
    }
    fclose(all);
    fclose(new);
    remove(LISTS_AVAILABLE);
    char *list =
        malloc(strlen(listname) + strlen(LISTS_DIR) + strlen(".txt") + 1);
    sprintf(list, LISTS_DIR "%s.txt", listname);
    remove(list);
    fprintf(output, "%s completed! Congrats!", list);
    rename("all_available.txt.new", LISTS_AVAILABLE);
    return 0;
  }
}

int taskshred(FILE *output, char *listname, char *task) {
  /*
   * pigeonshred (listname) (task)
   * Functionality:
   *  -removes a given task from a given list
   *  -prints a congratulatory message
   *  -returns an Exit Failure if the list doesn't exist*/
  char *list =
      malloc(strlen(listname) + strlen(LISTS_DIR) + strlen(".txt") + 1);
  sprintf(list, LISTS_DIR "%s.txt", listname);
  if (!contains_list(listname)) {
    fprintf(output, "list: %s not available\n", listname);
    return EXIT_FAILURE;
  } else {
    FILE *tasks = fopen(list, "r");
    FILE *new = fopen("list.txt.new", "w");
    while (!feof(tasks)) {
      char *line = read_line(tasks);
      if (strcmp(line, task)) {
        fprintf(new, "%s", line);
      }
    }
    fclose(new);
    remove(list);
    fprintf(output, "%s completed! Congrats!", task);
    rename("list.txt.new", list);
    return 0;
  }
}

#ifndef WEBSERVER
int main(int argc, char **argv) {
  if (argc < 2) {
    puts("Invalid number of arguments.\nUsage: \n\"shred (listname)\" will "
         "remove the given list");
    return 0;
  } else {
    char *list = argv[1];
    if (argc == 3) {
      char *task = argv[2];
      taskshred(stdout, list, task);
    } else {
      pigeonshred(stdout, list);
    }
  }
}
#endif
