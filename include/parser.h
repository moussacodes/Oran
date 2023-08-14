#ifndef PARSER_H
#define PARSER_H

#include "common.h"

typedef enum
{
    VARIABLE,
    FUNCTION,
    LOOP,
    CONDITIONAL
} PropositionType;


typedef struct
{
    Token tokens[50];
    int lineNumber;
    PropositionType propType;
} Proposition;


char **parser(Token **tokens, int numTokens);

#endif // PARSER_H
