#include "x86_translator.h"
#include <stdlib.h>
#include <string.h>

void initAssemblyCode(AssemblyCode *asmCode) {
    asmCode->capacity = 1024;
    asmCode->code = malloc(asmCode->capacity);
    asmCode->length = 0;
    if (asmCode->code) {
        asmCode->code[0] = '\0';
    }
}

void appendAssembly(AssemblyCode *asmCode, const char *line) {
    int lineLen = strlen(line);
    if (asmCode->length + lineLen + 2 >= asmCode->capacity) {
        asmCode->capacity *= 2;
        asmCode->code = realloc(asmCode->code, asmCode->capacity);
    }
    strcat(asmCode->code + asmCode->length, line);
    strcat(asmCode->code + asmCode->length, "\n");
    asmCode->length += lineLen + 1;
}

void freeAssemblyCode(AssemblyCode *asmCode) {
    if (asmCode->code) {
        free(asmCode->code);
        asmCode->code = NULL;
    }
}

void translatePCodeToX86(Instruction *pcode, int pc_max, AssemblyCode *asmCode) {
    char buffer[256];
    
    // x86-64 Assembly header
    appendAssembly(asmCode, ".section .data");
    appendAssembly(asmCode, "    .align 8");
    appendAssembly(asmCode, "    pascal_stack: .space 8192");
    appendAssembly(asmCode, "    input_format: .asciz \"%ld\"");
    appendAssembly(asmCode, "    output_format: .asciz \"%ld\\n\"");
    appendAssembly(asmCode, "");
    appendAssembly(asmCode, ".section .text");
    appendAssembly(asmCode, "    .global main");
    appendAssembly(asmCode, "");
    appendAssembly(asmCode, "main:");
    appendAssembly(asmCode, "    pushq %rbp");
    appendAssembly(asmCode, "    movq %rsp, %rbp");
    
    for (int i = 0; i <= pc_max; i++) {
        sprintf(buffer, "L%d:", i);
        appendAssembly(asmCode, buffer);
        
        switch (pcode[i].mne) {
            case LDA: // Load Address
                sprintf(buffer, "    leaq -%d(%%rbp), %%rax", pcode[i].suite * 8);
                appendAssembly(asmCode, buffer);
                appendAssembly(asmCode, "    pushq %rax");
                break;
                
            case LDI: // Load Immediate
                sprintf(buffer, "    pushq $%d", pcode[i].suite);
                appendAssembly(asmCode, buffer);
                break;
                
            case LDV: // Load Value
                appendAssembly(asmCode, "    popq %rax");
                appendAssembly(asmCode, "    pushq (%rax)");
                break;
                
            case STO: // Store
                appendAssembly(asmCode, "    popq %rax");  // value
                appendAssembly(asmCode, "    popq %rbx");  // address
                appendAssembly(asmCode, "    movq %rax, (%rbx)");
                break;
                
            case ADD:
                appendAssembly(asmCode, "    popq %rax");
                appendAssembly(asmCode, "    popq %rbx");
                appendAssembly(asmCode, "    addq %rbx, %rax");
                appendAssembly(asmCode, "    pushq %rax");
                break;
                
            case SUB:
                appendAssembly(asmCode, "    popq %rax");
                appendAssembly(asmCode, "    popq %rbx");
                appendAssembly(asmCode, "    subq %rax, %rbx");
                appendAssembly(asmCode, "    pushq %rbx");
                break;
                
            case MUL:
                appendAssembly(asmCode, "    popq %rax");
                appendAssembly(asmCode, "    popq %rbx");
                appendAssembly(asmCode, "    imulq %rbx, %rax");
                appendAssembly(asmCode, "    pushq %rax");
                break;
                
            case DIV:
                appendAssembly(asmCode, "    popq %rcx");  // divisor
                appendAssembly(asmCode, "    popq %rax");  // dividend
                appendAssembly(asmCode, "    cqo");
                appendAssembly(asmCode, "    idivq %rcx");
                appendAssembly(asmCode, "    pushq %rax");
                break;
                
            case EQL:
                appendAssembly(asmCode, "    popq %rax");
                appendAssembly(asmCode, "    popq %rbx");
                appendAssembly(asmCode, "    cmpq %rax, %rbx");
                appendAssembly(asmCode, "    sete %al");
                appendAssembly(asmCode, "    movzbq %al, %rax");
                appendAssembly(asmCode, "    pushq %rax");
                break;
                
            case NEQ:
                appendAssembly(asmCode, "    popq %rax");
                appendAssembly(asmCode, "    popq %rbx");
                appendAssembly(asmCode, "    cmpq %rax, %rbx");
                appendAssembly(asmCode, "    setne %al");
                appendAssembly(asmCode, "    movzbq %al, %rax");
                appendAssembly(asmCode, "    pushq %rax");
                break;
                
            case GTR:
                appendAssembly(asmCode, "    popq %rax");
                appendAssembly(asmCode, "    popq %rbx");
                appendAssembly(asmCode, "    cmpq %rax, %rbx");
                appendAssembly(asmCode, "    setg %al");
                appendAssembly(asmCode, "    movzbq %al, %rax");
                appendAssembly(asmCode, "    pushq %rax");
                break;
                
            case LSS:
                appendAssembly(asmCode, "    popq %rax");
                appendAssembly(asmCode, "    popq %rbx");
                appendAssembly(asmCode, "    cmpq %rax, %rbx");
                appendAssembly(asmCode, "    setl %al");
                appendAssembly(asmCode, "    movzbq %al, %rax");
                appendAssembly(asmCode, "    pushq %rax");
                break;
                
            case GEQ:
                appendAssembly(asmCode, "    popq %rax");
                appendAssembly(asmCode, "    popq %rbx");
                appendAssembly(asmCode, "    cmpq %rax, %rbx");
                appendAssembly(asmCode, "    setge %al");
                appendAssembly(asmCode, "    movzbq %al, %rax");
                appendAssembly(asmCode, "    pushq %rax");
                break;
                
            case LEQ:
                appendAssembly(asmCode, "    popq %rax");
                appendAssembly(asmCode, "    popq %rbx");
                appendAssembly(asmCode, "    cmpq %rax, %rbx");
                appendAssembly(asmCode, "    setle %al");
                appendAssembly(asmCode, "    movzbq %al, %rax");
                appendAssembly(asmCode, "    pushq %rax");
                break;
                
            case BZE: // Branch if Zero
                appendAssembly(asmCode, "    popq %rax");
                appendAssembly(asmCode, "    testq %rax, %rax");
                sprintf(buffer, "    jz L%d", pcode[i].suite);
                appendAssembly(asmCode, buffer);
                break;
                
            case BRN: // Branch
                sprintf(buffer, "    jmp L%d", pcode[i].suite);
                appendAssembly(asmCode, buffer);
                break;
                
            case PRN: // Print
                appendAssembly(asmCode, "    popq %rsi");
                appendAssembly(asmCode, "    movq $output_format, %rdi");
                appendAssembly(asmCode, "    movq $0, %rax");
                appendAssembly(asmCode, "    call printf");
                break;
                
            case INN: // Input
                appendAssembly(asmCode, "    popq %rsi");  // address for scanf
                appendAssembly(asmCode, "    movq $input_format, %rdi");
                appendAssembly(asmCode, "    movq $0, %rax");
                appendAssembly(asmCode, "    call scanf");
                break;
                
            case INT: // Initialize stack space
                sprintf(buffer, "    subq $%d, %%rsp", pcode[i].suite * 8);
                appendAssembly(asmCode, buffer);
                break;
                
            case HLT: // Halt
                appendAssembly(asmCode, "    leave");
                appendAssembly(asmCode, "    ret");
                break;
                
            default:
                sprintf(buffer, "    # Unknown instruction: %s", mneSTR[pcode[i].mne]);
                appendAssembly(asmCode, buffer);
                break;
        }
    }
    
    // Add external function declarations
    appendAssembly(asmCode, "");
    appendAssembly(asmCode, ".extern printf");
    appendAssembly(asmCode, ".extern scanf");
}

void writeAssemblyToFile(AssemblyCode *asmCode, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file) {
        fprintf(file, "%s", asmCode->code);
        fclose(file);
    }
}