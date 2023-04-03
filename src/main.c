#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void get_file_content(char *path)
{ // we should get the file path dynamicaly now matter where the program is executed from
    FILE *file;
    char c;
    file = fopen(path, "r");
    if (file == NULL)
    {
        printf("Sorry, file %s doesn't exist\n", path);
        exit(EXIT_FAILURE);
    }
    printf("File contents:\n");
    while ((c = fgetc(file)) != EOF)
    {
        printf("%c", c);
    }
    fclose(file);
}

int main(int argc, char const *argv[])
{
    char *filepath;
    if (argc >= 2)
    {
        filepath = malloc(sizeof(strlen(argv[1]) + 4));
        strcpy(filepath, argv[1]);
        get_file_content(filepath);
        free(filepath);
    }
    else
    {
        printf("sorry, not enough arguments");
        exit(EXIT_FAILURE);
    }

    return 0;
}
