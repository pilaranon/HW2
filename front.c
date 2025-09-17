/******************************************************************
 * Program: Lexical Analyzer for Arithmetic Expressions
 * PURPOSE:
 *   Scan an input expression and break it into tokens (identifiers,
 *   integers, operators, parentheses).  Based on Sebesta Ch.4.2,
 *   with MOD (%) support.
 * IMPLEMENTED BY: Nathan Malaluan
 * COURSE: CS 351
 * INSTRUCTOR: Prof. Shaun-inn Wu
 * DATE: 09/17/2025
 ******************************************************************/

#include <stdio.h>
#include <ctype.h>
#include "front.h"

/* -------- Global variables -------- */
int charClass;         /* letter / digit / unknown / EOF */
char lexeme[100];      /* buffer to hold current lexeme */
char nextChar;         /* current character from input */
int lexLen;            /* length of current lexeme */
int token, nextToken;  /* token codes */
FILE *in_fp;

/******************************************************************
 * FUNCTION: lookup
 * PURPOSE:  Map special characters (+ - * / % ( )) to token codes.
 ******************************************************************/
int lookup(char ch) {
    switch (ch) {
        case '(': addChar(); nextToken = LEFT_PAREN; break;
        case ')': addChar(); nextToken = RIGHT_PAREN; break;
        case '+': addChar(); nextToken = ADD_OP; break;
        case '-': addChar(); nextToken = SUB_OP; break;
        case '*': addChar(); nextToken = MULT_OP; break;
        case '/': addChar(); nextToken = DIV_OP; break;
        case '%': addChar(); nextToken = MOD_OP; break;
        default : addChar(); nextToken = EOF_TOKEN; break;
    }
    return nextToken;
}


/******************************************************************
 * FUNCTION: addChar
 * PURPOSE:  Append nextChar to lexeme if buffer limit not reached.
 ******************************************************************/
void addChar(void) {
    if (lexLen <= 98) {
        lexeme[lexLen++] = nextChar;
        lexeme[lexLen] = '\0';
    } else
        printf("Error: lexeme too long\n");
}
/******************************************************************
 * FUNCTION: getChar
 * PURPOSE:  Read next character from input file and classify it.
 ******************************************************************/
void getChar(void) {
    int c = getc(in_fp);
    if (c != EOF) {
        nextChar = (char)c;
        if (isalpha((unsigned char)nextChar)) charClass = LETTER;
        else if (isdigit((unsigned char)nextChar)) charClass = DIGIT;
        else charClass = UNKNOWN;
    } else {
        charClass = EOF_CHAR;
        nextChar = '\0';
    }
}

/******************************************************************
 * FUNCTION: getNonBlank
 * PURPOSE:  Skip whitespace characters in input.
 ******************************************************************/
void getNonBlank(void) {
    while (isspace((unsigned char)nextChar))
        getChar();
}

/******************************************************************
 * FUNCTION: lex
 * PURPOSE:  Main lexical analyzer; returns next token.
 ******************************************************************/
int lex(void) {
    lexLen = 0;
    getNonBlank();

    switch (charClass) {
        case LETTER: /* identifier */
            addChar(); getChar();
            while (charClass == LETTER || charClass == DIGIT) {
                addChar(); getChar();
            }
            nextToken = IDENT;
            break;

        case DIGIT:  /* integer literal */
            addChar(); getChar();
            while (charClass == DIGIT) { addChar(); getChar(); }
            nextToken = INT_LIT;
            break;

        case UNKNOWN: /* operator or paren */
            lookup(nextChar);
            getChar();
            break;

        case EOF_CHAR: /* end-of-file */
            nextToken = EOF_TOKEN;
            sprintf(lexeme, "EOF");
            break;
    }
    printf("Next token is: %d, Next lexeme is %s\n", nextToken, lexeme);
    return nextToken;
}
