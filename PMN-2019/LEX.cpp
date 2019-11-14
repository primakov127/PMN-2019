#include "pch.h"

namespace LEX
{
	GRAPH graph[] =
	{
		{ LEX_INTEGER, FST::FST(GRAPH_INTEGER) },
		{ LEX_STRING, FST::FST(GRAPH_STRING) },
		{ LEX_FUNCTION, FST::FST(GRAPH_FUNCTION) },
		{ LEX_DECLARE, FST::FST(GRAPH_DECLARE) },
		{ LEX_RETURN, FST::FST(GRAPH_RETURN) },
		{ LEX_PRINT, FST::FST(GRAPH_OUT) },
		{ LEX_MAIN, FST::FST(GRAPH_MAIN) },
		{ LEX_LITERAL, FST::FST(GRAPH_INT_LITERAL) },
		{ LEX_LITERAL, FST::FST(GRAPH_STRING_LITERAL) },
		{ LEX_ID, FST::FST(GRAPH_ID) },
		{ LEX_SEMICOLON, FST::FST(GRAPH_SEMICOLON) },
		{ LEX_COMMA, FST::FST(GRAPH_COMMA) },
		{ LEX_LEFTBRACE, FST::FST(GRAPH_LEFTBRACE_OPEN) },
		{ LEX_RIGHTBRACE, FST::FST(GRAPH_RIGHTBRACE_CLOSE) },
		{ LEX_LEFTHESIS, FST::FST(GRAPH_LEFTHESIS_OPEN) },
		{ LEX_RIGHTHESIS, FST::FST(GRAPH_RIGHTHESIS_CLOSE) },
		{ LEX_LEFTRVK, FST::FST(GRAPH_LEFTRVK_OPEN) },
		{ LEX_RIGHTRVK, FST::FST(GRAPH_RIGHTRVK_CLOSE) },
		{ LEX_PLUS, FST::FST(GRAPH_PLUS) },
		{ LEX_MINUS, FST::FST(GRAPH_MINUS) },
		{ LEX_STAR, FST::FST(GRAPH_STAR) },
		{ LEX_DIRSLASH, FST::FST(GRAPH_DIRSLASH) },
		{LEX_REMDIV, FST::FST(GRAPH_REMDIV)},
		{ LEX_EQUAL, FST::FST(GRAPH_EQUALS) }
	};

	
	char lexType(TOKEN::Token token)
	{
		for (int i = 0; i < LENGTHOF(graph); i++)
		{
			FST::FST fstlex(token.token, graph[i].graph);
			if (FST::execute(fstlex))
			{
				switch (graph[i].lex)
				{
				case LEX_SEMICOLON:
					return LEX_SEMICOLON;
				case LEX_EQUAL:
					return LEX_EQUAL;
				case LEX_COMMA:
					return LEX_COMMA;
				case LEX_LEFTBRACE:
					return LEX_LEFTBRACE;
				case LEX_RIGHTBRACE:
					return LEX_RIGHTBRACE;
				case LEX_LEFTRVK:
					return LEX_LEFTRVK;
				case LEX_RIGHTRVK:
					return LEX_RIGHTRVK;
				case LEX_LEFTHESIS:
					return LEX_LEFTHESIS;
				case LEX_RIGHTHESIS:
					return LEX_RIGHTHESIS;
				case LEX_PLUS:
					return LEX_PLUS;
				case LEX_MINUS:
					return LEX_MINUS;
				case LEX_STAR:
					return LEX_STAR;
				case LEX_DIRSLASH:
					return LEX_DIRSLASH;
				case LEX_REMDIV:
					return LEX_REMDIV;
				case LEX_LITERAL:
					return LEX_LITERAL;
				case LEX_DECLARE:
					return LEX_DECLARE;
				case LEX_MAIN:
					return LEX_MAIN;
				case LEX_INTEGER:
					return LEX_INTEGER;
				case LEX_STRING:
					return LEX_STRING;
				case LEX_FUNCTION:
					return LEX_FUNCTION;
				case LEX_RETURN:
					return LEX_RETURN;
				case LEX_OUT:
					return LEX_OUT;
				case LEX_ID:
					return LEX_ID;

				default:
					throw ERROR_THROW_IN(126, token.line, 0);
				}
			}
		}

	}


}