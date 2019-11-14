#pragma once
#include "pch.h"

namespace LEX
{
	struct LEX
	{
		IT::IdTable idtable;
		LT::LexTable lextable;
	};

	struct GRAPH
	{
		char lex;
		FST::FST graph;
	};

	char lexType(char *token);
}