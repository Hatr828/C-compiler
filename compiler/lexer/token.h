#pragma once

#include <stddef.h>

typedef enum {
    TOKEN_LEFT_PAREN, // (
    TOKEN_RIGHT_PAREN, // )
    TOKEN_LEFT_BRACE, // {
    TOKEN_RIGHT_BRACE, // }
    TOKEN_LEFT_BRACKET, // [
    TOKEN_RIGHT_BRACKET, // ]

    TOKEN_SEMICOLON, // ;

    TOKEN_KEYWORD,
    TOKEN_IDENTIFIER,
    TOKEN_NUMBER,

    TOKEN_UNKNOWN

} TokenType;

typedef struct {
    TokenType tokenType;
    char* data;
    size_t length;
} Token;

char* token_type_to_string(TokenType type);
Token token_create(TokenType type, const char* data, size_t length);
