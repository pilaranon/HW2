/******************************************************************
 * PURPOSE: Implementation of the lexical analyzer for arithmetic
 *          expressions, based on Sebesta Ch.4.2, extended with
 *          the MOD (%) operator.
 * IMPLEMENTED BY: Nathan Malaluan                                *
 * COURSE: CS 351                                                 *
 * INSTRUCTOR: Prof. Shaun-inn Wu                                 *
 * DATE: 09/17/2025  
 ******************************************************************/

#include <stdio.h>
#include <ctype.h>
#include "front.h"

char lexeme[100];
int  charClass;
char nextChar;
int  lexLen;
int  token;
int  nextToken;
FILE *in_fp;

/******************************************************************
 * FUNCTION: addChar
 * PURPOSE:  Append nextChar to lexeme if buffer limit not reached.
 * INPUT:    nextChar (global)
 * OUTPUT:   Updates lexeme[] and lexLen.
 ******************************************************************/
void addChar(void) {
    if (lexLen < 98) {
        lexeme[lexLen++] = nextChar;
        lexeme[lexLen] = '\0';
    }
}

/******************************************************************
 * FUNCTION: getChar
 * PURPOSE:  Read next character from input file and classify it.
 * OUTPUT:   Sets nextChar and charClass.
 ******************************************************************/
void getChar(void) {
    int c = fgetc(in_fp);
    if (c == EOF) { charClass = EOF_CHAR; nextChar = '\0'; }
    else {
        nextChar = (char)c;
        if (isalpha((unsigned char)nextChar)) charClass = LETTER;
        else if (isdigit((unsigned char)nextChar)) charClass = DIGIT;
        else charClass = UNKNOWN;
    }
}

void getNonBlank(void) {
    while (isspace((unsigned char)nextChar))
        getChar();
}

/******************************************************************
 * FUNCTION: lookup
 * PURPOSE:  Map special characters (+ - * / % () ) to token codes.
 * ALGORITHM: switch-case table; returns token code.
 ******************************************************************/
int lookup(char ch) {
    switch (ch) {
        case '(' : addChar(); nextToken = LEFT_PAREN; break;
        case ')' : addChar(); nextToken = RIGHT_PAREN; break;
        case '+' : addChar(); nextToken = ADD_OP; break;
        case '-' : addChar(); nextToken = SUB_OP; break;
        case '*' : addChar(); nextToken = MULT_OP; break;
        case '/' : addChar(); nextToken = DIV_OP; break;
        case '%' : addChar(); nextToken = MOD_OP; break;
        default  : addChar(); nextToken = EOF_TOKEN; break;
    }
    return nextToken;
}

/******************************************************************
 * FUNCTION: lex
 * PURPOSE:  Main lexical analyzer; returns next token.
 * ALGORITHM: Skips blanks, distinguishes identifiers, numbers,
 *            or single-char operators, including %.
 ******************************************************************/
int lex(void) {
    lexLen = 0;
    lexeme[0] = '\0';
    getNonBlank();

    if (charClass == LETTER) {
        addChar(); getChar();
        while (charClass == LETTER || charClass == DIGIT) {
            addChar(); getChar();
        }
        nextToken = IDENT;
    }
    else if (charClass == DIGIT) {
        /* Collect full integer constant */
        addChar(); getChar();
        while (charClass == DIGIT) { addChar(); getChar(); }
        nextToken = INT_LIT;
    }
    else if (charClass == UNKNOWN) {
        lookup(nextChar);
        getChar();
    }
    else if (charClass == EOF_CHAR) {
        nextToken = EOF_TOKEN;
        sprintf(lexeme, "EOF");
    }

    /* <<< print like textbook >>> */
    printf("Next token is: %d, Next lexeme is %s\n", nextToken, lexeme);

    return nextToken;
}
