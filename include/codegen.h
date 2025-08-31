#ifndef COMPILA_CODEGEN_H
#define COMPILA_CODEGEN_H

#include "types.h"
#include "errors.h"

void GENERER1(MNEMONIQUES mne);
void GENERER2(MNEMONIQUES mne, int suite);
void printPCODE();
void savePCODE();
void saveInstToFile(Instruction INST, int i);

extern FILE *OUTPUT;

#endif // COMPILA_CODEGEN_H