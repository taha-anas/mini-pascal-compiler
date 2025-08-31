cmake_minimum_required(VERSION 3.27)
project(Compila C)

set(CMAKE_C_STANDARD 17)

# Include directories
include_directories(include)

# Source files
set(SOURCES
    src/main.c
    src/utils/errors.c
    src/utils/globals.c
    src/lexer/lexer.c
    src/parser/parser.c
    src/semantic/semantic.c
    src/codegen/codegen.c
    src/backend/x86_translator.c
    src/backend/linker.c
)

# Create the main executable
add_executable(Compila ${SOURCES})

# Compiler flags
target_compile_options(Compila PRIVATE -Wall -Wextra -g)

# Build configuration
set(CMAKE_BUILD_TYPE Debug)

# Create build directory structure
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/build)

# Install target
install(TARGETS Compila DESTINATION bin)