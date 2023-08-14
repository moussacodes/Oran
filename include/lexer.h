#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#include "common.h"


 
Content *createNewLine(char *line, int lineNumber);
Content **read_file_content(const char *filename, int *lineNumber);
Token *createToken(TokenType type, const char *value, int lineNumber, int position);
Token **tokenize(Content **input, int numLines, int *numTokens);

#endif // LEXER_H
