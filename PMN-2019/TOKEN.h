#pragma once
#include "pch.h"
#define TOKEN_SEPARATORS "+-*/=(){},;"
#define TOKEN_MAXSIZE 4096

namespace TOKEN
{

	struct Token
	{
		char token[64];
		int line;
	};

	struct TokenTable
	{
		int maxsize;
		int size;
		Token* table;
	};

	TokenTable CreateTokenTable(int size);
	TokenTable* tokenize(In::IN in);
	bool isSeparator(char ch);
}