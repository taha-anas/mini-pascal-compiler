#include "../../include/codegen.h"

FILE *OUTPUT;

void GENERER1(MNEMONIQUES mne){
    if(PC == TAILLE_CODE) printErreur(ERR_PC_FULL);
    PC++;
    PCODE[PC]= (Instruction){mne, 0};
}

void GENERER2(MNEMONIQUES mne, int suite){
    if(PC == TAILLE_CODE) printErreur(ERR_PC_FULL);
    PC++;
    PCODE[PC]= (Instruction){mne,suite};
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
        case EQL:
            fprintf(OUTPUT, "%d: %s \n",i, "EQL");
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
        default: 
            printErreur(ERR_INST_PCODE);
            break;
    }
}