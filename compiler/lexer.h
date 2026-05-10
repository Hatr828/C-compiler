#pragma once

#include "token.h"
#include "../lists/token_list.h"

TokenList* lexer_run(const char* code);