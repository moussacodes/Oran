
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lexer.h"
#include "parser.h"
 #include "common.h"

 


int main(int argc, char const *argv[])
{

    char *filepath;
    Content **fileContent;
    int numLines;
    if (argc >= 2)
    {
        filepath = malloc(sizeof(strlen(argv[1]) + 4));
        strcpy(filepath, argv[1]);
        fileContent = read_file_content(filepath, &numLines);
        free(filepath);
    }
    else
    {
        printf("sorry, not enough arguments");
        exit(EXIT_FAILURE);
    }
    int numTokens;
    Token **tokens = tokenize(fileContent, numLines, &numTokens);
    // Proposition* propositions  = extract_propositions(**tokens, numTokens);

    printf("Tokens:\n");
    printTokens(tokens, numTokens);

    freeLines(fileContent, numLines);
    freeTokens(tokens, numTokens);

    return 0;
}
