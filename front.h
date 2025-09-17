/******************************************************************/
/* PURPOSE: Header file for lexical analyzer (front.c).           */
/*          Provides token definitions, character classes,        */
/*          and function prototypes for use in parser.c.          */
/* IMPLEMENTED BY: Nathan Malaluan                                */
/* COURSE: CS 351                                                 */
/* INSTRUCTOR: Prof. Shaun-inn Wu                                 */
/* DATE: 09/17/2025                                               */
/******************************************************************/

/* front.h — token codes and lexer prototypes */

#ifndef FRONT_H
#define FRONT_H

#include <stdio.h>

/* Char classes */
#define LETTER   0
#define DIGIT    1
#define UNKNOWN 99
#define EOF_CHAR -1

/* Token codes */
#define INT_LIT      10
#define IDENT        11
#define ADD_OP       21
#define SUB_OP       22
#define MULT_OP      23
#define DIV_OP       24
#define LEFT_PAREN   25
#define RIGHT_PAREN  26
#define MOD_OP       27
#define EOF_TOKEN   -1

/* Globals */
extern int  charClass;
extern char lexeme[];
extern char nextChar;
extern int  lexLen;
extern int  token;
extern int  nextToken;
extern FILE *in_fp;

/* Functions */
void addChar(void);
void getChar(void);
void getNonBlank(void);
int  lookup(char ch);
int  lex(void);

#endif
