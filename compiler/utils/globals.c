#include "types.h"

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

const char* mneSTR[] = {
    "ADD", "SUB", "MUL", "DIV", "EQL", "NEQ", "GTR",
    "LSS", "GEQ", "LEQ", "PRN", "INN", "INT", "LDI", "LDA", "LDV",
    "STO", "BRN", "BZE", "HLT"
};

TypeSymCour symCour;
FILE *fichier;
char carCour;
int numLigne = 1;
TypeSymCour TAB_SYM[TAILLE_TAB_SYM];
int OFFSET = 0;
Instruction PCODE[TAILLE_CODE];
int PC = 0;
int NB_IDFS = 0;
T_TAB_IDF TAB_IDFS[10];
MNEMONIQUES OP;
MNEMONIQUES CO;