/*
PIGEONFLY: Writes todo items to lists

FUNCTIONALITY:
"pigeonfly (listname) -m (message, enquoted)" to write to a file containing a to
do list. Entering a valid message should prompt user to add an optional due date
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
// for check_file
#ifdef WIN32
#include <io.h>
#define F_OK 0
#define access _access
#endif

int check_file(char *filename) {

  if (access(filename, F_OK) == 0 && access(filename, R_OK) == 0 &&
      access(filename, W_OK) == 0) {
    return 1;
  } else {

    printf("file can't be opened");
    return 0;
  }
}

int appendTask(char *message, char *listname) {
  FILE *fileptr;
  FILE *ptrlists;
  if (check_file("lists/all_available.txt") == 1) {
    ptrlists = fopen("lists/all_available.txt", "a");

    return 0;
  } else {
    return EXIT_FAILURE;
  }
}

int main(int argc, char **argv) {
  char *command = argv[2];
  if (argc < 3) {
    puts("Invalid number of arguments.\nUsage: pigeonfly (listname) (item)");
    return 0;
  }

  puts("Will execute sh with the following script :");
  char *listname = argv[1];
  puts(listname);

  if (!strcmp(command, "-m")) {
    char *message = argv[3];
    appendTask(message, argv[2]);
  }

  puts("Starting now:");
  //    system(PIGEONFLY);
  return 0;
}
