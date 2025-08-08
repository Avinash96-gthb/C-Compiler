#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef enum {
    TOKEN_CHAR,
    TOKEN_INT,
    TOKEN_SEMICOLON,
    TOKEN_IDENTIFIER,
    TOKEN_UNKNOWN,
    TOKEN_LEFT_CURLY_BRACKETS,
    TOKEN_RIGHT_CURLY_BRACKETS,
    TOKEN_LEFT_BRACKETS,
    TOKEN_RIGHT_BRACKETS,
    TOKEN_RETURN,
    TOKEN_END_OF_FILE,
    TOKEN_DIGIT,
    TOKEN_FLOAT
} TokenType;

typedef struct Token {
   TokenType type;
   int lineNo;
   char* lexeme; /* data */
}Token;

char* source;
int pos = 0;
int line = 1;

char peek(){
    return source[pos];
}

char advance(){
    return source[pos++];
}

int isAtEnd(){
    return source[pos] == '\0';
}

int isAlpha (char c){
    return isalpha(c) || c == '_';
}

int isAlNum (char c){
    return isalnum(c);
}

int isDigit (char c){
    return isdigit(c);
}

Token make_token(TokenType Type, const char* start, int length){
    Token token;
    token.type = Type;
    token.lexeme = strndup(start, length);
    token.lineNo = line;
    return token;
}


Token tokenise(){
    while (!isAtEnd()){
        char c = advance();
        if (isspace(c)){
            if (c == '\n'){
                line += 1;
                continue;
            }
            while(!isAtEnd() && isspace(peek())){
                if (peek()=='\n'){
                    line++;
                }
                advance();
            }
            continue;
        }

        if (c=='/' && peek() == '/'){
            while(!isAtEnd() && peek() != '\n'){
                advance();
                if (peek()=='\n'){
                    line+=1;
                }
            }
            continue;
        }

        if (c=='/' && peek() == '*'){
            while (!isAtEnd()){
                if (peek() == '*' && source[pos+1] == '/'){
                    advance();
                    advance();
                    break;
                }
                
                if (peek() == '\n'){
                    line+=1;
                }
                advance();
            }
            continue;
        }
        

        switch (c){
            case '(' :
               return make_token(TOKEN_LEFT_BRACKETS, &source[pos-1], 1);
            case ')' :
               return make_token(TOKEN_RIGHT_BRACKETS, &source[pos-1], 1);
            case '{' :
               return make_token(TOKEN_LEFT_CURLY_BRACKETS, &source[pos-1], 1);
            case '}' :
               return make_token(TOKEN_RIGHT_CURLY_BRACKETS, &source[pos-1], 1);
            case ';' :
               return make_token(TOKEN_SEMICOLON, &source[pos-1], 1);
        }

        if (isAlpha(c)){
            int start = pos-1;
            while (isAlNum(peek())){
                advance();
            }
            int length = pos - start;
            char* text = strndup(&source[start], length);
            if (strcmp(text,"int")==0){
                free(text);
                return make_token(TOKEN_INT, &source[start], length);
            }
            else if (strcmp(text,"char")==0){
                free(text);
                return make_token(TOKEN_CHAR, &source[start], length);
            }
            else if (strcmp(text,"return")==0){
                free(text);
                return make_token(TOKEN_RETURN, &source[start], length);
            }
            else if (strcmp(text,"float")==0){
                free(text);
                return make_token(TOKEN_FLOAT, &source[start], length);
            }
            else {
                free(text);
                return make_token(TOKEN_IDENTIFIER, &source[start], length);
            }
        }

        if (isDigit(c)){
            int start = pos - 1;
            while(isDigit(peek())){
                advance();
            }
            int length = pos - start;
            return make_token(TOKEN_DIGIT, &source[start], length);
        }
        return make_token(TOKEN_UNKNOWN, &source[pos-1], 1);
    }
    return make_token(TOKEN_END_OF_FILE, &source[pos],0);
}

const char* token_type_to_str(TokenType type) {
    switch (type) {
        case TOKEN_CHAR: return "CHAR";
        case TOKEN_INT: return "INT";
        case TOKEN_SEMICOLON: return "SEMICOLON";
        case TOKEN_IDENTIFIER: return "IDENTIFIER";
        case TOKEN_UNKNOWN: return "UNKNOWN";
        case TOKEN_LEFT_CURLY_BRACKETS: return "LEFT_CURLY";
        case TOKEN_RIGHT_CURLY_BRACKETS: return "RIGHT_CURLY";
        case TOKEN_LEFT_BRACKETS: return "LEFT_PAREN";
        case TOKEN_RIGHT_BRACKETS: return "RIGHT_PAREN";
        case TOKEN_RETURN: return "RETURN";
        case TOKEN_END_OF_FILE: return "EOF";
        case TOKEN_DIGIT: return "NUMBER";
        default: return "UNKNOWN";
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <source.c>\n", argv[0]);
        return 1;
    }

    FILE* f = fopen(argv[1], "rb");
    if (!f) {
        perror("Error opening file");
        return 1;
    }

    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, 0, SEEK_SET);

    source = malloc(size + 1);
    fread(source, 1, size, f);
    fclose(f);
    source[size] = '\0';

    // Token array (dynamic)
    Token* tokens = NULL;
    size_t token_count = 0;

    Token token;
    do {
        token = tokenise();
        printf("Line %d: %-12s '%s'\n", token.lineNo, token_type_to_str(token.type), token.lexeme);

        // Store token
        tokens = realloc(tokens, sizeof(Token) * (token_count + 1));
        tokens[token_count++] = token; // shallow copy (lexeme is already malloc'ed)

    } while (token.type != TOKEN_END_OF_FILE);

    printf("\nStored %zu tokens for parsing.\n", token_count);

    for (size_t i = 0; i < token_count; i++) {
        free(tokens[i].lexeme);
    }
    free(tokens);
    free(source);
    return 0;
}
