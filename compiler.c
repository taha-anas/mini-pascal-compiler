#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "compiler.h"

/*
    we have already declare some global variables in the header file:

        TypeSymCour symCour;
        FILE *fichier;
        char carCour;

    as well as two string arrays to store enums string value
*/

/* ---------------definition des fonctions helper--------------------*/
void lireCar()
{
    carCour = fgetc(fichier);
    if(carCour == '\n') numLigne++;
}

void symSuiv()
{
    while (carCour == ' ' || carCour == '\n' || carCour == '\t')
    {
        lireCar();
    }
    if (isalpha(carCour))
    {
        lireMot();
    }
    else if (isdigit(carCour))
    {
        lireNombre();
    }
    else
    {
        switch (carCour)
        {
            case ';':
                symCour.code = PV_TOKEN;
                strcpy(symCour.nom , ";");
                lireCar();
                break;

            case '+':
                symCour.code = PLUS_TOKEN;
                strcpy(symCour.nom , "+");
                lireCar();
                break;

            case '-':
                symCour.code = MOINS_TOKEN;
                strcpy(symCour.nom , "-");
                lireCar();
                break;

            case '*':
                symCour.code = MULT_TOKEN;
                strcpy(symCour.nom , "*");
                lireCar();
                break;

            case '/':
                symCour.code = DIV_TOKEN;
                strcpy(symCour.nom , "/");
                lireCar();
                break;

            case ',':
                symCour.code = VIR_TOKEN;
                strcpy(symCour.nom , ",");
                lireCar();
                break;

            case ':':
                lireCar();
                switch (carCour) {
                    case '=':
                        symCour.code = AFF_TOKEN;
                        strcpy(symCour.nom, ":=");
                        lireCar();
                        break;
                    case ':':
                        symCour.code = DDOT_TOKEN;
                        strcpy(symCour.nom, "::");
                        lireCar();
                        break;
                    default:
                        // you may need to add some error here
                        break;
                }
                break;
            case '<':
                lireCar();
                if (carCour == '=')
                {
                    symCour.code = INFEG_TOKEN;
                    strcpy(symCour.nom, "<=");
                    lireCar();
                }
                else if (carCour == '>')
                {
                    symCour.code = DIFF_TOKEN;
                    strcpy(symCour.nom, "<>");
                    lireCar();
                }
                else
                {
                    symCour.code = INF_TOKEN;
                    strcpy(symCour.nom, "<");
                    lireCar();
                }
                break;

            case '>':
                lireCar();
                if (carCour == '=')
                {
                    symCour.code = SUPEG_TOKEN;
                    strcpy(symCour.nom, ">=");
                    lireCar();
                }
                else
                {
                    symCour.code = SUP_TOKEN;
                    strcpy(symCour.nom, ">");
                    lireCar();
                }
                break;

            case '(':
                symCour.code = PO_TOKEN;
                strcpy(symCour.nom, "(");
                lireCar();
                break;
            case '=':
                symCour.code = EG_TOKEN;
                strcpy(symCour.nom, "=");
                lireCar();
                break;

            case ')':
                symCour.code = PF_TOKEN;
                strcpy(symCour.nom, ")");
                lireCar();
                break;

            case '.':
                symCour.code = PT_TOKEN;
                strcpy(symCour.nom, ".");
                lireCar();
                break;

            case EOF:
                symCour.code = EOF_TOKEN;
                strcpy(symCour.nom, "EOF");
                break;

            default:
                symCour.code = ERREUR_TOKEN;
                strcpy(symCour.nom, "error");
                lireCar();
                break;
        }
    }

//    printf("token: %s, value: %s\n", CODE_LEX_strings[symCour.code] , symCour.nom);
}

