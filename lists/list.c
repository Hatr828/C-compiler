#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

List* list_create(size_t capacity, size_t size) {
    List* list = malloc(sizeof(List));

    list->items = malloc(capacity * size);
    list->item_size = size;
    list->count = 0;
    list->capacity = capacity;

    return list;
}

void list_destroy(List* self) {
    free(self->items);
    free(self);
}

void list_add(List *self, void* new_item) {
    if(self == NULL) {
       printf("Error in list, self is null");
    }

    if(self->count >= self->capacity) {
        self->capacity *= 2;
        void* new_items = realloc(self->items, self->capacity * self->item_size);
        self->items = new_items;
    }

    unsigned char *items = self->items;
    void *des = items + self->count * self->item_size;

    memcpy(des, new_item, self->item_size);
    self->count++;
}
