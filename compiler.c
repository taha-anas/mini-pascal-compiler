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

    // add ID TO IDF table
    T_TAB_IDF IDF;
    IDF.TIDF = TIDF;
    strcpy(IDF.nom, symCour.nom);
    TAB_IDFS[NB_IDFS++] = IDF;

    //Add symbole to SYMB table
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
//    if(!isDeclared()) printErreur(ERR_IDF_INVAL);
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
// gener code
int getAdresse(){
    char* nom = symCour.nom;
    for (int i = 0; i < NB_IDFS; i++) {
        if (strcmp(TAB_SYM[i].nom, nom) == 0) {
            return TAB_SYM[i].adresse;
        }
    }
    printErreur(ERR_IDF_INVAL);
}

int getValue(){
    char* nom = symCour.nom;
    for (int i = 0; i < NB_IDFS; i++) {
        if (strcmp(TAB_SYM[i].nom, nom) == 0) {
            return TAB_SYM[i].valeur;
        }
    }
    printErreur(ERR_IDF_INVAL);
}

void printPCODE(){
    for (int i=0; i<=PC ; i++){
        printf("%d: %s %d\n",i ,mneSTR[PCODE[i].mne], PCODE[i].suite);
    }
}


void savePCODE(){
    for (int i=0; i<=PC ; i++){
        saveInstToFile(PCODE[i], i);
    }
    fflush(OUTPUT);
}

