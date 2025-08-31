CC = gcc
CFLAGS = -Wall -Wextra -g -std=c17
TARGET = compila
BUILD_DIR = build

# Source directories
MAIN_DIR = compiler/main
LEXER_DIR = compiler/frontend/lexer
PARSER_DIR = compiler/frontend/parser
SEMANTIC_DIR = compiler/frontend/semantic
CODEGEN_DIR = compiler/backend/codegen
X86_DIR = compiler/backend/x86_translator
LINKER_DIR = compiler/backend/linker
UTILS_DIR = compiler/utils

# Include paths
INCLUDES = -I$(LEXER_DIR) -I$(PARSER_DIR) -I$(SEMANTIC_DIR) -I$(CODEGEN_DIR) -I$(X86_DIR) -I$(LINKER_DIR) -I$(UTILS_DIR)

SOURCES = $(MAIN_DIR)/main.c \
          $(LEXER_DIR)/lexer.c \
          $(PARSER_DIR)/parser.c \
          $(SEMANTIC_DIR)/semantic.c \
          $(CODEGEN_DIR)/codegen.c \
          $(X86_DIR)/x86_translator.c \
          $(LINKER_DIR)/linker.c \
          $(UTILS_DIR)/errors.c \
          $(UTILS_DIR)/globals.c

OBJECTS = $(SOURCES:%.c=$(BUILD_DIR)/%.o)

.PHONY: all clean test help semantic-structure

all: $(BUILD_DIR) $(TARGET)

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)/$(MAIN_DIR)
	@mkdir -p $(BUILD_DIR)/$(LEXER_DIR)
	@mkdir -p $(BUILD_DIR)/$(PARSER_DIR)
	@mkdir -p $(BUILD_DIR)/$(SEMANTIC_DIR)
	@mkdir -p $(BUILD_DIR)/$(CODEGEN_DIR)
	@mkdir -p $(BUILD_DIR)/$(X86_DIR)
	@mkdir -p $(BUILD_DIR)/$(LINKER_DIR)
	@mkdir -p $(BUILD_DIR)/$(UTILS_DIR)

$(TARGET): $(OBJECTS)
	@echo "Linking $@..."
	@$(CC) $(OBJECTS) -o $@
	@echo "Build completed: $@"

$(BUILD_DIR)/%.o: %.c
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo "Cleaning build files..."
	@rm -rf $(BUILD_DIR)
	@rm -f $(TARGET)
	@rm -f test-programs/*.pcode test-programs/*.s test-programs/*.o
	@rm -f *.pcode *.s *.o program
	@echo "Clean completed"

test: $(TARGET)
	@echo "Running semantic structure tests..."
	@echo "\n=== Test 1: Conditional Statements ==="
	@./$(TARGET) -r test-programs/test1
	@echo "\n=== Test 2: While Loops ==="
	@./$(TARGET) -r test-programs/test2
	@echo "\n=== Test 3: Variable Assignment ==="
	@./$(TARGET) -r test-programs/test3
	@echo "\n=== Test 4: Constants and Variables ==="
	@./$(TARGET) -r test-programs/test4

semantic-structure:
	@echo "Pascal Compiler - Semantic Folder Structure:"
	@echo ""
	@echo "compiler/"
	@echo "├── frontend/          # Front-end compilation phases"
	@echo "│   ├── lexer/         # Lexical analysis (tokenization)"
	@echo "│   ├── parser/        # Syntax analysis (parsing)"
	@echo "│   └── semantic/      # Semantic analysis"
	@echo "├── backend/           # Back-end compilation phases"
	@echo "│   ├── codegen/       # P-code generation"
	@echo "│   ├── x86_translator/# x86-64 assembly translation"
	@echo "│   └── linker/        # Assembly and linking"
	@echo "├── utils/             # Utility functions"
	@echo "└── main/              # Main compiler driver"
	@echo ""
	@echo "test-programs/         # Pascal test programs"
	@echo "examples/              # Pascal example programs"
	@echo "documentation/         # Project documentation"

help: semantic-structure
	@echo ""
	@echo "Build Commands:"
	@echo "  make                 - Build the compiler"
	@echo "  make clean           - Clean build files"
	@echo "  make test            - Run test suite"
	@echo "  make semantic-structure - Show folder organization"
	@echo "  make help            - Show this help"
	@echo ""
	@echo "Compiler Usage:"
	@echo "  ./compila <file.p>        - Compile Pascal program"
	@echo "  ./compila -r <file.p>     - Compile and run"
	@echo "  ./compila -o name <file.p> - Specify output name"
	@echo "  ./compila -s <file.p>     - Keep assembly file"