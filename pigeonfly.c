/*
PIGEONFLY: Writes todo items to lists

FUNCTIONALITY:
"pigeonfly (listname) -m (message, enquoted)" to write to a file containing a to
do list. Entering a valid message should prompt user to add an optional due date
*/

#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
  char *command = argv[2];
  if (argc < 3) {
    puts("Invalid number of arguments.\nUsage: pigeonfly (listname) (item)");
    return 0;
  }

  puts("Will execute sh with the following script :");
  char *listname = argv[1];
  puts(listname);

  if (strcmp(command, "-m")) {
    char *message = argv[3];
  }

  puts("Starting now:");
  //    system(PIGEONFLY);
  return 0;
}
