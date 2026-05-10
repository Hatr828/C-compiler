#pragma once

#include <stddef.h>
#include "compiler/lexer/token.h"

typedef struct {
    Token* items;
    size_t count;
    size_t capacity;
} TokenList;

TokenList* token_list_create(size_t capacity);
void token_list_destroy(TokenList* self);
void token_list_add(TokenList *self, Token newToken);