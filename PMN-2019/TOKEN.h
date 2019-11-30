#pragma once
#include "pch.h"
#define TOKEN_SEPARATORS " \t\n+-*/%=<>(){},;!"
#define TOKEN_MAXSIZE 4096

namespace TOKEN
{

	struct Token
	{
		char token[258];
		int length;
		int line;
		int linePosition;
	};

	struct TokenTable
	{
		//int CountOfWord;  ол-во сслов в тексте дл€ создани€ таблицы лексем
		int maxsize;
		int size;
		Token* table;
	};

	TokenTable CreateTokenTable(int size);
	void addToken(TokenTable& tokens, char* token, int line, int linePosition, int length);
	TokenTable tokenize(In::IN in);
	bool isSeparator(char ch);
	char* sepToken(char sep);
	void SaveTokenTableInFile(TokenTable tokens, wchar_t outfile[]);
}