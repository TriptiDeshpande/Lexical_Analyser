#include "lexer.h"

FILE *file; // File pointer for input source
char currentChar; // Stores the current character being processed

// List of C language keywords
const char *keywords[] = {"auto", "break", "case", "char", "const", "continue", "default", "do",
                          "double", "else", "enum", "extern", "float", "for", "goto", "if",
                          "int", "long", "register", "return", "short", "signed", "sizeof", "static",
                          "struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while", NULL};

#define NUM_KEYWORDS (sizeof(keywords) / sizeof(keywords[0]) - 1) // Number of keywords

// Initialize the lexer by opening the file and reading the first character
void initLexer(const char *filename) {
    file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file\n");
        return;
    }
    currentChar = fgetc(file);
}

// Advances to the next character in the file
void advance() {
    if (currentChar == EOF) {
        printf("Reached EOF\n");
        return;
    }
    currentChar = fgetc(file);
    //printf("Advanced to: %c\n", currentChar);
}


// Checks if a given word is a keyword
bool isKeyword(const char *word) {
    for (int i = 0; keywords[i] != NULL; i++) {
        if (strcmp(word, keywords[i]) == 0) {
            return true;
        }
    }
    return false;
}

// Retrieves the next token from the input
Token getNextToken() {
    Token token;

    // Skip whitespace characters
    while (isspace(currentChar)) {
        advance();
    }

    // Identify keywords and identifiers
    if (isalpha(currentChar) || (currentChar == '_') ) { // If it starts with a letter
        int i = 0;
        while ((isalnum(currentChar) || (currentChar == '_')) && i < MAX_TOKEN_LENGTH - 1) { // Continue if alphanumeric
            token.value[i++] = currentChar;
            advance();
        }
        token.value[i] = '\0'; // Null-terminate string
        
        // Check if it's a keyword, otherwise classify as an identifier
        token.type = isKeyword(token.value) ? TOKEN_KEYWORD : TOKEN_IDENTIFIER;
        return token;
    }
    //Identify the type of constant (float or int)
    if (isdigit(currentChar)) {
        int i = 0;
        bool isFloat = false;
        while ((isdigit(currentChar) || currentChar == '.') && i < MAX_TOKEN_LENGTH - 1) {
            if(currentChar == '.'){
                if(isFloat) break; // only one dot allowed
                isFloat = true;
            }
            token.value[i++] = currentChar;
            advance();
        }
        // If next character is alphabetic (invalid identifier like "19x")
        if (isalpha(currentChar)) {
            while (isalnum(currentChar) && i < MAX_TOKEN_LENGTH - 1) { // Store full invalid token
                 token.value[i++] = currentChar;
                advance();
                }
            token.value[i] = '\0'; // Null-terminate

            token.type = TOKEN_ERROR;
            return token;
        }

        token.value[i] = '\0'; // Null-terminate 
        token.type = isFloat ? TOKEN_FLOAT_CONSTANT : TOKEN_INTEGER_CONSTANT;
        return token;
    } 
        

    // Identify Character Literals
    if (currentChar == '\'') {
        token.value[0] = currentChar;
        advance();
        token.value[1] = currentChar;
        advance();

        if (currentChar == '\'') {
            token.value[2] = currentChar;
            token.value[3] = '\0';
            advance();
            token.type = TOKEN_CHARACTER;
            return token;
        }
    }

    // Identify string literals
    if (currentChar == '"') {
        int i = 0;
        advance(); // Move past opening quote
        while (currentChar != '"' && currentChar != EOF && i < MAX_TOKEN_LENGTH - 1) {
            token.value[i++] = currentChar;
            advance();
        }
        token.value[i] = '\0';
        advance(); // Move past closing quote
        token.type = TOKEN_STRING_LITERAL;
        return token;
    }

    // Identify Logical Operators (&&, ||, !)
    if (currentChar == '&' || currentChar == '|') {
        token.value[0] = currentChar;
        advance();
        if (currentChar == token.value[0]) {  // Detect '&&' or '||'
            token.value[1] = currentChar;
            token.value[2] = '\0';
            token.type = TOKEN_LOGICAL_OPERATOR;
            advance();
        } else {
            token.value[1] = '\0';
            token.type = TOKEN_BITWISE_OPERATOR;  // Single & or | is bitwise
        }
        return token;
    }
    if (currentChar == '!') {  // Single '!' is logical NOT
        token.value[0] = currentChar;
        advance();
        if (currentChar == '=') {  // Detect '!='
            token.value[1] = currentChar;
            token.value[2] = '\0';
            token.type = TOKEN_RELATIONAL_OPERATOR;
            advance();
        } else {
            token.value[1] = '\0';
            token.type = TOKEN_LOGICAL_OPERATOR; // '!' alone
        }
        return token;
    }
    

    // Identify Bitwise Operators (&, |, <<, >>, ~, ^) and Relational Operators (<, >, <=, >=)
    if (currentChar == '~' || currentChar == '^') {
        token.value[0] = currentChar;
        token.value[1] = '\0';
        token.type = TOKEN_BITWISE_OPERATOR;
        advance();
        return token;
    }
    if (currentChar == '<' || currentChar == '>') {  // Check for << and >>
        token.value[0] = currentChar;
        advance();
        if (currentChar == token.value[0]) {  // Detect << or >>
            token.value[1] = currentChar;
            token.value[2] = '\0';
            token.type = TOKEN_BITWISE_OPERATOR;
            advance();
            return token;
        }else if (currentChar == '=') {  // Detect <= or >= (relational operators)
            token.value[1] = currentChar;
            token.value[2] = '\0';
            token.type = TOKEN_RELATIONAL_OPERATOR;
            advance();
            return token;
        }else {
            token.value[1] = '\0';
            token.type = TOKEN_RELATIONAL_OPERATOR;  // Single < or > is relational
            return token;
        }
        
    }

    // Identify Assignment and Arithmetic Operators
    // Assignment Operators (=, +=, -=, *=, /=, %=)
    if (currentChar == '*' || currentChar == '/' || currentChar == '%' || currentChar == '=' ) {  // Check for arithmetic operators
        token.value[0] = currentChar;  // Store first character
        advance();  // Move to next character

        // If second character is '=', it's an assignment operator like +=, -= .. etc

        if (currentChar == '=' && token.value[0] != '=') {  
            token.value[1] = currentChar;
            token.value[2] = '\0';
            token.type = TOKEN_ASSIGNMENT_OPERATOR;  
            advance();  
        } else if(currentChar == '=' && token.value[0] == '=' ) { 
                token.value[1] = currentChar;
                token.value[2] = '\0';
                token.type = TOKEN_RELATIONAL_OPERATOR;  
                advance();  
        }else if(currentChar == '*' || currentChar == '/' || currentChar == '%'){ 
            token.value[1] = '\0';
            token.type = TOKEN_ARITHMETIC_OPERATOR;
        }else {
            token.value[1] = '\0';
            token.type = TOKEN_ASSIGNMENT_OPERATOR;
        }
            
        return token;
    }

    // Unary Operators (++, --)
    if (currentChar == '+' || currentChar == '-') {
        token.value[0] = currentChar;
        advance();
        if (currentChar == token.value[0]) {  // Detect '++' or '--'
            token.value[1] = currentChar;
            token.value[2] = '\0';
            token.type = TOKEN_UNARY_OPERATOR;
            advance();
        } else if(currentChar == '=') {  
            token.value[1] = currentChar;
            token.value[2] = '\0';
            token.type = TOKEN_ASSIGNMENT_OPERATOR;  
            advance(); 
        }else{
            token.value[1] = '\0';
            token.type = TOKEN_ARITHMETIC_OPERATOR;  // + or - alone is arithmetic
        }
        return token;
    }

    // Ternary Operator (?:)
    if (currentChar == '?') {
        token.value[0] = currentChar;
        advance();
        if (currentChar == ':') {  // Detect '?:'
            token.value[1] = currentChar;
            token.value[2] = '\0';
            token.type = TOKEN_TERNARY_OPERATOR;
            advance();
        } else {
            token.value[1] = '\0';
            token.type = TOKEN_TERNARY_OPERATOR;  // '?' alone
        }
        return token;
    }


    // Identify punctuation symbols
    if (strchr("(){}[];,", currentChar)) {
        token.value[0] = currentChar;
        token.value[1] = '\0';
        token.type = TOKEN_SPECIAL_CHARACTER;
        advance();
        return token;
    }


    // Handle End-of-File (EOF)
    if (currentChar == EOF) {
        token.type = TOKEN_EOF;
        strcpy(token.value, "EOF");
        return token;
    }

    // If no valid token is found, mark as an error
    token.type = TOKEN_ERROR;
    token.value[0] = currentChar;  // Store the invalid character
    token.value[1] = '\0';  // Null-terminate
    return token; //exit(EXIT_FAILURE);  // Immediately stop execution;
}

