#ifndef COMPILA_COMPILER_H
#define COMPILA_COMPILER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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
    EG_TOKEN,REPEAT_TOKEN,UNTIL_TOKEN,FOR_TOKEN,ELSE_TOKEN,CASE_TOKEN,OF_TOKEN,
    INTO_TOKEN,DOWNTO_TOKEN,
    DDOT_TOKEN
} CODE_LEX;



typedef struct
{
    CODE_LEX code;
    char nom[20];
    int valeur;
} TypeSymCour;

// define token string to print
const char *CODE_LEX_strings[] = {
        "ID_TOKEN","PROGRAM_TOKEN",
        "CONST_TOKEN","VAR_TOKEN",
        "BEGIN_TOKEN","END_TOKEN",
        "IF_TOKEN","THEN_TOKEN",
        "WHILE_TOKEN","DO_TOKEN",
        "READ_TOKEN","WRITE_TOKEN",
        "PV_TOKEN","PT_TOKEN",
        "PLUS_TOKEN","MOINS_TOKEN",
        "MULT_TOKEN","DIV_TOKEN",
        "VIR_TOKEN","AFF_TOKEN",
        "INF_TOKEN","INFEG_TOKEN",
        "SUP_TOKEN","SUPEG_TOKEN",
        "DIFF_TOKEN","PO_TOKEN",
        "PF_TOKEN","FIN_TOKEN",
        "NUM_TOKEN","ERREUR_TOKEN",
        "EOF_TOKEN","EG_TOKEN",
        "REPEAT_TOKEN","UNTIL_TOKEN",
        "FOR_TOKEN","ELSE_TOKEN",
        "CASE_TOKEN","OF_TOKEN",
        "INTO_TOKEN","DOWNTO_TOKEN",
        "DDOT_TOKEN"
};

const char *CODE_ERR_strings[] = {
        "ID_ERR","PROGRAM_ERR",
        "CONST_ERR","VAR_ERR",
        "BEGIN_ERR","END_ERR",
        "IF_ERR","THEN_ERR",
        "WHILE_ERR","DO_ERR",
        "READ_ERR","WRITE_ERR",
        "PV_ERR","PT_ERR",
        "PLUS_ERR","MOINS_ERR",
        "MULT_ERR","DIV_ERR",
        "VIR_ERR","AFF_ERR",
        "INF_ERR","INFEG_ERR",
        "SUP_ERR","SUPEG_ERR",
        "DIFF_ERR","PO_ERR",
        "PF_ERR","FIN_ERR",
        "NUM_ERR","ERREUR_ERR",
        "EOF_ERR","EG_ERR",
        "CONST_VAR_BEGIN_ERR","VAR_BEGIN_ERR",
        "REPEAT_ERR","UNTIL_ERR",
        "FOR_ERR","ELSE_ERR",
        "CASE_ERR","OF_ERR",
        "INTO_ERR","DOWNTO_ERR",
        "DDOT_ERR"
};


// ----------------------- DECLARATION DES CLASSES DES ERREURS --------------------------------

typedef enum {
    // CodeErreur lexicales
    ERR_CAR_INC,             // Caractère inconnu
    ERR_FICH_VID,            // Fichier vide
    ERR_IDF_LONG,            // Identificateur trop long
    ERR_IDF_INVAL,           // Identificateur invalide
    ERR_SYM_INCONNU,         // Symbole inconnu
    ERR_CONST_INVAL,         // Constante invalide

    // CodeErreur syntaxiques

    ERR_BEGIN_MANQ,          // BEGIN manquant
    ERR_END_MANQ,            // END manquant
    ERR_POINT_VIRG_MANQ,     // Point-virgule manquant
    ERR_POINT_MANQ,          // Point manquant
    ERR_EG_MANQ,             // EGALE MANQUANT
    ERR_PAR_OUV_MANQ,        // Parenthèse manquante
    ERR_PAR_FER_MANQ,        // Parenthèse manquante
    ERR_PLUS_MANQ,
    ERR_MOINS_MANQ,
    ERR_MULT_MANQ,
    ERR_DIV_MANQ,
    ERR_DDOT_MANQ,
    ERR_AFF_MANQ,
    ERR_MOT_CLE_INATT,       // Mot-clé inattendu
    ERR_NUM_MANQ,            // Number manquant
    ERR_STRUCT_INCORRECTE,   // Structure incorrecte
    ERR_FIN_FICHIER_INATT,   // Fin de fichier inattendue
    ERR_OPERATOR_INCORRECT,

    // CodeErreur sémantiques
    ERR_TYPE_INCOMPATIBLE,   // Types incompatibles
    ERR_VAR_INDEF,           // Variable indéfinie
    ERR_NOMBRE_PARAM_INVAL,  // Nombre de paramètres invalide
    ERR_ID_USED,
    ERR_CONST_CANT_CHANGE,
    ERR_PROGRAM_ID

} CodeErreur;

