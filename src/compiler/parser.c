#include "parser.h"




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