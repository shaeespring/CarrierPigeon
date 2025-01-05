/*
PIGEONDROP: todo list reader
Functionality:

"pigeondrop -a" should show all available lists
"pigeondrop (listname)" should read all items from list
"pigeondrop -ws (or windowsill)" should read all items across all lists due in the next 2 days
*/
#include <stdio.h>
#include <stdlib.h>

int all_lists(){

    FILE *file_ptr;

    file_ptr = fopen("lists/all_available", "r");
    if (NULL == file_ptr) {
        printf("file can't be opened \n");
        return EXIT_FAILURE;
    }

    char line[100];
    char buffer[20];
    char *s = malloc(sizeof(char)*20);
    int cap = 20;

//A no magic number solution for fgets
	while(fgets(buffer, 20, file_ptr)){
        if (strlen(s) + strlen(buffer) >=cap){
            s = realloc(s, 2*cap);
            cap *= 2;
        }
        strcat(s,buffer);

        printf("%s\n", line);
    }
    // Closing the file
    fclose(file_ptr);
    return 0;
}


int main(int argc, char **argv) {

    if (argc<2){
    puts("Invalid number of arguments.\nUsage: \n\"pigeondrop -a\" should show all available lists\n\"pigeondrop (listname)\" should read all items from list\n\"pigeondrop -ws (or windowsill)\" should read all items across all lists due in the next 2 days");
    return 0;
    }
    else{
        char* command = argv[2];   
        if (command == "-a") {
            all_lists();
        }
    }
    

}