// definition de la structure erreur
typedef struct {
    CodeErreur code;
    char message[40];
} ErreurType;

// creation d'un tableau d'erreur:
//ErreurType MES_ERR[];

const char *MES_ERR[] = {
        [ERR_CAR_INC] = "Caractère inconnu",
        [ERR_FICH_VID] = "Fichier vide",
        [ERR_IDF_LONG] = "Identificateur trop long",
        [ERR_IDF_INVAL] = "Identificateur invalide",
        [ERR_SYM_INCONNU] = "Symbole inconnu",
        [ERR_CONST_INVAL] = "Constante invalide",

        // ... et ainsi de suite pour chaque erreur

        [ERR_BEGIN_MANQ] = "Mot-clé 'BEGIN' manquant",
        [ERR_END_MANQ] = "Mot-clé 'END' manquant",
        [ERR_POINT_VIRG_MANQ] = "Point-virgule manquant",
        [ERR_POINT_MANQ] = "Point manquant",
        [ERR_EG_MANQ] = "Symbole ':=' manquant",
        [ERR_PAR_OUV_MANQ] = "Parenthèse ouvrante '(' manquante",
        [ERR_PAR_FER_MANQ] = "Parenthèse fermante ')' manquante",
        [ERR_PLUS_MANQ] = "Symbole '+' manquant",
        [ERR_MOINS_MANQ] = "Symbole '-' manquant",
        [ERR_MULT_MANQ] = "Symbole '*' manquant",
        [ERR_DIV_MANQ] = "Symbole '/' manquant",
        [ERR_DDOT_MANQ] = "Symbole ':' manquant",
        [ERR_AFF_MANQ] = "Symbole d'affectation ':=' manquant",
        [ERR_MOT_CLE_INATT] = "Mot-clé inattendu",
        [ERR_NUM_MANQ] = "Nombre manquant",
        [ERR_STRUCT_INCORRECTE] = "Structure incorrecte",
        [ERR_FIN_FICHIER_INATT] = "Fin de fichier inattendue",

        [ERR_TYPE_INCOMPATIBLE] = "Types incompatibles",
        [ERR_VAR_INDEF] = "Variable indéfinie",
        [ERR_NOMBRE_PARAM_INVAL] = "Nombre de paramètres invalide",
        [ERR_ID_USED] = "Identifacteur est utilisé",
        [ERR_CONST_CANT_CHANGE] = "varriable de type const ne peut pas être changée",
        [ERR_PROGRAM_ID] = "ID du programme ne peut pas être utilisée."
};

void printErreur(CodeErreur codeERR);


// ---------------------ANALYE SEMANTIC ---------------------
typedef enum {
    TPROG,
    TCONST,
    TVAR
} TSYM;

typedef struct {
    char nom[20];
    TSYM TIDF;
} T_TAB_IDF;

int NB_IDFS = 0;

T_TAB_IDF TAB_IDFS[10];

// ---------------------declaration des variable global------------------------------------------
TypeSymCour symCour;
FILE *fichier;
char carCour; // caractère courant
int numLigne=1; // num line

// declaration des fonction helper
void lireCar();
void symSuiv();
void lireMot();
void lireNombre();
void testSymbole(CODE_LEX cl, CodeErreur erreur);
bool isDeclared();

// declaration des procedure de language
void VARS();
void INSTS();
void INST();
void AFFEC();
void SI();
void TANTQUE();
void ECRIRE();
void LIRE();
void EXPR();
void TERM();
void FACT();
void MULOP();
void ADDOP();
void RELOP();
void COND();
void PROGRAM();
void BLOCK();
void CONSTS();
void CAS();
void POUR();
void REPETER();


#endif //COMPILA_COMPILER_H
