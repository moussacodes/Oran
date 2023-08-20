#define _GNU_SOURCE
#include "lexer.h"

Content *createNewLine(char *line, int lineNumber)
{
    Content *newLine = malloc(sizeof(Content));
    if (newLine == NULL)
    {
        perror("Memory allocation failed");
        free(newLine);
        return NULL;
    }
    newLine->lineContent = strdup(line);
    newLine->lineNumber = lineNumber;
    return newLine;
}

Content **read_file_content(const char *filename, int *lineNumber)
{
    Content **fileContent = NULL;
    FILE *file = fopen(filename, "r");
    size_t lineLen = 0;
    *lineNumber = 0;
    char *lineBuffer = NULL;
    ssize_t read;

    if (file == NULL)
    {
        perror("Failed to open file");
        return NULL;
    }

    while ((read = getline(&lineBuffer, &lineLen, file)) != -1)
    {
        *lineNumber = *lineNumber + 1;
        Content *lineContent = createNewLine(lineBuffer, *lineNumber);
        fileContent = realloc(fileContent, (*lineNumber) * sizeof(Content *));
        if (fileContent == NULL)
        {
            perror("Memory allocation failed");
            // Cleanup before returning NULL
            free(lineBuffer);
            fclose(file);
            for (int i = 0; i < *lineNumber - 1; i++)
            {
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

    char buffer[256];
    int bufferIndex = 0;

    for (int i = 0; i < numLines; i++)
    {
        int index = 0;

        while (input[i]->lineContent[index] != '\0')
        {
            char currentChar = input[i]->lineContent[index];

            if (isspace(currentChar))
            {
                index++;
                continue;
            }

            if (IS_DELIMITER(currentChar))
            {
                TokenType type = TOKEN_DELIMITER;
                if (currentChar == '|')
                {
                    type = TOKEN_OPTION;
                }
                else if (currentChar == '_')
                {
                    type = TOKEN_DEFAULT_KEY;
                }
                buffer[bufferIndex] = currentChar;
                buffer[bufferIndex + 1] = '\0'; // Null-terminate the buffer
                tokens = realloc(tokens, (*numTokens + 1) * sizeof(Token *));
                tokens[*numTokens] = createToken(type, buffer, i, index + 1);
                (*numTokens)++;
                bufferIndex = 0;
                index++;
                continue;
            }

            if (IS_OPERATOR(currentChar))
            {
                TokenType type = TOKEN_OPERATOR;
                buffer[bufferIndex++] = currentChar;

                if (input[i]->lineContent[index] == '-' && input[i]->lineContent[index + 1] == '>')
                {
                    buffer[bufferIndex++] = '>';
                    index++;
                }

                buffer[bufferIndex] = '\0'; // Null-terminate the buffer

                tokens = realloc(tokens, (*numTokens + 1) * sizeof(Token *));
                tokens[*numTokens] = createToken(type, buffer, i, index - bufferIndex + 1);
                (*numTokens)++;

                bufferIndex = 0;
                index++;
                continue;
            }

            if (IS_COMPARATOR(currentChar))
            {
                TokenType type = TOKEN_COMPARATOR;
                buffer[bufferIndex++] = currentChar;

                if (input[i]->lineContent[index + 1] == '=')
                {
                    buffer[bufferIndex++] = '=';
                    index++;
                }
                if (input[i]->lineContent[index] == '=' && input[i]->lineContent[index + 1] == '>')
                {
                    buffer[bufferIndex++] = '>';
                    type = TOKEN_DEFAULT_KEY;
                    index++;
                }
                buffer[bufferIndex] = '\0'; // Null-terminate the buffer

                tokens = realloc(tokens, (*numTokens + 1) * sizeof(Token *));
                tokens[*numTokens] = createToken(type, buffer, i, index - bufferIndex + 1);
                (*numTokens)++;

                bufferIndex = 0;
                index++;
                continue;
            }

            // <= >= == !=
            if (isalpha(currentChar))
            {
                while (isalnum(input[i]->lineContent[index]) || input[i]->lineContent[index] == '_')
                {
                    buffer[bufferIndex++] = input[i]->lineContent[index++];
                }
                buffer[bufferIndex] = '\0';

                TokenType type = TOKEN_IDENTIFIER;
                if (IS_KEYWORD(buffer))
                {
                    type = TOKEN_KEYWORD;
                }

                tokens = realloc(tokens, (*numTokens + 1) * sizeof(Token *));
                tokens[*numTokens] = createToken(type, buffer, i, index - bufferIndex + 1);
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
                for (int j = 0; j < bufferIndex; j++)
                {
                    if (buffer[j] == '.')
                    {
                        type = TOKEN_FLOAT;
                        break;
                    }
                }

                tokens = realloc(tokens, (*numTokens + 1) * sizeof(Token *));
                tokens[*numTokens] = createToken(type, buffer, i, index - bufferIndex + 1);
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