void lireMot()
{
    char mot[20];
    int indice = 0;

    // Lecture du premier caractère (lettre)
    mot[indice++] = carCour;
    lireCar();

    // Lecture des caractères suivants (lettres ou chiffres)
    while (isalpha(carCour) || isdigit(carCour))
    {
        mot[indice++] = carCour;
        lireCar();
    }

    // Ajout du caractère de fin de chaîne
    mot[indice] = '\0';

    // Vérifier si le mot est un mot-clé
    if (strcmp(mot, "program") == 0)
    {
        symCour.code = PROGRAM_TOKEN;
    }
    else if (strcmp(mot, "const") == 0)
    {
        symCour.code = CONST_TOKEN;
    }
    else if (strcmp(mot, "var") == 0)
    {
        symCour.code = VAR_TOKEN;
    }
    else if (strcmp(mot, "begin") == 0)
    {
        symCour.code = BEGIN_TOKEN;
    }
    else if (strcmp(mot, "end") == 0)
    {
        symCour.code = END_TOKEN;
    }
    else if (strcmp(mot, "if") == 0)
    {
        symCour.code = IF_TOKEN;
    }
    else if (strcmp(mot, "then") == 0)
    {
        symCour.code = THEN_TOKEN;
    }
    else if (strcmp(mot, "while") == 0)
    {
        symCour.code = WHILE_TOKEN;
    }
    else if (strcmp(mot, "do") == 0)
    {
        symCour.code = DO_TOKEN;
    }
    else if (strcmp(mot, "read") == 0)
    {
        symCour.code = READ_TOKEN;
    }
    else if (strcmp(mot, "write") == 0)
    {
        symCour.code = WRITE_TOKEN;
    }
    else if (strcmp(mot, "else") == 0)
    {
        symCour.code = ELSE_TOKEN;
    }
    else if (strcmp(mot, "repeat") == 0)
    {
        symCour.code = REPEAT_TOKEN;
    }
    else if (strcmp(mot, "until") == 0)
    {
        symCour.code = UNTIL_TOKEN;
    }
    else if (strcmp(mot, "for") == 0)
    {
        symCour.code = FOR_TOKEN;
    }
    else if (strcmp(mot, "case") == 0)
    {
        symCour.code = CASE_TOKEN;
    }
    else if (strcmp(mot, "of") == 0)
    {
        symCour.code = OF_TOKEN;
    }
    else
    {
        // If it's not a keyword, it's an identifier
        symCour.code = ID_TOKEN;
    }

    // Stockage du mot dans le jeton
    strcpy(symCour.nom, mot);
}



void lireNombre(){
    char nombre[11];
    int indice = 0;

    // Lecture du premier chiffre
    nombre[indice++] = carCour;
    lireCar();

    // Lecture des chiffres suivants
    while (isdigit(carCour)){
        nombre[indice++] = carCour;
        lireCar();
    }

    // Ajout du caractère de fin de chaîne
    nombre[indice] = '\0';

    // Stockage du nombre dans le jeton
    symCour.code = NUM_TOKEN;
    // stocker la valeur
    symCour.valeur = atoi(nombre);
    strcpy(symCour.nom, nombre);
}



void testSymbole(CODE_LEX cl, CodeErreur erreur){
    if (symCour.code != cl){
        printErreur(erreur);
        return;
    }
    if(symCour.code == ID_TOKEN){
        if(!isDeclared(symCour.nom)) printErreur(ERR_VAR_INDEF);
    };
    symSuiv();
}



// fonction pour vérifier si une variable/constante existe déjà
bool isDeclared() {
    char* nom = symCour.nom;
    for (int i = 0; i < NB_IDFS; i++) {
        if (strcmp(TAB_IDFS[i].nom, nom) == 0) {
            return true;
        }
    }
    return false;
}

