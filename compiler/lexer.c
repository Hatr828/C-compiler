#include <stdbool.h>
#include <stdio.h>
#include "lexer.h"

TokenList* lexer_run(const char* code) {
    int offset = 0;

    TokenList* list = token_list_create(20);

    while(code[offset] != '\0') {
        char c = code[offset];
        if(c == ' ' || c == '\n' || c == '\t') {
            offset++;
            continue;
        }

        switch (c)
        {
        case '(':
            token_list_add(list, token_create(TOKEN_LEFT_PAREN, code + offset, 1));
            break;
        case ')':
            token_list_add(list, token_create(TOKEN_RIGHT_PAREN, code + offset, 1));
            break;

        case '{':
            token_list_add(list, token_create(TOKEN_LEFT_BRACE, code + offset, 1));
            break;
        case '}':
            token_list_add(list, token_create(TOKEN_RIGHT_BRACE, code + offset, 1));
            break;

        case '[':
            token_list_add(list, token_create(TOKEN_LEFT_BRACKET, code + offset, 1));
            break;
        case ']':
            token_list_add(list, token_create(TOKEN_RIGHT_BRACKET, code + offset, 1));
            break;
        }
        offset++;
    }

    return list;
}

bool is_character(const char c) {
    return (c >= 'a' && c <= 'z') ||
           (c >= 'A' && c <= 'Z') ||
           c == '_';
}

bool is_digit(const char c) {
    return c >= '0' && c <= '9';
}