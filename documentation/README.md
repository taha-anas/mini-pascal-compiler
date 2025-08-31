# Compila - Mini Pascal Compiler

A complete Pascal compiler that translates Pascal source code to executable x86-64 binaries.

## Features

- **Full Pascal Grammar Support**: Variables, constants, expressions, control structures
- **Modular Architecture**: Clean separation of compiler phases
- **P-code Intermediate Representation**: Stack-based intermediate code
- **x86-64 Assembly Generation**: Direct translation to native assembly
- **Automatic Linking**: Generates executable binaries
- **Error Reporting**: Comprehensive lexical, syntactic, and semantic error detection

## Project Structure

```
.
├── src/
│   ├── main.c              # Main compiler driver
│   ├── lexer/
│   │   └── lexer.c         # Lexical analysis
│   ├── parser/
│   │   └── parser.c        # Syntax analysis & parsing
│   ├── semantic/
│   │   └── semantic.c      # Semantic analysis
│   ├── codegen/
│   │   └── codegen.c       # P-code generation
│   ├── backend/
│   │   ├── x86_translator.c # x86 assembly translation
│   │   └── linker.c        # Assembly and linking
│   └── utils/
│       ├── errors.c        # Error handling
│       └── globals.c       # Global variables and constants
├── include/                # Header files
├── tests/                  # Pascal test programs
├── build/                  # Build artifacts
└── docs/                   # Documentation
```

## Compilation Phases

1. **Lexical Analysis** - Tokenizes Pascal source code
2. **Syntax Analysis** - Parses tokens into abstract syntax tree
3. **Semantic Analysis** - Type checking and symbol table management
4. **P-code Generation** - Stack-based intermediate code generation
5. **Assembly Translation** - Converts P-code to x86-64 assembly
6. **Assembly & Linking** - Generates executable binary

## Building

### Using Make
```bash
make                # Build compiler
make clean          # Clean build files
make test           # Run test suite
make install        # Install to system (requires sudo)
```

### Using CMake
```bash
mkdir build && cd build
cmake ..
make
```

## Usage

### Basic Compilation
```bash
./compila program.p          # Compile Pascal program
./program                    # Run generated executable
```

### Command Line Options
```bash
./compila [options] <pascal_file>

Options:
  -o <output>    Specify output executable name (default: program)
  -s             Keep assembly file (.s)
  -p             Keep P-code file (.pcode)
  -r             Run executable after compilation
  -h             Show help
```

### Examples
```bash
# Compile and run
./compila -r tests/test

# Compile with custom output name
./compila -o calculator calculator.p

# Keep intermediate files for debugging
./compila -s -p program.p
```

## Pascal Language Support

### Supported Features
- Program structure with `program` keyword
- Variable declarations (`var`)
- Constant declarations (`const`)
- Integer arithmetic (+, -, *, /)
- Relational operators (<, >, <=, >=, =, <>)
- Control structures:
  - `if-then-else`
  - `while-do`
  - `repeat-until`
  - `for` loops
  - `case` statements
- I/O operations (`read`, `write`)
- Block structure with `begin-end`

### Example Pascal Program
```pascal
program operations;
var num1, num2, result;

begin
  read(num1);
  read(num2);
  
  result := num1 + num2;
  write(result);
  
  result := num1 * num2;
  write(result);
end.
```

## Testing

The `tests/` directory contains various Pascal programs for testing:

- `test` - Basic arithmetic operations
- `test1` - Conditional statements
- `test2` - Variable declarations
- `test3` - Control flow
- `test4` - Expression evaluation
- `test5` - Complex operations

Run all tests:
```bash
make test
```

## Technical Details

### P-code Instructions
The compiler generates stack-based P-code instructions:
- `LDA` - Load Address
- `LDI` - Load Immediate
- `LDV` - Load Value
- `STO` - Store
- `ADD, SUB, MUL, DIV` - Arithmetic
- `EQL, NEQ, GTR, LSS, GEQ, LEQ` - Comparisons
- `BZE, BRN` - Branching
- `INN, PRN` - Input/Output
- `INT` - Initialize stack space
- `HLT` - Halt

### x86-64 Assembly Generation
- Uses System V ABI calling convention
- Stack-based evaluation model
- Direct register allocation for operations
- Links with C runtime for I/O functions

## Dependencies

- GCC (for linking)
- GNU Assembler (`as`)
- C standard library

## Error Handling

The compiler provides comprehensive error reporting:
- **Lexical Errors**: Invalid characters, malformed tokens
- **Syntax Errors**: Missing keywords, incorrect structure
- **Semantic Errors**: Undefined variables, type mismatches

## Contributing

1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Add tests for new features
5. Submit a pull request

## License

This project is open source. See LICENSE file for details.

## Authors

Pascal Compiler Implementation - Educational compiler project demonstrating complete compilation pipeline from Pascal source to x86-64 executable.