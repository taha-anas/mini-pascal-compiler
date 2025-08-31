CC = gcc
CFLAGS = -Wall -Wextra -g -std=c17 -Iinclude
TARGET = compila
BUILD_DIR = build
TEST_DIR = tests

SOURCES = src/main.c \
          src/utils/errors.c \
          src/utils/globals.c \
          src/lexer/lexer.c \
          src/parser/parser.c \
          src/semantic/semantic.c \
          src/codegen/codegen.c \
          src/backend/x86_translator.c \
          src/backend/linker.c

OBJECTS = $(SOURCES:src/%.c=$(BUILD_DIR)/%.o)

.PHONY: all clean test install help

all: $(BUILD_DIR) $(TARGET)

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)/utils
	@mkdir -p $(BUILD_DIR)/lexer
	@mkdir -p $(BUILD_DIR)/parser
	@mkdir -p $(BUILD_DIR)/semantic
	@mkdir -p $(BUILD_DIR)/codegen
	@mkdir -p $(BUILD_DIR)/backend

$(TARGET): $(OBJECTS)
	@echo "Linking $@..."
	@$(CC) $(OBJECTS) -o $@
	@echo "Build completed: $@"

$(BUILD_DIR)/%.o: src/%.c
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "Cleaning build files..."
	@rm -rf $(BUILD_DIR)
	@rm -f $(TARGET)
	@rm -f tests/*.pcode tests/*.s tests/*.o
	@rm -f tests/test_program tests/test_operations tests/test_control
	@echo "Clean completed"

test: $(TARGET)
	@echo "Running tests..."
	@echo "\n=== Test 1: Basic Operations ==="
	@./$(TARGET) -r tests/test
	@echo "\n=== Test 2: Control Flow ==="
	@./$(TARGET) -r tests/test1
	@echo "\n=== Test 3: Variables ==="
	@./$(TARGET) -r tests/test2

install: $(TARGET)
	@echo "Installing to /usr/local/bin..."
	@sudo cp $(TARGET) /usr/local/bin/
	@echo "Installation completed"

help:
	@echo "Pascal Compiler Build System"
	@echo "Usage:"
	@echo "  make          - Build the compiler"
	@echo "  make clean    - Clean build files"
	@echo "  make test     - Run test suite"
	@echo "  make install  - Install to system"
	@echo "  make help     - Show this help"
	@echo ""
	@echo "Compiler Usage:"
	@echo "  ./compila <file.p>        - Compile Pascal program"
	@echo "  ./compila -r <file.p>     - Compile and run"
	@echo "  ./compila -o name <file.p> - Specify output name"
	@echo "  ./compila -s <file.p>     - Keep assembly file"