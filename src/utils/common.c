
#include "common.h"

 

#define FREE_TOKEN(token)     \
    do                        \
    {                         \
        free((token)->value); \
        free(token);          \
    } while (0)

#define FREE_LINES(line)           \
    do                             \
    {                              \
        free((line)->lineContent); \
        free(line);                \
    } while (0)

void freeTokens(Token **tokens, int numTokens)
{
    for (int i = 0; i < numTokens; i++)
    {
        FREE_TOKEN(tokens[i]);
    }
    free(tokens);
}

void freeLines(Content **fileContent, int numLInes)
{
    for (int i = 0; i < numLInes; i++)
    {
        FREE_LINES(fileContent[i]);
    }
    free(fileContent);
}

void printTokens(Token **tokens, int numTokens)
{
    for (int i = 0; i < numTokens; i++)
    {
        Token *token = tokens[i];
        const char *typeString;

        switch (token->type)
        {
        case TOKEN_INTEGER:
            typeString = "INTEGER";
            break;
        case TOKEN_FLOAT:
            typeString = "FLOAT";
            break;
        case TOKEN_IDENTIFIER:
            typeString = "IDENTIFIER";
            break;
        case TOKEN_KEYWORD:
            typeString = "KEYWORD";
            break;

        case TOKEN_DELIMITER:
            typeString = "DELIMITER";
            break;
        case TOKEN_COMPARATOR:
            typeString = "COMPARATOR";
            break;
        case TOKEN_DEFAULT_KEY:
            typeString = "DEFAULT_KEY";
            break;
        case TOKEN_OPTION:
            typeString = "OPTION";
            break;

        case TOKEN_OPERATOR:
            typeString = "OPERATOR";
            break;
        case TOKEN_UNKNOWN:
        default:
            typeString = "UNKNOWN";
            break;
        }

        printf("Type: %s,\t\t Value: %s,\t\t Line number: %d,\t\t position: %d\n", typeString, token->value, token->lineNumber, token->position);
    }
}
