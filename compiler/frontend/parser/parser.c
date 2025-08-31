#include "parser.h"
#include "semantic.h"
#include "codegen.h"

void testSymbole(CODE_LEX cl, CodeErreur erreur){
    if (symCour.code != cl){
        printErreur(erreur);
        return;
    }
    if(symCour.code == ID_TOKEN){
        if(!isDeclared()) printErreur(ERR_VAR_INDEF);
    };
    symSuiv();
}


void PROGRAM(){
    testSymbole(PROGRAM_TOKEN, ERR_MOT_CLE_INATT);
    IsIdAlreadyUsed(TPROG);
    symSuiv();

    testSymbole(PV_TOKEN, ERR_POINT_VIRG_MANQ);
    BLOCK();
    GENERER1 (HLT);
    testSymbole(PT_TOKEN, ERR_POINT_MANQ);
}

void BLOCK(){
    CONSTS();
    VARS();
    PCODE[0].mne=INT;
    PCODE[0].suite=OFFSET;
    INSTS();
}

void CONSTS(){
    if(symCour.code != CONST_TOKEN){
        return;
    }
    symSuiv();

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

void VARS(){
    if(symCour.code != VAR_TOKEN ) return;
    symSuiv();

    IsIdAlreadyUsed(TVAR);
    GENERER2(LDA, getAdresse());
    symSuiv();

    while (symCour.code == VIR_TOKEN)
    {
        symSuiv();
        IsIdAlreadyUsed(TVAR);
        GENERER2(LDA, getAdresse());
        symSuiv();
    }

    testSymbole(PV_TOKEN, ERR_POINT_VIRG_MANQ);
}

void INSTS(){
    testSymbole(BEGIN_TOKEN, ERR_BEGIN_MANQ);

    INST();

    while (symCour.code == PV_TOKEN){
        symSuiv();
        INST();
    }

    testSymbole(END_TOKEN, ERR_END_MANQ);
}

void INST(){
    switch (symCour.code){
        case BEGIN_TOKEN:
            INSTS();
            break;
        case ID_TOKEN:
            AFFEC();
            break;
        case IF_TOKEN:
            SI();
            break;
        case WHILE_TOKEN:
            TANTQUE();
            break;
        case WRITE_TOKEN:
            ECRIRE();
            break;
        case READ_TOKEN:
            LIRE();
            break;
        case REPEAT_TOKEN:
            REPETER();
            break;
        case FOR_TOKEN:
            POUR();
            break;
        case CASE_TOKEN:
            CAS();
            break;
        default:
            break;
    }
}

void AFFEC(){
    if(symCour.code != ID_TOKEN){
        printErreur(ERR_MOT_CLE_INATT);
    }
    isConst();
    isPrograID();
    GENERER2(LDA,getAdresse());
    symSuiv();
    testSymbole(AFF_TOKEN, ERR_AFF_MANQ);
    EXPR();
    GENERER1(STO);
}

void SI(){
    testSymbole(IF_TOKEN, ERR_MOT_CLE_INATT);
    COND();
    GENERER2(BZE, PC+1);
    int ind_bze = PC;

    testSymbole(THEN_TOKEN, ERR_MOT_CLE_INATT);
    INST();

    PCODE[ind_bze].suite=PC+1;
    if (symCour.code == ELSE_TOKEN){
        symSuiv();
        INST();
    }
}

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

void ECRIRE(){
    testSymbole(WRITE_TOKEN, ERR_MOT_CLE_INATT);
    testSymbole(PO_TOKEN, ERR_PAR_OUV_MANQ);
    EXPR();
    GENERER1(PRN);
    while (symCour.code == VIR_TOKEN){
        symSuiv();
        EXPR();
        GENERER1(PRN);
    }
    testSymbole(PF_TOKEN, ERR_PAR_FER_MANQ);
}

void LIRE(){
    testSymbole(READ_TOKEN, ERR_MOT_CLE_INATT);
    testSymbole(PO_TOKEN, ERR_PAR_OUV_MANQ);
    if(symCour.code != ID_TOKEN) printErreur(ERR_MOT_CLE_INATT);
    isConst();
    isPrograID();
    GENERER2(LDA, getAdresse());
    GENERER1(INN);

    symSuiv();

    while (symCour.code == VIR_TOKEN){
        symSuiv();

        if(symCour.code != ID_TOKEN) printErreur(ERR_MOT_CLE_INATT);
        isConst();
        isPrograID();
        GENERER2(LDA, getAdresse());
        GENERER1(INN);
    }
    testSymbole(PF_TOKEN, ERR_PAR_FER_MANQ);
}

void COND(){
    EXPR();
    RELOP();
    EXPR();
    GENERER1(CO);
}

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

void EXPR(){
    TERM();
    while (symCour.code == PLUS_TOKEN || symCour.code == MOINS_TOKEN){
        ADDOP();
        TERM();
        GENERER1(OP);
    }
}

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

void TERM(){
    FACT();

    while (symCour.code == MULT_TOKEN || symCour.code == DIV_TOKEN)
    {
        MULOP();
        FACT();
        GENERER1(OP);
    }
}

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

void REPETER(){
    testSymbole(REPEAT_TOKEN, ERR_MOT_CLE_INATT);
    int LABEL_REPEAT = PC+1;
    INST();

    while (symCour.code == PV_TOKEN ){
        symSuiv();
        INST();
    }

    testSymbole(UNTIL_TOKEN, ERR_MOT_CLE_INATT);
    COND();
    GENERER2(BZE,LABEL_REPEAT);
}

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