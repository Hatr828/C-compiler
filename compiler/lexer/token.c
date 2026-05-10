#include "token.h"

char* token_type_to_string(TokenType type) {
    switch (type)
    {
    case TOKEN_LEFT_PAREN:
        return "TOKEN_LEFT_PAREN";
    case TOKEN_RIGHT_PAREN:
        return "TOKEN_RIGHT_PAREN";

    case TOKEN_LEFT_BRACKET:
        return "TOKEN_LEFT_BRACKET";
    case TOKEN_RIGHT_BRACKET:
        return "TOKEN_RIGHT_BRACKET";

    case TOKEN_LEFT_BRACE:
        return "TOKEN_LEFT_BRACE";
    case TOKEN_RIGHT_BRACE:
        return "TOKEN_RIGHT_BRACE";

    case TOKEN_KEYWORD:
        return "TOKEN_KEYWORD";
    case TOKEN_IDENTIFIER:
        return "TOKEN_IDENTIFIER";
    case TOKEN_NUMBER:
        return "TOKEN_NUMBER";
    case TOKEN_SEMICOLON:
        return "TOKEN_SEMICOLON";
    case TOKEN_UNKNOWN:
        return "TOKEN_UNKNOWN";
    default:
        return "Unknown token";
    }
}

Token token_create(TokenType type, const char* data, size_t length) {
    return (Token) {
        .tokenType = type,
        .data = data,
        .length = length
    };
}
