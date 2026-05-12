#pragma once

#include "lists/list.h"

typedef enum {
    STATEMENT_FUNC,
    STATEMENT_RETURN,
    STATEMENT_INT,
} StatementType;

typedef struct {
    char* name;
    // params
    void* code_block;
    void* return_type;
} StatementFunc;

typedef struct {
    StatementType type;
    void* statement;
} Statement;

typedef enum {
    TYPE_INT,
} DataType;

void print_statements(List* list);
void statements_destroy(List* list);