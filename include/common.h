#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct
{
    int lineNumber;
    char *lineContent;
} Content;

typedef enum
{
    TOKEN_INTEGER,
    TOKEN_FLOAT,
    TOKEN_DEFAULT_KEY,
    TOKEN_OPTION,
    TOKEN_COMPARATOR,
    TOKEN_IDENTIFIER,
    TOKEN_OPERATOR,
    TOKEN_KEYWORD,
    TOKEN_DELIMITER,
    TOKEN_UNKNOWN
} TokenType;

typedef struct
{
    TokenType type;
    int lineNumber;
    int position;
    char *value;
} Token;

#define IS_DELIMITER(CH) ( \
    (CH) == '(' || (CH) == ')' || (CH) == '{' || (CH) == '}' || (CH) == ',' || (CH) == '|' || (CH) == '_' || (CH) == ';' || (CH) == ':')

#define IS_OPERATOR(CH)( \
    (CH) == '+' || (CH) == '-' || (CH) == '*' || (CH) == '/' || (CH) == '%')

#define IS_COMPARATOR(CH) ( \
    (CH) == '=' || (CH) == '<' || (CH) == '>' || (CH) == '!')

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

void freeTokens(Token **tokens, int numTokens);

void freeLines(Content **fileContent, int numLines);

void printTokens(Token **tokens, int numTokens);

#endif /* COMMON_H */
