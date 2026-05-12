#include <stdio.h>
#include <stdlib.h>
#include "statement.h"
#include "lists/list.h"

static int depth;

void print_statement(Statement* st);

void print_statements_without_depth_reset(List* list) {
    Statement* statements = list->items;
    for(int i = 0; i < list->count; i++) {
        print_statement(&statements[i]);
    }
}

char* data_type_to_string(DataType type) {
    switch (type)
    {
    case TYPE_INT:
        return "TYPE_INT";
    
    default:
        return "unknown";
    }
}

char* print_statement_func(StatementFunc* st) {
    printf("(%s, %s)\n", st->name, data_type_to_string((DataType)st->return_type));
    depth++;
    print_statements_without_depth_reset(st->code_block);
}

void print_depth()
{
    for (size_t i = 0; i < depth; i++) {
        printf("\t");
    }
    printf("->");
}

void print_statement(Statement* st) {
    print_depth();
    StatementType s = st->type;
    switch (st->type)
    {
    case STATEMENT_FUNC:
        printf("STATEMENT_FUNC: ");
        print_statement_func(st->statement);
        break;
    case STATEMENT_RETURN:
        printf("STATEMENT_RETURN: \n");
        depth++;
        print_statement(st->statement);
        break;
    case STATEMENT_INT:
        printf("STATEMENT_INT: ");
        printf("(%s)\n", (char*)st->statement);
        depth++;
        break;
    
    default:
        printf("unknown statement");
    }
}

void print_statements(List* list) {
    Statement* statements = list->items;
    for(size_t i = 0; i < list->count; i++) {
        depth = 0;
        print_statement(&statements[i]);
    }
}

void statement_destroy(Statement* statement)
{
    switch (statement->type) {
        case STATEMENT_FUNC:
            StatementFunc* st = statement->statement;
            statements_destroy(st->code_block);
            free(st->name);
            free(st->return_type);
            break;

        case STATEMENT_RETURN:
            statement_destroy(statement->statement);
            free(statement);
            break;

        case STATEMENT_INT:
            free(statement->statement);
            free(statement);
            break;
    }
}

void statements_destroy(List* list)
{
    Statement* statements = list->items;
    
    for(size_t i = 0; i < list->count; i++) {
        Statement statement = statements[i];
        switch (statement.type) {
            case STATEMENT_FUNC:
                StatementFunc* st = statement.statement;
                statements_destroy(st->code_block);
                free(st->name);
                free(st->return_type);
                free(st);
                break;

            case STATEMENT_RETURN:
                statement_destroy(statement.statement);
                break;

            case STATEMENT_INT:
                free(statement.statement);
                break;
        }
    }

    list_destroy(list);
}