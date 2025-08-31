#ifndef COMPILA_LINKER_H
#define COMPILA_LINKER_H

#include <stdbool.h>

typedef enum {
    LINK_SUCCESS,
    LINK_ERROR_ASSEMBLER_FAILED,
    LINK_ERROR_LINKER_FAILED,
    LINK_ERROR_FILE_NOT_FOUND
} LinkResult;

LinkResult assembleAndLink(const char *assembly_file, const char *output_executable);
bool runExecutable(const char *executable_path);

#endif // COMPILA_LINKER_H