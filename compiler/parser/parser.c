#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "statement.h"
#include "parser.h"


Statement* parse(List* list, Token* tokens, const int count, size_t* idx) {
    while(count > *idx) {
        switch (tokens[*idx].tokenType)
        {
        case TOKEN_KEYWORD:
            if(tokens[*idx+1].tokenType == TOKEN_IDENTIFIER) {
                if(tokens[*idx+2].tokenType != TOKEN_LEFT_PAREN) {
                    fprintf(stderr, "Parser error: expected (\n");
                    exit(1);
                }
                if(tokens[*idx+3].tokenType != TOKEN_RIGHT_PAREN) {
                    fprintf(stderr, "Parser error: expected )\n");
                    exit(1);
                }
                if(tokens[*idx+4].tokenType != TOKEN_LEFT_BRACE) {
                    fprintf(stderr, "Parser error: expected {\n");
                    exit(1);
                }

                StatementFunc* func = malloc(sizeof(StatementFunc));

                func->name = malloc(tokens[*idx+1].length + 1);
                memcpy(func->name, tokens[*idx+1].data, tokens[*idx+1].length);
                func->name[tokens[*idx+1].length] = '\0';

                func->return_type = TYPE_INT;
                *idx += 5;
                List* code_block = list_create(1, sizeof(Statement));
        
                while(tokens[*idx].tokenType != TOKEN_RIGHT_BRACE) {
                    Statement* st = parse(list, tokens, count, idx);
                    list_add(code_block, st);
                    free(st);
                }
                (*idx)++;
                func->code_block = code_block;
                Statement* st = malloc(sizeof(Statement));
                st->type = STATEMENT_FUNC;
                st->statement = func;
                return st;
            }

            if(!memcmp(tokens[*idx].data, "return", 6)) {
                Statement* st = malloc(sizeof(Statement));
                st->type = STATEMENT_RETURN;
                (*idx)++;
                st->statement = parse(list, tokens, count, idx);
                return st;
            }
        
        case TOKEN_NUMBER:
            Statement* st = malloc(sizeof(Statement));
            st->type = STATEMENT_INT;

            char* temp = malloc(tokens[*idx].length + 1);
            memcpy(temp, tokens[*idx].data, tokens[*idx].length);
            temp[tokens[*idx].length] = '\0';
            st->statement = temp;

            if(tokens[*idx+1].tokenType != TOKEN_SEMICOLON) {
                fprintf(stderr, "Parser error: expected ;\n");
                exit(1);
            }
            *idx+=2;
            return st;
        
        default:
            fprintf(stderr, "Parser error: unknown token (%s)\n", token_type_to_string(tokens[*idx].tokenType));
            exit(1);
        }
    }
}

List* parser_run(List* tokens_) {
    size_t idx = 0;
    Token* tokens = tokens_->items;
    List* list = list_create(3, sizeof(Statement));
    while(tokens_->count > idx) {
        Statement* st = parse(list, tokens, tokens_->count, &idx);
        list_add(list, st);
        free(st);
    }
    return list;
}