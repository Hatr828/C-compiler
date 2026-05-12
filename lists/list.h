#pragma once

#include <stddef.h>
#include "compiler/lexer/token.h"

typedef struct {
    void* items;
    size_t item_size;
    size_t count;
    size_t capacity;
} List;

List* list_create(size_t capacity, size_t size);
void list_destroy(List* self);
void list_add(List *self, void* new_item);