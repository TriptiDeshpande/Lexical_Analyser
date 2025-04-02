# Lexical Analyzer for C

## Overview
This project implements a **Lexical Analyzer (Lexer) for C** to process source code and identify tokens, keywords, identifiers, operators, and other lexical components. The analyzer reads a C program, tokenizes it, and categorizes each token based on lexical rules.

## Features
- **Tokenization**: Identifies keywords, identifiers, constants, operators, string literals, and special characters.
- **Lexical Analysis**: Analyzes input source code and categorizes tokens.
- **Error Handling**: Detects invalid tokens and reports errors.
- **Efficient Processing**: Uses state-based parsing for efficient analysis.

## How It Works
1. The input C source code is read character by character.
2. Tokens are identified based on predefined lexical rules.
3. The analyzer categorizes tokens into keywords, identifiers, operators, numbers, and symbols.
4. Errors such as invalid tokens are flagged.


### Input Example (`input.c`)
```c
int main() {
    int a = 10;
    float b = 20.5;
    if (a < b) {
        printf("Hello, World!\n");
    }
    return 0;
}
```

### Output Example
```sh
int : KEYWORD
main : IDENTIFIER
( : DELIMITER
) : DELIMITER
{ : DELIMITER
int : KEYWORD
a : IDENTIFIER
= : ASSIGNMENT_OPERATOR
10 : INTEGER CONSTANT
; : DELIMITER
float : KEYWORD
b : IDENTIFIER
= : ASSIGNMENT_OPERATOR
20.5 : FLOAT CONSTANT
; : DELIMITER
if : KEYWORD
( : DELIMITER
a : IDENTIFIER
< : RELATIONAL OEPRATOR
b : IDENTIFIER
) : DELIMITER
{ : DELIMITER
printf : IDENTIFIER
( : DELIMITER
"Hello, World!\n" : STRING LITERAL
) : DELIMITER
; : DELIMITER
} : DELIMITER
return : KEYWORD
0 : INTEGER CONSTANT
; : DELIMITER
} : DELIMITER
...
```

## Project Files Structure
```
├── main.c          # Main program for the lexical analysis
├── lexer.c         # C program implementing the tokenisation of the input data
├── lexer.h         # Header file for lexical analysis functions
├── README.md       # Project documentation
```

