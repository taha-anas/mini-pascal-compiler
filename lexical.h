#ifndef COMPILA_LEXICAL_H
#define COMPILA_LEXICAL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef enum {
    ID_TOKEN, PROGRAM_TOKEN,
    CONST_TOKEN, VAR_TOKEN,
    BEGIN_TOKEN, END_TOKEN,
    IF_TOKEN, THEN_TOKEN,
    WHILE_TOKEN, DO_TOKEN,
    READ_TOKEN, WRITE_TOKEN,
    PV_TOKEN, PT_TOKEN,
    PLUS_TOKEN, MOINS_TOKEN,
    MULT_TOKEN, DIV_TOKEN,
    VIR_TOKEN, AFF_TOKEN,
    INF_TOKEN, INFEG_TOKEN,
    SUP_TOKEN, SUPEG_TOKEN,
    DIFF_TOKEN, PO_TOKEN,
    PF_TOKEN, FIN_TOKEN,
    NUM_TOKEN, ERREUR_TOKEN, EOF_TOKEN,EG_TOKEN
} Token;

typedef struct {
    Token token;
    char name[20];
} Symbol;

// Function prototypes
void read_char(void);
void read_string(void);
void read_number(void);
void next_symbol(void);
//char* codeToString(Symbol code);

// Global variable
extern FILE * file;
extern char current_char;
extern Symbol current_symbol;


#endif //COMPILA_LEXICAL_H
