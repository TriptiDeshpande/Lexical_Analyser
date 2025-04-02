#include "lexer.h"

//Ensure correct usage of the program
int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <source_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    initLexer(argv[1]); //Initialize the lexer source file

    //Error checking to check whether file is successfully opened or not. 
    if (!file) {
        fprintf(stderr, "Error: Could not open file %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    //Process tokens until End of File (EOF) is reached
    Token token;
    do {
        token = getNextToken();
        switch (token.type) {
        case TOKEN_IDENTIFIER:
            printf("%s : IDENTIFIER\n", token.value);
            break;
        case TOKEN_KEYWORD:
            printf("%s : KEYWORD\n", token.value);
            break;
        case TOKEN_FLOAT_CONSTANT:
            printf("%s : FLOAT CONSTANT\n", token.value);
            break;
        case TOKEN_INTEGER_CONSTANT:
            printf("%s : INTEGER CONSTANT\n", token.value);
            break;
        case TOKEN_CHARACTER:
            printf("%s : CHARACTER\n", token.value);
            break;
        case TOKEN_STRING_LITERAL:
            printf("\"%s\" : STRING LITERAL\n", token.value);
            break;
        case TOKEN_ARITHMETIC_OPERATOR:
            printf("%s : ARTHIMETIC OPERATOR\n", token.value);
            break;
        case TOKEN_ASSIGNMENT_OPERATOR:
            printf("%s : ASSIGNMENT_OPERATOR\n", token.value);
            break;
        case TOKEN_RELATIONAL_OPERATOR:
            printf("%s : RELATIONAL OEPRATOR\n", token.value);
            break;
        case TOKEN_LOGICAL_OPERATOR:
            printf("%s : LOGICAL OEPRATOR\n", token.value);
            break; 
        case TOKEN_BITWISE_OPERATOR:
            printf("%s : BITWISE OEPRATOR\n", token.value);
            break; 
        case TOKEN_UNARY_OPERATOR:
            printf("%s : UNARY OPERATOR\n", token.value);
            break;
        case TOKEN_TERNARY_OPERATOR:
            printf("%s : TERNARY OPERATOR\n", token.value);
            break;
        case TOKEN_SPECIAL_CHARACTER:
            printf("%s : DELIMITER\n", token.value);
            break;
        case TOKEN_EOF:
            printf("End of file reached.\n");
            break;
        case TOKEN_ERROR:  // Handle TOKEN_ERROR explicitly
                fprintf(stderr, "Error: Unknown token: %s\n", token.value);
                return EXIT_FAILURE; 
        }
    } while (token.type != TOKEN_EOF);

 // Close the file after processing
    fclose(file);
    return EXIT_SUCCESS;
}
