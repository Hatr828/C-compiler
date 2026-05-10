#include <stdio.h>
#include <stdlib.h>
#include "token_list.h"

TokenList* token_list_create(size_t capacity) {
    TokenList* tokens = malloc(sizeof(TokenList));

    tokens->items = malloc(capacity * sizeof(Token));
    tokens->count = 0;
    tokens->capacity = capacity;

    return tokens;
}

void token_list_destroy(TokenList* self) {
    free(self->items);
    free(self);
}

void token_list_add(TokenList *self, Token newToken) {
    if(self == NULL) {
       printf("Error in TokenList, self is null");
    }

    if(self->count >= self->capacity) {
        self->capacity *= 2;
        Token* new_items = realloc(self->items, self->capacity * sizeof(Token));
        self->items = new_items;
    }

    self->items[self->count] = newToken;
    self->count++;
}