void saveInstToFile(Instruction INST, int i)
{
    switch( INST.mne){
        case LDA:
            fprintf(OUTPUT, "%d: %s \t %d \n",i, "LDA", INST.suite); break;
        case LDI:
            fprintf(OUTPUT, "%d: %s \t %d \n",i, "LDI", INST.suite); break;
        case INT:
            fprintf(OUTPUT, "%d: %s \t %d \n",i, "INT", INST.suite); break;
        case BZE:
            fprintf(OUTPUT, "%d: %s \t %d \n",i, "BZE", INST.suite); break;
        case BRN:
            fprintf(OUTPUT, "%d: %s \t %d \n",i, "BRN", INST.suite); break;
        case LDV:
            fprintf(OUTPUT, "%d: %s \n",i, "LDV");
            break;
        case ADD:
            fprintf(OUTPUT, "%d: %s \n",i, "ADD");
            break;
        case SUB:
            fprintf(OUTPUT, "%d: %s \n",i, "SUB");
            break;
        case MUL:
            fprintf(OUTPUT, "%d: %s \n",i, "MUL");
            break;

        case DIV:
            fprintf(OUTPUT, "%d: %s \n",i, "DIV");
            break;
        case LEQ:
            fprintf(OUTPUT, "%d: %s \n",i, "LEQ");
            break;
        case GEQ:
            fprintf(OUTPUT, "%d: %s \n",i, "GEQ");
            break;
        case NEQ:
            fprintf(OUTPUT, "%d: %s \n",i, "NEQ");
            break;
        case LSS:
            fprintf(OUTPUT, "%d: %s \n",i, "LSS");
            break;
        case GTR:
            fprintf(OUTPUT, "%d: %s \n",i, "GTR");
            break;
        case HLT:
            fprintf(OUTPUT, "%d: %s \n",i, "HLT");
            break;
        case STO:
            fprintf(OUTPUT, "%d: %s \n",i, "STO");
            break;
        case INN:
            fprintf(OUTPUT, "%d: %s \n",i, "INN");
            break;
        case PRN:
            fprintf(OUTPUT, "%d: %s \n",i, "PRN");
            break;
        default: printErreur(ERR_INST_PCODE);
            break;
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
    symSuiv();

    testSymbole(PV_TOKEN, ERR_POINT_VIRG_MANQ);
    BLOCK();
    GENERER1 (HLT);
    testSymbole(PT_TOKEN, ERR_POINT_MANQ);

}

//BLOCK := CONSTS VARS INSTS
void BLOCK(){
    CONSTS();
    VARS();
    PCODE[0].mne=INT;
    PCODE[0].suite=OFFSET;
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
    isPrograID();
    IsIdAlreadyUsed(TCONST);
    GENERER2(LDA, getAdresse());
    symSuiv();

    testSymbole(EG_TOKEN, ERR_MOT_CLE_INATT);

    if(symCour.code != NUM_TOKEN) printErreur(ERR_NUM_MANQ);
    GENERER2(LDI, symCour.valeur);
    GENERER1(STO);

    symSuiv();

    testSymbole(PV_TOKEN, ERR_POINT_VIRG_MANQ);

    // { ID = NUM ; }
    while (symCour.code == ID_TOKEN)
    {
        IsIdAlreadyUsed(TCONST);
        GENERER2(LDA, getAdresse());
        symSuiv();

        testSymbole(EG_TOKEN, ERR_MOT_CLE_INATT);

        if(symCour.code != NUM_TOKEN) printErreur(ERR_NUM_MANQ);
        GENERER2(LDI, symCour.valeur);
        GENERER1(STO);
        symSuiv();

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
    GENERER2(LDA, getAdresse());
    symSuiv();


    // { , ID }
    while (symCour.code == VIR_TOKEN)
    {
        symSuiv();
        IsIdAlreadyUsed(TVAR);
        GENERER2(LDA, getAdresse());
        symSuiv();


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
    isConst(); // check if id refer to const raise error
    isPrograID(); // check is id refer to program id raise error
    GENERER2(LDA,getAdresse());
    symSuiv(); // increment symbole
//    testSymbole(ID_TOKEN, ERR_MOT_CLE_INATT);
    testSymbole(AFF_TOKEN, ERR_AFF_MANQ);
    EXPR();
    GENERER1(STO);
}

// SI := if COND then INST
void SI(){
    testSymbole(IF_TOKEN, ERR_MOT_CLE_INATT);
    COND();
    //stocker indx de bze
    GENERER2(BZE, PC+1);
    int ind_bze = PC;

    testSymbole(THEN_TOKEN, ERR_MOT_CLE_INATT);
    INST();

    PCODE[ind_bze].suite=PC+1;
//    testSymbole(PV_TOKEN, ERR_POINT_VIRG_MANQ);
    if (symCour.code == ELSE_TOKEN){
        symSuiv();
        INST();
    }
}

// TANTQUE := while COND do INST
void TANTQUE(){
    testSymbole(WHILE_TOKEN, ERR_MOT_CLE_INATT);
    int LABEL_BRN= PC+1;
    COND();
    GENERER1(BZE);
    int INDICE_BZE=PC;
    testSymbole(DO_TOKEN, ERR_MOT_CLE_INATT);
    INST();
    GENERER2(BRN, LABEL_BRN);
    PCODE[INDICE_BZE].suite=PC+1;
}

// ECRIRE :=  write ( EXPR { , EXPR } )
void ECRIRE(){
    // write
    testSymbole(WRITE_TOKEN, ERR_MOT_CLE_INATT);
    // (
    testSymbole(PO_TOKEN, ERR_PAR_OUV_MANQ);
    // EXPR
    EXPR();
    GENERER1(PRN);
    // { , EXPR }
    while (symCour.code == VIR_TOKEN){
        symSuiv();
        EXPR();
        GENERER1(PRN);
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
    isConst();
    isPrograID();
    GENERER2(LDA, getAdresse());
    GENERER1(INN);

    symSuiv();

    // { , ID }
    while (symCour.code == VIR_TOKEN){
        symSuiv();

        if(symCour.code != ID_TOKEN) printErreur(ERR_MOT_CLE_INATT);
        isConst();
        isPrograID();
        GENERER2(LDA, getAdresse());
        GENERER1(INN);
    }
    // )
    testSymbole(PF_TOKEN, ERR_PAR_FER_MANQ);

}

// COND := EXPR [= | <> | < | > | <= | >=] EXPR
void COND(){
    EXPR();
    RELOP();
    EXPR();
    GENERER1(CO);
}

// RELOP := = | <> | < | > | <= | >=
void RELOP()
{
    switch (symCour.code)
    {
        case EG_TOKEN:
            CO=EQL;
            symSuiv();
            break;
        case DIFF_TOKEN:
            CO=NEQ;
            symSuiv();
            break;
        case SUPEG_TOKEN:
            CO=GEQ;
            symSuiv();
            break;
        case SUP_TOKEN:
            CO=GTR;
            symSuiv();
            break;
        case INF_TOKEN:
            CO=LSS;
            symSuiv();
            break;
        case INFEG_TOKEN:
            CO=LEQ;
            symSuiv();
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
        GENERER1(OP);
    }
}

// ADDOP := +|-
void ADDOP(){
    switch (symCour.code){
        case PLUS_TOKEN:
            OP=ADD;
            symSuiv();
            break;
        case MOINS_TOKEN:
            OP=SUB;
            symSuiv();
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
        GENERER1(OP);
    }
}

// FACT := ID | NUM | ( EXPR )
void FACT(){
    switch (symCour.code)
    {
        case ID_TOKEN:
            isPrograID();
            GENERER2(LDA, getAdresse());
            GENERER1(LDV);
            symSuiv();
            break;
        case NUM_TOKEN:
//            if(symCour.code != NUM_TOKEN) printErreur(ERR_NUM_MANQ);
//            GENERER2(LDI, symCour.valeur);
//            symSuiv();
            GENERER2(LDI, symCour.valeur);
            symSuiv();
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
            OP=MUL;
            symSuiv();
            break;
        case DIV_TOKEN:
            OP=DIV;
            symSuiv();
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

// REPETER ::= Repeat INST until COND
/*
REPEAT_TOKEN,UNTIL_TOKEN,FOR_TOKEN,ELSE_TOKEN,CASE_TOKEN,OF_TOKEN*/
void REPETER(){
    testSymbole(REPEAT_TOKEN, ERR_MOT_CLE_INATT);
    int LABEL_REPEAT = PC+1;
    printf("%d \n",PC+1);
    INST();

    while (symCour.code == PV_TOKEN ){
        symSuiv();
        INST();
    }

    testSymbole(UNTIL_TOKEN, ERR_MOT_CLE_INATT);
    COND();
    GENERER2(BZE,LABEL_REPEAT);
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
    fichier = fopen("test1", "r");

    if (fichier == NULL)
    {
        perror("printErreur lors de l'ouverture du fichier");
        return 1;
    }

    // read first char;
    lireCar();

    // detect first symbol;
    symSuiv();
    // call program function
    PROGRAM();

    //if you are here then the syntax is correct
    if (symCour.code == EOF_TOKEN) {
        printf("BRAVO: le programme est correcte!!! \n");
    }
    else {
        printf("PAS BRAVO: fin de programme erronée!!!! \n");
    }
//    printPCODE();


    OUTPUT = fopen("output", "w+");
    if (OUTPUT == NULL) {
        perror("Error opening output");
        fclose(OUTPUT); // Close the first file if the second fails to open
        return 1;
    }
    savePCODE();

    fclose(OUTPUT);

    fclose(fichier);
    return 0;
}