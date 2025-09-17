/******************************************************************
 * PROGRAM: Recursive-descent parser for arithmetic expressions
 * PURPOSE: Parse <expr> -> <term> {(+|-)<term>}
 *          <term> -> <factor> {(*|/|%)<factor>}
 *          <factor> -> id | int_constant | ( <expr> )
 * IMPLEMENTED BY: Nathan Malaluan                                *
 * COURSE: CS 351                                                 *
 * INSTRUCTOR: Prof. Shaun-inn Wu                                 *
 * DATE: 09/17/2025  
 ******************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "front.h"

/* --- Forward declarations --- */
void expr(void);
void term(void);
void factor(void);

/******************************************************************
 * FUNCTION: error
 * PURPOSE:  Print a syntax error message and terminate.
 ******************************************************************/
static void error(const char *msg) {
    fprintf(stderr, "Syntax error: %s at '%s'\n", msg, lexeme);
    exit(1);
}
/******************************************************************
 * FUNCTION: expr
 * PURPOSE:  Parse <expr> -> <term> {(+|-) <term>}.
 ******************************************************************/
void expr(void) {
    printf("Enter <expr>\n");
    term();
    while (nextToken == ADD_OP || nextToken == SUB_OP) {
        lex();
        term();
    }
    printf("Exit <expr>\n");
}

/******************************************************************
 * FUNCTION: term
 * PURPOSE:  Parse <term> -> <factor> {(*|/|%) <factor>}.
 ******************************************************************/
void term(void) {
    printf("Enter <term>\n");
    factor();
    while (nextToken == MULT_OP ||
           nextToken == DIV_OP ||
           nextToken == MOD_OP) {
        lex();
        factor();
    }
    printf("Exit <term>\n");
}
/******************************************************************
 * FUNCTION: factor
 * PURPOSE:  Parse <factor> -> id | int_constant | ( <expr> ).
 ******************************************************************/
void factor(void) {
    printf("Enter <factor>\n");
    if (nextToken == IDENT || nextToken == INT_LIT) {
        lex();
    } else if (nextToken == LEFT_PAREN) {
        lex();
        expr();
        if (nextToken == RIGHT_PAREN) lex();
        else error("missing )");
    } else {
        error("unexpected token");
    }
    printf("Exit <factor>\n");
}

/******************************************************************
 * FUNCTION: main
 * PURPOSE:  Initialize lexer and run parser on input file.
 ******************************************************************/
int main(void) {
    in_fp = fopen("front.in", "r");
    if (!in_fp) { in_fp = stdin; fprintf(stderr,"Using stdin\n"); }

    getChar();
    lex();
    if (nextToken != EOF_TOKEN) {
        expr();
        while (nextToken != EOF_TOKEN) lex();
        printf("Parsing completed.\n");
    }
    if (in_fp != stdin) fclose(in_fp);
    return 0;
}
