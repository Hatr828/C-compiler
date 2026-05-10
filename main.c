#include <stdio.h>
#include "compiler/lexer/lexer.h"
#include "lists/token_list.h"

int main() {
    char* code = "\n int main() \n { \n return 0; \n }";

    TokenList* tokens = lexer_run(code);

    for(size_t i = 0; i < tokens->count; i++) {
        printf("%s: ", token_type_to_string(tokens->items[i].tokenType));
        printf("%.*s\n", (int)tokens->items[i].length, tokens->items[i].data);
    }

    token_list_destroy(tokens);
}