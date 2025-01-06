/*
PIGEONDROP: todo list reader
Functionality:

"pigeondrop -a" should show all available lists
"pigeondrop (listname)" should read all items from list
"pigeondrop -ws (or windowsill)" should read all items across all lists due in the next 2 days
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int due_soon()
{
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

    file_ptr = fopen("lists/all_available", "r");
    if (NULL == file_ptr)
    {
        printf("file can't be opened \n");
        return EXIT_FAILURE;
    }

    char line[100];
    char buffer[20];
    char *s = malloc(sizeof(char) * 20);
    int cap = 20;
    int amtof_lists = 0;
    int arrayof_lists[100];

    // A no magic number solution for fgets
    while (fgets(buffer, 20, file_ptr))
    {
        if (strlen(s) + strlen(buffer) >= cap)
        {
            s = realloc(s, 2 * cap);
            cap *= 2;
        }
        strcat(s, buffer);
        arrayof_lists[amtof_lists] = line;
        amtof_lists += 1;
    }
    // Closing the file
    fclose(file_ptr);
    int i;

    for (i = 0; i < 100; i++) {
    //open each list and read things due in 2 days
    }
    return 0;

}

int all_lists()
{
    /*
    pigeondrop -a
    Functionality:
    -should show all available lists
    -takes no arguments*/

    FILE *file_ptr;

    file_ptr = fopen("lists/all_available", "r");
    if (NULL == file_ptr)
    {
        printf("file can't be opened \n");
        return EXIT_FAILURE;
    }

    char line[100];
    char buffer[20];
    char *s = malloc(sizeof(char) * 20);
    int cap = 20;

    // A no magic number solution for fgets
    while (fgets(buffer, 20, file_ptr))
    {
        if (strlen(s) + strlen(buffer) >= cap)
        {
            s = realloc(s, 2 * cap);
            cap *= 2;
        }
        strcat(s, buffer);

        printf("%s\n", line);
    }
    // Closing the file
    fclose(file_ptr);
    return 0;
}

int main(int argc, char **argv)
{

    if (argc < 2)
    {
        puts("Invalid number of arguments.\nUsage: \n\"pigeondrop -a\" should show all available lists\n\"pigeondrop (listname)\" should read all items from list\n\"pigeondrop -ws (or windowsill)\" should read all items across all lists due in the next 2 days");
        return 0;
    }
    else
    {
        char *command = argv[2];
        if (command == "-a")
        {
            all_lists();
        }
        else if (command == "-ws" | command == "-windowsill")
        {
            due_soon();
            // FUTURE UPDATE: having settings to make the windowsill set to more than / less than 2 days
        }
    }
}
