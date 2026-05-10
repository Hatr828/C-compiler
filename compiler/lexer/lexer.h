#pragma once

#include "compiler/lexer/lexer.h"
#include "lists/token_list.h"

TokenList* lexer_run(const char* code);