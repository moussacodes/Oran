// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <stdbool.h>
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef enum
{
    TOKEN_INTEGER,
    TOKEN_FLOAT,
    TOKEN_IDENTIFIER,
    TOKEN_KEYWORD,

    TOKEN_DELIMITER,
    TOKEN_UNKNOWN
} TokenType;

typedef enum
{
    VARIABLE,
    FUNCTION,
    LOOP,
    CONDITIONAL
} PropositionType;

typedef struct
{
    int lineNumber;
    char *lineContent;
} Content;

typedef struct
{
    TokenType type;
    int lineNumber;
    int position;
    char *value;
} Token;

typedef struct
{
    Token tokens[50];
    int lineNumber;
    PropositionType propType;
} Proposition;

#define IS_DELIMITER(CH) ( \
    (CH) == '(' || (CH) == ')' || (CH) == '{' || (CH) == '}' || (CH) == ',' || (CH) == ';' || (CH) == ':')

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

Token *createToken(TokenType type, const char *value, int lineNumber, int position)
{
    Token *token = malloc(sizeof(Token));
    token->lineNumber = lineNumber;
    token->position = position;
    token->type = type;
    token->value = strdup(value);
    return token;
}

Token **tokenize(Content **input, int numLines, int *numTokens)
{
    Token **tokens = NULL;
    *numTokens = 0;

    char buffer[256]; // i will change this later to make it dynamic
    int bufferIndex = 0;
    int index = 0;

    for (int i = 0; i < numLines; i++)
    {
        while (input[i]->lineContent[index] != '\0')
        {
            char currentChar = input[i]->lineContent[index];

            // Handle whitespace
            if (isspace(currentChar))
            {
                index++;
                continue;
            }

            if (IS_DELIMITER(currentChar))
            {
                buffer[bufferIndex++] = currentChar;
                buffer[bufferIndex] = '\0';
                tokens = realloc(tokens, (*numTokens + 1) * sizeof(Token *));
                tokens[*numTokens] = createToken(TOKEN_DELIMITER, buffer, i, index + 1);
                (*numTokens)++;
                bufferIndex = 0;
                index++;
                continue;
            }

            if (isalpha(currentChar))
            {
                while (isalnum(input[i]->lineContent[index]) || input[i]->lineContent[index] == '_')
                {
                    buffer[bufferIndex++] = input[i]->lineContent[index++];
                }
                buffer[bufferIndex] = '\0';

                TokenType type = TOKEN_IDENTIFIER;
                if (strcmp(buffer, "int") == 0 || strcmp(buffer, "float") == 0)
                {
                    type = TOKEN_KEYWORD;
                }

                tokens = realloc(tokens, (*numTokens + 1) * sizeof(Token *));
                tokens[*numTokens] = createToken(type, buffer, i, index + 1);
                (*numTokens)++;
                bufferIndex = 0;
                continue;
            }

            if (isdigit(currentChar))
            {
                while (isdigit(input[i]->lineContent[index]) || input[i]->lineContent[index] == '.')
                {
                    buffer[bufferIndex++] = input[i]->lineContent[index++];
                }
                buffer[bufferIndex] = '\0';

                TokenType type = TOKEN_INTEGER;
                for (int i = 0; i < bufferIndex; i++)
                {
                    if (buffer[i] == '.')
                    {
                        type = TOKEN_FLOAT;
                        break;
                    }
                }

                tokens = realloc(tokens, (*numTokens + 1) * sizeof(Token *));
                tokens[*numTokens] = createToken(type, buffer, i, index + 1);
                (*numTokens)++;
                bufferIndex = 0;
                continue;
            }

            buffer[bufferIndex++] = currentChar;
            buffer[bufferIndex] = '\0';
            tokens = realloc(tokens, (*numTokens + 1) * sizeof(Token *));
            tokens[*numTokens] = createToken(TOKEN_UNKNOWN, buffer, i, index + 1);
            (*numTokens)++;
            bufferIndex = 0;
            index++;
        }
    }

    return tokens;
}

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
        case TOKEN_UNKNOWN:
        default:
            typeString = "UNKNOWN";
            break;
        }

        printf("Type: %s, Value: %s, Line number: %d, position: %d\n", typeString, token->value, token->lineNumber, token->position);
    }
}

char **parser(Token **tokens, int numTokens)
{
    Proposition *proposition = NULL;
    int nbPropositions = 0;
    int index = 0;
    Token *buffer[50];
    for (int i = 0; i < numTokens; i++)
    {
        buffer[index++] = tokens[i];

        if (tokens[i]->value == ";")
        {
            proposition = realloc(proposition, (nbPropositions + 1) * sizeof(Proposition));
            // proposition[] = createProposition(buffer);
            index = 0;
        }
    }
}

Content *createNewLine(char *line, int lineNumber)
{
    Content *newLine = malloc(sizeof(Content));
    newLine->lineContent = line;
    newLine->lineNumber = lineNumber;
    return newLine;
}

Content **read_file_content(const char *filename, int *lineNumber) {
    Content **fileContent = NULL;
    FILE *file = fopen(filename, "r");
    size_t lineLen = 0;
    *lineNumber = 0;
    char *lineBuffer = NULL;
    ssize_t read;

    if (file == NULL) {
        perror("Failed to open file");
        return NULL;
    }

    while ((read = getline(&lineBuffer, &lineLen, file)) != -1) {
        *lineNumber = *lineNumber + 1;
        Content *lineContent = malloc(sizeof(Content));
        lineContent->lineContent = strdup(lineBuffer);
        lineContent->lineNumber = *lineNumber;

        fileContent = realloc(fileContent, (*lineNumber) * sizeof(Content *));
        if (fileContent == NULL) {
            perror("Memory allocation failed");
            // Cleanup before returning NULL
            free(lineBuffer);
            fclose(file);
            for (int i = 0; i < *lineNumber - 1; i++) {
                free(fileContent[i]->lineContent);
                free(fileContent[i]);
            }
            free(fileContent);
            return NULL;
        }

        fileContent[*lineNumber - 1] = lineContent;
    }

    fclose(file);
    free(lineBuffer);

    return fileContent;
}
 // should free fileContent later

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

    printf("Tokens:\n");
    printTokens(tokens, numTokens);

    freeLines(fileContent, numLines);
    freeTokens(tokens, numTokens);

    return 0;
}
