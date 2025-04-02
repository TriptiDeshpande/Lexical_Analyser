#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define MAX_TOKEN_LENGTH 100



// Token types
typedef enum {
    TOKEN_IDENTIFIER,
    TOKEN_KEYWORD,
    TOKEN_FLOAT_CONSTANT,
    TOKEN_INTEGER_CONSTANT,
    TOKEN_CHARACTER,
    TOKEN_STRING_LITERAL,
    TOKEN_ARITHMETIC_OPERATOR,
    TOKEN_ASSIGNMENT_OPERATOR,
    TOKEN_RELATIONAL_OPERATOR,
    TOKEN_LOGICAL_OPERATOR,
    TOKEN_BITWISE_OPERATOR,
    TOKEN_TERNARY_OPERATOR,
    TOKEN_UNARY_OPERATOR,   
    TOKEN_SPECIAL_CHARACTER,
    TOKEN_EOF,
    TOKEN_ERROR,
} TokenType;

// Token structure
typedef struct {
    TokenType type;
    char value[MAX_TOKEN_LENGTH];
} Token;

extern FILE *file;  // Declare file as external

// Function prototypes
void initLexer(const char *filename);
void advance();
Token getNextToken();
bool isKeyword(const char *word);

#endif // LEXER_H
