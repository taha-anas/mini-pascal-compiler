#include "../include/types.h"
#include "../include/errors.h"
#include "../include/lexer.h"
#include "../include/parser.h"
#include "../include/semantic.h"
#include "../include/codegen.h"
#include "../include/x86_translator.h"
#include "../include/linker.h"
#include <string.h>
#include <unistd.h>

void printUsage(const char *progname) {
    printf("Usage: %s [options] <pascal_file>\n", progname);
    printf("Options:\n");
    printf("  -o <output>    Specify output executable name (default: program)\n");
    printf("  -s             Keep assembly file (.s)\n");
    printf("  -p             Keep P-code file (.pcode)\n");
    printf("  -r             Run executable after compilation\n");
    printf("  -h             Show this help\n");
}

int main(int argc, char *argv[]) {
    char *input_file = NULL;
    char *output_name = "program";
    bool keep_assembly = false;
    bool keep_pcode = false;
    bool run_after = false;
    
    // Parse command line arguments
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-o") == 0 && i + 1 < argc) {
            output_name = argv[++i];
        } else if (strcmp(argv[i], "-s") == 0) {
            keep_assembly = true;
        } else if (strcmp(argv[i], "-p") == 0) {
            keep_pcode = true;
        } else if (strcmp(argv[i], "-r") == 0) {
            run_after = true;
        } else if (strcmp(argv[i], "-h") == 0) {
            printUsage(argv[0]);
            return 0;
        } else if (argv[i][0] != '-') {
            input_file = argv[i];
        } else {
            fprintf(stderr, "Unknown option: %s\n", argv[i]);
            printUsage(argv[0]);
            return 1;
        }
    }
    
    if (!input_file) {
        fprintf(stderr, "Error: No input file specified\n");
        printUsage(argv[0]);
        return 1;
    }
    
    // Open input file
    fichier = fopen(input_file, "r");
    if (!fichier) {
        fprintf(stderr, "Error: Cannot open file '%s'\n", input_file);
        return 1;
    }
    
    printf("Compiling Pascal program: %s\n", input_file);
    
    // Initialize compiler
    lireCar();  // Read first character
    symSuiv();  // Get first token
    
    // Create P-code output file name
    char pcode_file[256];
    strcpy(pcode_file, output_name);
    strcat(pcode_file, ".pcode");
    
    OUTPUT = fopen(pcode_file, "w");
    if (!OUTPUT) {
        fprintf(stderr, "Error: Cannot create P-code file '%s'\n", pcode_file);
        fclose(fichier);
        return 1;
    }
    
    // Parse and generate P-code
    printf("Phase 1: Lexical and Syntactic Analysis...\n");
    printf("Phase 2: Semantic Analysis...\n");
    printf("Phase 3: P-code Generation...\n");
    
    PROGRAM();  // Start parsing from PROGRAM rule
    
    fclose(fichier);
    
    // Save P-code to file
    savePCODE();
    fclose(OUTPUT);
    
    printf("P-code generation completed: %s\n", pcode_file);
    
    // Translate P-code to x86 assembly
    printf("Phase 4: Assembly Translation...\n");
    
    AssemblyCode asmCode;
    initAssemblyCode(&asmCode);
    
    translatePCodeToX86(PCODE, PC, &asmCode);
    
    // Create assembly file name
    char assembly_file[256];
    strcpy(assembly_file, output_name);
    strcat(assembly_file, ".s");
    
    writeAssemblyToFile(&asmCode, assembly_file);
    printf("Assembly generation completed: %s\n", assembly_file);
    
    // Assemble and link
    printf("Phase 5: Assembly and Linking...\n");
    
    LinkResult result = assembleAndLink(assembly_file, output_name);
    
    switch (result) {
        case LINK_SUCCESS:
            printf("Compilation successful: %s\n", output_name);
            break;
        case LINK_ERROR_ASSEMBLER_FAILED:
            fprintf(stderr, "Error: Assembly failed\n");
            freeAssemblyCode(&asmCode);
            return 1;
        case LINK_ERROR_LINKER_FAILED:
            fprintf(stderr, "Error: Linking failed\n");
            freeAssemblyCode(&asmCode);
            return 1;
        case LINK_ERROR_FILE_NOT_FOUND:
            fprintf(stderr, "Error: File not found during linking\n");
            freeAssemblyCode(&asmCode);
            return 1;
    }
    
    // Clean up temporary files unless user wants to keep them
    if (!keep_pcode) {
        unlink(pcode_file);
    }
    if (!keep_assembly) {
        unlink(assembly_file);
    }
    
    freeAssemblyCode(&asmCode);
    
    // Run executable if requested
    if (run_after) {
        printf("\n--- Running executable ---\n");
        char executable_path[256];
        strcpy(executable_path, "./");
        strcat(executable_path, output_name);
        
        if (!runExecutable(executable_path)) {
            fprintf(stderr, "Error: Failed to run executable\n");
            return 1;
        }
    }
    
    return 0;
}