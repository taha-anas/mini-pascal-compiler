#ifndef COMPILA_X86_TRANSLATOR_H
#define COMPILA_X86_TRANSLATOR_H

#include "types.h"
#include "codegen.h"

typedef struct {
    char *code;
    int capacity;
    int length;
} AssemblyCode;

void initAssemblyCode(AssemblyCode *asmCode);
void appendAssembly(AssemblyCode *asmCode, const char *line);
void freeAssemblyCode(AssemblyCode *asmCode);
void translatePCodeToX86(Instruction *pcode, int pc_max, AssemblyCode *asmCode);
void writeAssemblyToFile(AssemblyCode *asmCode, const char *filename);

#endif // COMPILA_X86_TRANSLATOR_H