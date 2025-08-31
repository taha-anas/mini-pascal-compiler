#include "linker.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

LinkResult assembleAndLink(const char *assembly_file, const char *output_executable) {
    char command[512];
    int result;
    char object_file[256];
    
    // Create object file name
    strcpy(object_file, assembly_file);
    char *dot = strrchr(object_file, '.');
    if (dot) {
        strcpy(dot, ".o");
    } else {
        strcat(object_file, ".o");
    }
    
    // Step 1: Assemble the .s file to .o file using gas (GNU assembler)
    snprintf(command, sizeof(command), "as --64 %s -o %s", assembly_file, object_file);
    result = system(command);
    
    if (result != 0) {
        fprintf(stderr, "Assembly failed: %s\n", command);
        return LINK_ERROR_ASSEMBLER_FAILED;
    }
    
    // Step 2: Link the object file to create executable
    // Link with C runtime for printf/scanf support
    snprintf(command, sizeof(command), "gcc -no-pie %s -o %s", object_file, output_executable);
    result = system(command);
    
    if (result != 0) {
        fprintf(stderr, "Linking failed: %s\n", command);
        // Clean up object file
        unlink(object_file);
        return LINK_ERROR_LINKER_FAILED;
    }
    
    // Clean up object file
    unlink(object_file);
    
    // Make executable
    snprintf(command, sizeof(command), "chmod +x %s", output_executable);
    system(command);
    
    return LINK_SUCCESS;
}

bool runExecutable(const char *executable_path) {
    if (access(executable_path, F_OK) != 0) {
        fprintf(stderr, "Executable not found: %s\n", executable_path);
        return false;
    }
    
    // Make it executable just in case
    char command[512];
    snprintf(command, sizeof(command), "chmod +x %s", executable_path);
    system(command);
    
    // Run the executable
    int result = system(executable_path);
    return (result == 0);
}