//fonction permet de verifier si symCour is token_id and not used yet
void IsIdAlreadyUsed(TSYM TIDF){
    // expect id_token
    if(symCour.code != ID_TOKEN) printErreur(ERR_MOT_CLE_INATT);

    // check if the id already declared
    if(isDeclared()) printErreur(ERR_ID_USED);

    // add symbole to symbole table
    T_TAB_IDF IDF;
    IDF.TIDF = TIDF;
    strcpy(IDF.nom, symCour.nom);
    TAB_IDFS[NB_IDFS++] = IDF;
    symSuiv();
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
    if(!isDeclared()) printErreur(ERR_IDF_INVAL);
    char* nom = symCour.nom;
    for (int i = 0; i < NB_IDFS; i++) {
        if (strcmp(TAB_IDFS[i].nom, nom) == 0 && TAB_IDFS[i].TIDF==TPROG) {
            printErreur(ERR_PROGRAM_ID);
        }
    }
}
void printErreur(CodeErreur codeERR){
    char* err_message = MES_ERR[codeERR];
    printf("\033[31m Erreur: ligne numéro %d \033[0m", numLigne);
    printf("\033[32m'%s'\033[0m",symCour.nom );
    printf("\033[31m, %s \033[0m \n",err_message);
    exit(EXIT_FAILURE);
}

/*--------------------definition des procedures de language---------------*/
// PROGRAM := program ID ; BLOCK .
void PROGRAM(){
    testSymbole(PROGRAM_TOKEN, ERR_MOT_CLE_INATT);
    IsIdAlreadyUsed(TPROG);
    testSymbole(PV_TOKEN, ERR_POINT_VIRG_MANQ);
    BLOCK();
    testSymbole(PT_TOKEN, ERR_POINT_MANQ);

}

//BLOCK := CONSTS VARS INSTS
void BLOCK(){
    CONSTS();
    VARS();
    INSTS();
}


//CONST := const ID = NUM ; { ID = NUM ; } | epsilon
void CONSTS(){
    // epsilon case
    if(symCour.code != CONST_TOKEN){
        return;
    }
    symSuiv();

    // expect id_token and check if it is already used
    IsIdAlreadyUsed(TCONST);
    testSymbole(EG_TOKEN, ERR_MOT_CLE_INATT);
    testSymbole(NUM_TOKEN, ERR_CONST_INVAL);
    testSymbole(PV_TOKEN, ERR_POINT_VIRG_MANQ);

    // { ID = NUM ; }
    while (symCour.code == ID_TOKEN)
    {
        IsIdAlreadyUsed(TCONST);
        testSymbole(EG_TOKEN, ERR_MOT_CLE_INATT);
        testSymbole(NUM_TOKEN, ERR_CONST_INVAL);
        testSymbole(PV_TOKEN, ERR_POINT_VIRG_MANQ);
    };
}

// VARS := var ID { , ID } ; | e
void VARS(){
    // epsilon
    if(symCour.code != VAR_TOKEN ) return;
    symSuiv();

    // var ID
    IsIdAlreadyUsed(TVAR);

    // { , ID }
    while (symCour.code == VIR_TOKEN)
    {
        symSuiv();
        IsIdAlreadyUsed(TVAR);

//        testSymbole(ID_TOKEN, ERR_MOT_CLE_INATT);
    }

    // ;
    testSymbole(PV_TOKEN, ERR_POINT_VIRG_MANQ);
}

//INSTS := begin INST { ; INST } end
void INSTS(){
    // begin
    testSymbole(BEGIN_TOKEN, ERR_BEGIN_MANQ);

    // INST
    INST();

    //{ ; INST }
    while (symCour.code == PV_TOKEN){
        symSuiv();
        INST();
    }

    // end
    testSymbole(END_TOKEN, ERR_END_MANQ);
}


//INSTS | AFFEC | SI | TANTQUE | ECRIRE | LIRE | e
void INST(){
    switch (symCour.code){
        // INSTS := begin ...
        case BEGIN_TOKEN:
            INSTS();
            break;
        // AFFEC := ID ...
        case ID_TOKEN:
            AFFEC();
            break;
        // SI := if ...
        case IF_TOKEN:
            SI();
            break;
        // TANQUE := while ...
        case WHILE_TOKEN:
            TANTQUE();
            break;
        // ECRIRE := write ...
        case WRITE_TOKEN:
            ECRIRE();
            break;
        // LIRE := read...
        case READ_TOKEN:
            LIRE();
            break;
        // REPETER := repeat ..
        case REPEAT_TOKEN:
            REPETER();
            break;
        // POUR := FOR ...
        case FOR_TOKEN:
            POUR();
            break;
        // CAS := case
        case CASE_TOKEN:
            CAS();
            break;
        // epsilon
        default:
            break;
    }
}


