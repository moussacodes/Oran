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
    (CH) == '(' || (CH) == ')' || (CH) == '[' || (CH) == ']' || (CH) == '{' || (CH) == '}' || (CH) == ',' || (CH) == '|' || (CH) == '_' || (CH) == ';' || (CH) == ':')

#define IS_OPERATOR(CH) ( \
    (CH) == '+' || (CH) == '-' || (CH) == '*' || (CH) == '/' || (CH) == '%')

#define IS_COMPARATOR(CH) ( \
    (CH) == '=' || (CH) == '<' || (CH) == '>' || (CH) == '!')

#include <string.h>

#define IS_KEYWORD(CH) ( \
    strcmp(CH, "let") == 0 || \
    strcmp(CH, "type") == 0 || \
    strcmp(CH, "const") == 0 || \
    strcmp(CH, "Array") == 0 || \
    strcmp(CH, "return") == 0 || \
    strcmp(CH, "fn") == 0 || \
    strcmp(CH, "import") == 0 || \
    strcmp(CH, "as") == 0 || \
    strcmp(CH, "match") == 0 || \
    strcmp(CH, "if") == 0 || \
    strcmp(CH, "else") == 0 || \
    strcmp(CH, "then") == 0 || \
    strcmp(CH, "for") == 0 || \
    strcmp(CH, "while") == 0 || \
    strcmp(CH, "do") == 0 || \
    strcmp(CH, "Null") == 0 || \
    strcmp(CH, "of") == 0 || \
    strcmp(CH, "true") == 0 || \
    strcmp(CH, "false") == 0 || \
    strcmp(CH, "Int") == 0 || \
    strcmp(CH, "Byte") == 0 || \
    strcmp(CH, "Short") == 0 || \
    strcmp(CH, "Long") == 0 || \
    strcmp(CH, "UInt") == 0 || \
    strcmp(CH, "Float") == 0 || \
    strcmp(CH, "Double") == 0 || \
    strcmp(CH, "Char") == 0 || \
    strcmp(CH, "String") == 0 || \
    strcmp(CH, "Void") == 0)

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
