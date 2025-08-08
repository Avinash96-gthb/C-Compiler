# C Compiler Project

## Project Overview
This is a personal project aimed at building a small C compiler to deepen my understanding of compiler design and implementation. The goal is to create a functional compiler that can process a subset of the C programming language, providing hands-on experience with lexical analysis, parsing, semantic analysis, and code generation.

## Current Progress
So far, the project includes a **lexical analyzer** (lexer) that supports basic tokenization of C source code. The lexer is capable of:

- Recognizing tokens such as:
  - Keywords: `int`, `char`, `return`
  - Punctuation: `;`, `(`, `)`, `{`, `}`
  - Identifiers (variable/function names)
  - Numeric literals (digits)
- Handling whitespace and comments (both `//` single-line and `/* */` multi-line comments)
- Tracking line numbers for error reporting
- Storing tokens dynamically for future parsing stages

The lexer is implemented in C and processes input from a source file, outputting tokens with their types, lexemes, and line numbers.

## Future Goals
The next steps for the project include:

- **Parser**: Implement a parser to build an Abstract Syntax Tree (AST) from the token stream, supporting a subset of C syntax (e.g., function declarations, variable declarations, and basic statements like `return`).
- **Semantic Analysis**: Add checks for type correctness, variable scoping, and other semantic rules.
- **Code Generation**: Generate intermediate code or target machine code (e.g., assembly or LLVM IR) for simple C programs.
- **Expand Language Support**: Include more C features like loops, conditionals, arrays, and pointers.
- **Error Handling**: Improve error reporting for better developer experience.
- **Optimization**: Explore basic compiler optimizations to improve generated code efficiency.

## Usage Instructions
### Prerequisites
- A C compiler (e.g., `gcc`)
- A Unix-like environment or compatible system for building and running the project

### Building the Project
1. Clone the repository:
   ```bash
   git clone <repository-url>
   cd <repository-directory>
   ```
2. Compile the lexer:
   ```bash
   gcc -o lexer main.c
   ```

### Running the Lexer
The lexer takes a C source file as input and outputs the identified tokens. A sample file, `test.c`, is provided in the repository for testing.

Run the lexer with:
```bash
./lexer test.c
```

### Example Input (`test.c`)
```c
int main() {
    char x;
    return 0;
}
```

### Example Output
```
Line 1: INT           'int'
Line 1: IDENTIFIER    'main'
Line 1: LEFT_PAREN    '('
Line 1: RIGHT_PAREN   ')'
Line 1: LEFT_CURLY    '{'
Line 2: CHAR          'char'
Line 2: IDENTIFIER    'x'
Line 2: SEMICOLON     ';'
Line 3: RETURN        'return'
Line 3: NUMBER        '0'
Line 3: SEMICOLON     ';'
Line 4: RIGHT_CURLY   '}'
Line 4: EOF           ''
```

The lexer processes `test.c`, identifies tokens, and prints their line numbers, types, and lexemes. Tokens are also stored dynamically for future parsing.

## License
This project is licensed under the MIT License.