// AFFEC := ID := EXPR
void AFFEC(){
    if(symCour.code != ID_TOKEN){
        printErreur(ERR_MOT_CLE_INATT);
    }
    isConst();
    isPrograID();
    symSuiv();
//    testSymbole(ID_TOKEN, ERR_MOT_CLE_INATT);
    testSymbole(AFF_TOKEN, ERR_AFF_MANQ);
    EXPR();
}

// SI := if COND then INST
void SI(){
    testSymbole(IF_TOKEN, ERR_MOT_CLE_INATT);
    COND();
    testSymbole(THEN_TOKEN, ERR_MOT_CLE_INATT);
    INST();

    if (symCour.code == ELSE_TOKEN){
        INST();
    }
}

// TANTQUE := while COND do INST
void TANTQUE(){
    testSymbole(WHILE_TOKEN, ERR_MOT_CLE_INATT);
    COND();
    testSymbole(DO_TOKEN, ERR_MOT_CLE_INATT);
    INST();
}

// ECRIRE :=  write ( EXPR { , EXPR } )
void ECRIRE(){
    // write
    testSymbole(WRITE_TOKEN, ERR_MOT_CLE_INATT);
    // (
    testSymbole(PO_TOKEN, ERR_PAR_OUV_MANQ);
    // EXPR
    EXPR();
    // { , EXPR }
    while (symCour.code == VIR_TOKEN){
        symSuiv();
        EXPR();
    }
    // )
    testSymbole(PF_TOKEN, ERR_PAR_FER_MANQ);
}

// LIRE =: read ( ID { , ID } )
void LIRE(){
    // read
    testSymbole(READ_TOKEN, ERR_MOT_CLE_INATT);
    // (
    testSymbole(PO_TOKEN, ERR_PAR_OUV_MANQ);
    // ID
    if(symCour.code != ID_TOKEN) printErreur(ERR_MOT_CLE_INATT);
    isDeclared();
    isConst();
    isPrograID();
    symSuiv();

    // { , ID }
    while (symCour.code == VIR_TOKEN){
        symSuiv();
        testSymbole(ID_TOKEN, ERR_MOT_CLE_INATT);
    }
    // )
    testSymbole(PF_TOKEN, ERR_PAR_FER_MANQ);

}

// COND := EXPR [= | <> | < | > | <= | >=] EXPR
void COND(){
    EXPR();
    RELOP();
    EXPR();
}

// RELOP := = | <> | < | > | <= | >=
void RELOP()
{
    switch (symCour.code)
    {
        case EG_TOKEN:
            break;
        case DIFF_TOKEN:
            break;
        case SUPEG_TOKEN:
            break;
        case INF_TOKEN:
            break;
        case SUP_TOKEN:
            break;
        case INFEG_TOKEN:
            break;
        default:
            printErreur(ERR_OPERATOR_INCORRECT);
            break;
    }
}

//EXPR := TERM { ADDOP TERM }
void EXPR(){

    TERM();
    while (symCour.code == PLUS_TOKEN || symCour.code == MOINS_TOKEN){
        ADDOP();
        TERM();
    }
}

// ADDOP := +|-
void ADDOP(){
    switch (symCour.code){
        case PLUS_TOKEN:
            testSymbole(PLUS_TOKEN, ERR_PLUS_MANQ);
            break;
        case MOINS_TOKEN:
            testSymbole(MOINS_TOKEN, ERR_MOINS_MANQ);
            break;
        default:
            printErreur(ERR_OPERATOR_INCORRECT);
            break;
    }
}

// TERM := FACT { MULOP FACT }
void TERM(){
    FACT();

    while (symCour.code == MULT_TOKEN || symCour.code == DIV_TOKEN)
    {
        MULOP();
        FACT();
    }
}

