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
  /*
   * pigeonshred (listname)
   * Functionality:
   * -removes an entire list of tasks
   * -prints a congratulatory message
   * -returns an Exit Failure if the list doesn't exist*/
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

int taskshred(char *listname, char *task) {
  /*
   * pigeonshred (listname) (task)
   * Functionality:
   *  -removes a given task from a given list
   *  -prints a congratulatory message
   *  -returns an Exit Failure if the list doesn't exist*/
  char *list = malloc(strlen(listname) + strlen("lists/.txt") + 1);
  sprintf(list, "lists/%s.txt", listname);
  if (!contains_list(listname)) {
    printf("list: %s not available\n", listname);
    return EXIT_FAILURE;
  } else {
    FILE *tasks = fopen(list, "r");
    FILE *new = fopen("list.txt.new", "a");
    while (!feof(tasks)) {
      char *line = read_line(tasks);
      if (strcmp(line, task)) {
        fprintf(new, "%s", line);
      }
    }
    fclose(new);
    remove(list);
    printf("%s completed! Congrats!", task);
    rename("list.txt.new", list);
    return 0;
  }
}

int main(int argc, char **argv) {
  if (argc < 2) {
    puts("Invalid number of arguments.\nUsage: \n\"shred (listname)\" will "
         "remove the given list");
    return 0;
  } else {
    char *list = argv[1];
    if (argc == 3) {
      char *task = argv[2];
      taskshred(list, task);
    } else {
      pigeonshred(list);
    }
  }
}
