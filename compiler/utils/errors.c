#include "errors.h"
#include <stdio.h>

const char *MES_ERR[] = {
    [ERR_CAR_INC] = "Caractère inconnu",
    [ERR_FICH_VID] = "Fichier vide",
    [ERR_IDF_LONG] = "Identificateur trop long",
    [ERR_IDF_INVAL] = "Identificateur non declarer",
    [ERR_SYM_INCONNU] = "Symbole inconnu",
    [ERR_CONST_INVAL] = "Constante invalide",

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
    [ERR_PROGRAM_ID] = "ID du programme ne peut pas être utilisée.",

    [ERR_PC_FULL] = "Program counter full",
    [ERR_INST_PCODE] = "Invalid pcode instruction"
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

void printErreur(CodeErreur codeERR) {
    printf("ERREUR: %s\n", MES_ERR[codeERR]);
}