// FACT := ID | NUM | ( EXPR )
void FACT(){
    switch (symCour.code)
    {
        case ID_TOKEN:
            isPrograID();
            testSymbole(ID_TOKEN, ERR_MOT_CLE_INATT);
            break;
        case NUM_TOKEN:
            testSymbole(NUM_TOKEN, ERR_NUM_MANQ);
            break;
        case PO_TOKEN:
            testSymbole(PO_TOKEN, ERR_PAR_OUV_MANQ);
            EXPR();
            testSymbole(PF_TOKEN, ERR_PAR_FER_MANQ);
            break;
        default:
            printErreur(ERR_STRUCT_INCORRECTE);
            break;
    }
}

// MULOP := * | /
void MULOP()
{
    switch (symCour.code)
    {
        case MULT_TOKEN:
            testSymbole(MULT_TOKEN, ERR_MULT_MANQ);
            break;
        case DIV_TOKEN:
            testSymbole(DIV_TOKEN, ERR_DIV_MANQ);
            break;
        default:
            printErreur(ERR_STRUCT_INCORRECTE);
            break;
    }
}
// POUR:= For ID=NUM [to | downto] NUM do INST
void POUR()
{
    testSymbole(FOR_TOKEN, ERR_MOT_CLE_INATT);
    testSymbole(ID_TOKEN, ERR_MOT_CLE_INATT);
    testSymbole(AFF_TOKEN, ERR_MOT_CLE_INATT);

    switch (symCour.code)
    {
        case DOWNTO_TOKEN:
            testSymbole(DOWNTO_TOKEN, ERR_MOT_CLE_INATT);
            break;
        case INTO_TOKEN:
            testSymbole(INTO_TOKEN, ERR_MOT_CLE_INATT);
            break;
        default:
            printErreur(ERR_STRUCT_INCORRECTE);
            break;
    }

    testSymbole(NUM_TOKEN, ERR_NUM_MANQ);
    testSymbole(DO_TOKEN, ERR_MOT_CLE_INATT);
    INST();

}

/*
REPEAT_TOKEN,UNTIL_TOKEN,FOR_TOKEN,ELSE_TOKEN,CASE_TOKEN,OF_TOKEN*/

// REPETER ::= Repeat INST until COND
void REPETER(){
    testSymbole(REPEAT_TOKEN, ERR_MOT_CLE_INATT);
    INST();
    testSymbole(UNTIL_TOKEN, ERR_MOT_CLE_INATT);
    COND();
}

// CAS ::= CASE ID OF NUM : INST { NUM: INST} [ELSE INST |e] END
void CAS()
{
    testSymbole(CASE_TOKEN, ERR_MOT_CLE_INATT);
    testSymbole(ID_TOKEN, ERR_MOT_CLE_INATT);
    testSymbole(OF_TOKEN, ERR_PAR_OUV_MANQ);
    testSymbole(NUM_TOKEN, ERR_NUM_MANQ);
    testSymbole(DDOT_TOKEN, ERR_DDOT_MANQ);
    INST();
    while (symCour.code == NUM_TOKEN)
    {
        symSuiv();
        testSymbole(DDOT_TOKEN, ERR_DDOT_MANQ);
        INST();
    }
    if (symCour.code == ELSE_TOKEN) {
        symSuiv();
        INST();
    }

    testSymbole(END_TOKEN, ERR_END_MANQ);
}



/*-------------------- Main function --------------------*/
int main()
{
    // open code file
    fichier = fopen("program.p", "r");
    if (fichier == NULL)
    {
        perror("printErreur lors de l'ouverture du fichier");
        return 1;
    }

//    initialiserErreurs(MES_ERR);

    // read first char;
    lireCar();

    // detect first symbol;
    symSuiv();
    // call program function
    PROGRAM();

    //if you are here then the syntax is correct
//    printf("Program execution completed.\n");

//    for (int i = 0; i < NB_IDFS; ++i) {
//        printf("name : %s \n", TAB_IDFS[i].nom);
//    }
    if (symCour.code == EOF_TOKEN) {
        printf("BRAVO: le programme est correcte!!!");
    }
    else {
        printf("PAS BRAVO: fin de programme erronée!!!!");
    }

    fclose(fichier);
    return 0;
}