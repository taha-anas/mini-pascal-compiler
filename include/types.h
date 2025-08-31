#ifndef COMPILA_TYPES_H
#define COMPILA_TYPES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

typedef enum
{
    ID_TOKEN,
    PROGRAM_TOKEN,
    CONST_TOKEN,
    VAR_TOKEN,
    BEGIN_TOKEN,
    END_TOKEN,
    IF_TOKEN,
    THEN_TOKEN,
    WHILE_TOKEN,
    DO_TOKEN,
    READ_TOKEN,
    WRITE_TOKEN,
    PV_TOKEN,
    PT_TOKEN,
    PLUS_TOKEN,
    MOINS_TOKEN,
    MULT_TOKEN,
    DIV_TOKEN,
    VIR_TOKEN,
    AFF_TOKEN,
    INF_TOKEN,
    INFEG_TOKEN,
    SUP_TOKEN,
    SUPEG_TOKEN,
    DIFF_TOKEN,
    PO_TOKEN,
    PF_TOKEN,
    FIN_TOKEN,
    NUM_TOKEN,
    ERREUR_TOKEN,
    EOF_TOKEN,
    EG_TOKEN,
    REPEAT_TOKEN,
    UNTIL_TOKEN,
    FOR_TOKEN,
    ELSE_TOKEN,
    CASE_TOKEN,
    OF_TOKEN,
    INTO_TOKEN,
    DOWNTO_TOKEN,
    DDOT_TOKEN
} CODE_LEX;

typedef struct
{
    CODE_LEX code;
    char nom[20];
    int valeur;
    int adresse;
} TypeSymCour;

typedef enum {
    TPROG,
    TCONST,
    TVAR
} TSYM;

typedef struct {
    char nom[20];
    TSYM TIDF;
} T_TAB_IDF;

typedef enum {
    ADD, SUB, MUL, DIV, EQL, NEQ, GTR,
    LSS, GEQ, LEQ, PRN, INN, INT, LDI, LDA, LDV,
    STO, BRN, BZE, HLT
} MNEMONIQUES;

typedef struct {
    MNEMONIQUES mne;
    int suite;
} Instruction;

extern const char *CODE_LEX_strings[];
extern const char *mneSTR[];

#define TAILLE_CODE 100
#define TAILLE_TAB_SYM 10

extern TypeSymCour symCour;
extern FILE *fichier;
extern char carCour;
extern int numLigne;
extern TypeSymCour TAB_SYM[];
extern int OFFSET;
extern Instruction PCODE[];
extern int PC;
extern int NB_IDFS;
extern T_TAB_IDF TAB_IDFS[];

#endif // COMPILA_TYPES_H