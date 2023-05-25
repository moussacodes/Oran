// #include <stdio.h>
// #include <sys/stat.h>
// #include <stdlib.h>
// #include <string.h>
// #include <stdbool.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Token types enumeration
typedef enum
{
    TOKEN_INTEGER,
    TOKEN_FLOAT,
    TOKEN_IDENTIFIER,
    TOKEN_KEYWORD,

    TOKEN_DELIMITER,
    TOKEN_UNKNOWN
} TokenType;

// Token structure
typedef struct
{
    TokenType type;
    char *value;
} Token;


int isDelimiter(char ch)
{
    return (ch == '(' || ch == ')' || ch == '{' || ch == '}' || ch == ',' || ch == ';' || ch == ':');
}

Token *createToken(TokenType type, const char *value)
{
    Token *token = malloc(sizeof(Token));
    token->type = type;
    token->value = strdup(value);
    return token;
}

void freeToken(Token *token)
{
    free(token->value);
    free(token);
}

Token **tokenize(const char *input, int *numTokens)
{
    Token **tokens = NULL;
    *numTokens = 0;

    char buffer[256];  //i will change this later to make it dynamic
    int bufferIndex = 0;

    int index = 0;

    while (input[index] != '\0')
    {
        char currentChar = input[index];

        // Handle whitespace
        if (isspace(currentChar))
        {
            index++;
            continue;
        }

        if (isDelimiter(currentChar))
        {
            buffer[bufferIndex++] = currentChar;
            buffer[bufferIndex] = '\0';
            tokens = realloc(tokens, (*numTokens + 1) * sizeof(Token *));
            tokens[*numTokens] = createToken(TOKEN_DELIMITER, buffer);
            (*numTokens)++;
            bufferIndex = 0;
            index++;
            continue;
        }

        if (isalpha(currentChar))
        {
            while (isalnum(input[index]) || input[index] == '_')
            {
                buffer[bufferIndex++] = input[index++];
            }
            buffer[bufferIndex] = '\0';

            TokenType type = TOKEN_IDENTIFIER;
            if (strcmp(buffer, "int") == 0 || strcmp(buffer, "float") == 0)
            {
                type = TOKEN_KEYWORD;
            }

            tokens = realloc(tokens, (*numTokens + 1) * sizeof(Token *));
            tokens[*numTokens] = createToken(type, buffer);
            (*numTokens)++;
            bufferIndex = 0;
            continue;
        }

        if (isdigit(currentChar))
        {
            while (isdigit(input[index]) || input[index] == '.')
            {
                buffer[bufferIndex++] = input[index++];
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
            tokens[*numTokens] = createToken(type, buffer);
            (*numTokens)++;
            bufferIndex = 0;
            continue;
        }

        buffer[bufferIndex++] = currentChar;
        buffer[bufferIndex] = '\0';
        tokens = realloc(tokens, (*numTokens + 1) * sizeof(Token *));
        tokens[*numTokens] = createToken(TOKEN_UNKNOWN, buffer);
        (*numTokens)++;
        bufferIndex = 0;
        index++;
    }

    return tokens;
}

void freeTokens(Token **tokens, int numTokens)
{
    for (int i = 0; i < numTokens; i++)
    {
        freeToken(tokens[i]);
    }
    free(tokens);
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

        printf("Type: %s, Value: %s\n", typeString, token->value);
    }
}

char *read_file_content(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        perror("Failed to open file");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    char *content = (char *)malloc(file_size + 1);
    if (content == NULL)
    {
        fclose(file);
        perror("Failed to allocate memory");
        return NULL;
    }

    size_t bytes_read = fread(content, 1, file_size, file);
    if (bytes_read != file_size)
    {
        fclose(file);
        free(content);
        perror("Failed to read file");
        return NULL;
    }

    content[file_size] = '\0';

    fclose(file);
    return content;
}

int main(int argc, char const *argv[])
{

    char *filepath;
    char *fileContent;
    if (argc >= 2)
    {
        filepath = malloc(sizeof(strlen(argv[1]) + 4));
        strcpy(filepath, argv[1]);
        fileContent = read_file_content(filepath);
        free(filepath);
    }
    else
    {
        printf("sorry, not enough arguments");
        exit(EXIT_FAILURE);
    }
    int numTokens;
    Token **tokens = tokenize(fileContent, &numTokens);

    printf("Tokens:\n");
    printTokens(tokens, numTokens);

    freeTokens(tokens, numTokens);

    return 0;
}
