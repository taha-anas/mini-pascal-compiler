#include "../../include/semantic.h"

bool isDeclared() {
    char* nom = symCour.nom;
    for (int i = 0; i < NB_IDFS; i++) {
        if (strcmp(TAB_IDFS[i].nom, nom) == 0) {
            return true;
        }
    }
    return false;
}

void IsIdAlreadyUsed(TSYM TIDF){
    if(symCour.code != ID_TOKEN) printErreur(ERR_MOT_CLE_INATT);

    if(isDeclared()) printErreur(ERR_ID_USED);

    T_TAB_IDF IDF;
    IDF.TIDF = TIDF;
    strcpy(IDF.nom, symCour.nom);
    TAB_IDFS[NB_IDFS++] = IDF;

    TypeSymCour newSymb;
    newSymb.code=symCour.code;
    strcpy(newSymb.nom,symCour.nom);
    newSymb.valeur = symCour.valeur;
    newSymb.adresse = OFFSET;
    TAB_SYM[OFFSET++]=newSymb;
}

void isConst(){
    if(!isDeclared()) printErreur(ERR_IDF_INVAL);
    char* nom = symCour.nom;
    for (int i = 0; i < NB_IDFS; i++) {
        if (strcmp(TAB_IDFS[i].nom, nom) == 0 && TAB_IDFS[i].TIDF==TCONST) {
            printErreur(ERR_CONST_CANT_CHANGE);
        }
    }
}

void isPrograID(){
    char* nom = symCour.nom;
    for (int i = 0; i < NB_IDFS; i++) {
        if (strcmp(TAB_IDFS[i].nom, nom) == 0 && TAB_IDFS[i].TIDF==TPROG) {
            printErreur(ERR_PROGRAM_ID);
        }
    }
}

void ANALYSE_SEMENTIC(){
    isDeclared();
    isPrograID();
    isConst();
}

int getAdresse(){
    char* nom = symCour.nom;
    for (int i = 0; i < OFFSET; i++) {
        if (strcmp(TAB_SYM[i].nom, nom) == 0) {
            return TAB_SYM[i].adresse;
        }
    }
    printErreur(ERR_IDF_INVAL);
    return -1;
}

int getValue(){
    char* nom = symCour.nom;
    for (int i = 0; i < OFFSET; i++) {
        if (strcmp(TAB_SYM[i].nom, nom) == 0) {
            return TAB_SYM[i].valeur;
        }
    }
    printErreur(ERR_IDF_INVAL);
    return -1;
}