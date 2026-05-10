#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "lexer.h"

int get_word(const char* code);
TokenType get_single_character_token_type(const char c);
bool is_keyword(const char* data, size_t length);
bool is_character(const char c);
bool is_digit(const char c);

TokenList* lexer_run(const char* code) {
    int offset = 0;

    TokenList* list = token_list_create(20);

    while(code[offset] != '\0') {
        char c = code[offset];
        if(c == ' ' || c == '\n' || c == '\t') {
            offset++;
            continue;
        }

        TokenType type = get_single_character_token_type(code[offset]);

        if(type != TOKEN_UNKNOWN) {
            token_list_add(list, token_create(type, code + offset, 1));
            offset++;
            continue;
        }

        int offset2 = get_word(code + offset);
        if(!offset2) {
            printf("Error in lexer, unknown TokenType");
            offset++;
            continue;
        }

        if(is_keyword(code + offset, offset2)) {
            token_list_add(list, token_create(TOKEN_KEYWORD, code + offset, offset2));
            offset += offset2;
            continue;
        }

        if(is_character(code[offset])) {
            token_list_add(list, token_create(TOKEN_IDENTIFIER, code + offset, offset2));
            offset += offset2;
            continue;
        }
        else {
            token_list_add(list, token_create(TOKEN_NUMBER, code + offset, offset2));
            offset += offset2;
            continue;
        }
    }

    return list;
}

int get_word(const char* code) {
    int res = 0;

    while(is_character(code[res]) || is_digit(code[res])) {
        res++;
    }

    return res;
}

TokenType get_single_character_token_type(const char c) {
        switch (c)
        {
        case '(':
            return TOKEN_LEFT_PAREN;
            break;
        case ')':
            return TOKEN_RIGHT_PAREN;
            break;

        case '{':
            return TOKEN_LEFT_BRACE;
            break;
        case '}':
            return TOKEN_RIGHT_BRACE;
            break;

        case '[':
            return TOKEN_LEFT_BRACE;
            break;
        case ']':
            return TOKEN_RIGHT_BRACE;
            break;

        case ';':
            return TOKEN_SEMICOLON;
            break;

        default:
            return TOKEN_UNKNOWN;
            break;
        }
}

bool is_keyword(const char* data, size_t length) {
    switch (length)
    {
    case 3:
        return memcmp(data, "int", 3) == 0;
    case 4:
        return memcmp(data, "void", 4) == 0;
    case 6:
        return memcmp(data, "return", 6) == 0;
    default:
        return false;
    }
}

bool is_character(const char c) {
    return (c >= 'a' && c <= 'z') ||
           (c >= 'A' && c <= 'Z') ||
           c == '_';
}

bool is_digit(const char c) {
    return c >= '0' && c <= '9';
}