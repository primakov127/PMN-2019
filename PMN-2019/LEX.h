#pragma once
#include "pch.h"
using namespace std;

namespace Lexer
{
	struct LEX
	{
		IT::IdTable idtable;
		LT::LexTable lextable;
		LEX();
		LEX(int lexTableSize, int idTableSize);
	};

	char lexType(TOKEN::Token token);
	LEX fillingInTables(TOKEN::TokenTable tokenTable);
	int searchID(stack<int> areaOfVisibility, string id, IT::IdTable& idtable);
}