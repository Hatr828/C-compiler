#include <stdio.h>
#include <stdlib.h>
#include "compiler/lexer/lexer.h"
#include "compiler/parser/parser.h"
#include "compiler/parser/statement.h"
#include "lists/list.h"

char* read_file_as_string(const char* path);

int main() {
    int a = 0;
    int* b = &a;
    *b++;
    printf("%d", *b);

    /*
    char* code = read_file_as_string("test.txt");
    
    List* token_list = lexer_run(code);
    Token *tokens = token_list->items;
    for(size_t i = 0; i < token_list->count; i++) {
        printf("%s: ", token_type_to_string(tokens[i].tokenType));
        printf("%.*s\n", (int)tokens[i].length, tokens[i].data);
    }
    printf("\n---\n\n");
    List* statement_list = parser_run(token_list);
    print_statements(statement_list);

    list_destroy(token_list);
    statements_destroy(statement_list);
    free(code); */
}

char* read_file_as_string(const char* path)
{
    FILE* file = fopen(path, "rb");
    if (file == NULL) {
        perror("fopen");
        return NULL;
    }

    if (fseek(file, 0, SEEK_END) != 0) {
        perror("fseek");
        fclose(file);
        return NULL;
    }

    long size = ftell(file);
    if (size < 0) {
        perror("ftell");
        fclose(file);
        return NULL;
    }

    rewind(file);

    char* buffer = malloc((size_t)size + 1);
    if (buffer == NULL) {
        perror("malloc");
        fclose(file);
        return NULL;
    }

    size_t read_bytes = fread(buffer, 1, (size_t)size, file);
    if (read_bytes != (size_t)size) {
        perror("fread");
        free(buffer);
        fclose(file);
        return NULL;
    }

    buffer[size] = '\0';

    fclose(file);
    return buffer;
}