#include "pch.h"
using namespace std;

namespace Lex
{
	LEX::LEX(int lexTableSize, int idTableSize)
	{
		this->lextable = LT::Create(lexTableSize);
		this->idtable = IT::Create(idTableSize);
	}

	GRAPH graph[] =
	{
		{ LEX_INTEGER, FST::FST(GRAPH_INTEGER) },
		{ LEX_STRING, FST::FST(GRAPH_STRING) },
		{ LEX_FUNCTION, FST::FST(GRAPH_FUNCTION) },
		{ LEX_DECLARE, FST::FST(GRAPH_DECLARE) },
		{ LEX_RETURN, FST::FST(GRAPH_RETURN) },
		{ LEX_OUT, FST::FST(GRAPH_OUT) },
		{ LEX_MAIN, FST::FST(GRAPH_MAIN) },
		{ LEX_LITERAL, FST::FST(GRAPH_INT_LITERAL) },
		{ LEX_LITERAL, FST::FST(GRAPH_STRING_LITERAL) },
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
		{ LEX_REMDIV, FST::FST(GRAPH_REMDIV) },
		{ LEX_EQUAL, FST::FST(GRAPH_EQUALS) },
		{ LEX_IF, FST::FST(GRAPH_IF) },
		{ LEX_THEN, FST::FST(GRAPH_THEN) },
		{ LEX_ELSE, FST::FST(GRAPH_ELSE) },
		{ LEX_ID, FST::FST(GRAPH_ID) }
	};

	
	char lexType(TOKEN::Token token)
	{
		for (int i = 0; i < LENGTHOF(graph); i++)
		{
			FST::FST fstlex = FST::FST(token.token, graph[i].graph);
			if (FST::execute(fstlex))
			{
				return graph[i].lex;
			}
		}
		throw ERROR_THROW_IN(126, token.line, 0);
	}

	LEX fillingInTables(TOKEN::TokenTable tokenTable)
	{
		LEX lex = LEX(4096, 4096);
		char lexema;										// Лексема для LT
		string id;											// id для IT
		int lineIT = TI_NULLIDX;											// Индекс в IT
		stack<int> areaOfVisibility;						// Стек с областями видимости
		areaOfVisibility.push(0);
		stack<int> restoringAreaOfVis;
		int globalAreaOfVisibility = 0;						// Текущая глобальная область видимости
		char *currentVisibility = new char[0];				// ?
		IT::IDTYPE idType = IT::IDTYPE::P;					// Тип идентификатора для IT
		IT::IDDATATYPE idDataType = IT::IDDATATYPE::NON;	// Тип данных для IT
		int isNotGlobal = 0;								// Если isNotGlobal = 0 => Область видимости глобальная
		bool isMain = false;								// Есть ли ф-ция main
		int numOfLit = 0;
		bool isDeclare = false;

		for (int index = 0; index < tokenTable.size; index++)
		{
			switch (lexema = lexType(tokenTable.table[index]))
			{
			case LEX_ID:
				lineIT = searchID(areaOfVisibility, string(tokenTable.table[index].token), lex.idtable);
				if (lineIT == TI_NULLIDX || isDeclare)
				{
					lineIT = lex.idtable.size;
					id = string(tokenTable.table[index].token) + to_string(areaOfVisibility.top());
					IT::Add(lex.idtable, IT::createEntry(lex.lextable.size, id, idDataType, idType));
				}
				// Проверка повторного объявления

				LT::Add(lex.lextable, LT::createEntry(lexema, tokenTable.table[index].line, lineIT));
				idType = IT::IDTYPE::P;
				idDataType = IT::IDDATATYPE::NON;
				break;
			case LEX_LITERAL:
				if (tokenTable.table[index].token[0] == '\'')
				{
					id = "str" + to_string(numOfLit++);
					IT::Add(lex.idtable, IT::createEntry(lex.lextable.size, id, IT::IDDATATYPE::STR, IT::IDTYPE::L, string(tokenTable.table[index].token)));
				}
				else
				{
					id = "int" + to_string(numOfLit++);
					int vint = atoi(tokenTable.table[index].token);
					if (vint > INT8_MAX)
						throw ERROR_THROW_IN(138, tokenTable.table[index].line, tokenTable.table[index].linePosition);
					IT::Add(lex.idtable, IT::createEntry(lex.lextable.size, id, IT::IDDATATYPE::INT, IT::IDTYPE::L, atoi(tokenTable.table[index].token)));
					// max value = int(bite)
				}
				LT::Add(lex.lextable, LT::createEntry(lexema, tokenTable.table[index].line, lex.idtable.size - 1));
				break;
			default:
				LT::Add(lex.lextable, LT::createEntry(lexema, tokenTable.table[index].line));

				switch (lexema)
				{
				case LEX_LEFTBRACE:
					areaOfVisibility.push(lex.lextable.size - 1);
					isNotGlobal++;
					break;
				case LEX_RIGHTBRACE:
					areaOfVisibility.pop();
					isNotGlobal--;
					break;
				case LEX_INTEGER:
					idDataType = IT::IDDATATYPE::INT;
					break;
				case LEX_STRING:
					idDataType = IT::IDDATATYPE::STR;
					break;
				case LEX_DECLARE:
					idType = IT::IDTYPE::V;
					isDeclare = true;
					break;
				case LEX_FUNCTION:
					idType = IT::IDTYPE::F;
					if (!isNotGlobal)
					{
						globalAreaOfVisibility++;
						if (areaOfVisibility.top() != 0)
							areaOfVisibility.pop();
					}
					

					areaOfVisibility.push(globalAreaOfVisibility);
					break;
				case LEX_MAIN:
					if (isMain)
						throw ERROR_THROW_IN(136, tokenTable.table[index].line, tokenTable.table[index].linePosition);
					isMain = true;
					break;
				case LEX_SEMICOLON:
					isDeclare = false;
					break;
				default:
					break;
				}

				break;
			}
		}
		if (!isMain)
			throw ERROR_THROW_IN(139, -1, -1);
		return lex;
	}

	int searchID(stack<int> areaOfVisibility, string id, IT::IdTable& idtable)
	{
		char* currentVisibility = new char[0];
		string searchingID;
		int result = TI_NULLIDX;
		while (areaOfVisibility.top() != 0)
		{
			itoa(areaOfVisibility.top(), currentVisibility, 10);
			areaOfVisibility.pop();
			searchingID = id + string(currentVisibility);
			result = IT::IsId(idtable, searchingID);
			if (result != TI_NULLIDX)
				return result;
		}
		return result;
	}
	
}