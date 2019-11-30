#include "pch.h"
#include "Polish.h"

using namespace std;

#define OPERATOR_CASE	if (!Y.empty()) \
						{ \
							while (priorityIs(lextable.table[lextable_pos]) < priorityIs(Y.top()) || Y.top().lexema != LEX_LEFTHESIS)\
							{\
								X.push(Y.top()); \
								Y.pop(); \
							}\
							continue; \
						} \
						

void CallPolishNotation(LT::LexTable& lextable, IT::IdTable& idtable)
{
	for (int i = 0; i < lextable.size; i++)
	{
		if (lextable.table[i].lexema == LEX_EQUAL)
		{
			polishNotation(++i, lextable, idtable);
		}
	}
}

void polishNotation(int lextable_pos, LT::LexTable& lextable, IT::IdTable& idtable)
{
	queue<LT::Entry> X;
	stack<LT::Entry> Y;
	int count = 0;
	bool checker = false;
	int curLine = 0;
	int countOfLex = 0;
	int posOfFirstLex = lextable_pos;
	bool logic = true;

	for (lextable_pos; lextable.table[lextable_pos].lexema != LEX_SEMICOLON; lextable_pos++, countOfLex++)
	{
		switch (lextable.table[lextable_pos].lexema)
		{
		case LEX_POW:
		{
			Y.push(lextable.table[lextable_pos]);
			continue;
		}
		case LEX_ABS:
		{
			Y.push(lextable.table[lextable_pos]);
			continue;
		}
		case LEX_ID:
		{
			if (idtable.table[lextable.table[lextable_pos].idxTI].idType == IT::IDTYPE::F) // Если ф-ция
			{
				Y.push(lextable.table[lextable_pos]);
				continue;
			}
			X.push(lextable.table[lextable_pos]);
			continue;
		}
		case LEX_LITERAL:
		{
			X.push(lextable.table[lextable_pos]);
			continue;
		}
		case LEX_LEFTHESIS:
		{
			Y.push(lextable.table[lextable_pos]);
			continue;
		}
		case LEX_RIGHTHESIS:
		{
			while (Y.top().lexema != LEX_LEFTHESIS)
			{
				X.push(Y.top());
				Y.pop();
			}
			Y.pop();	// Удаляем (
			//if (Y.top().lexema == 'p' || Y.top().lexema == 'a' || idtable.table[Y.top().idxTI].idType == IT::IDTYPE::F)
			//{
			//	X.push(Y.top());
			//	//Y.pop();
			//}

			continue;
		}
		case LEX_PLUS:
			if (!Y.empty())
			{
				while (priorityIs(lextable.table[lextable_pos]) < priorityIs(Y.top()) || Y.top().lexema == 'p' || Y.top().lexema == 'a' || idtable.table[Y.top().idxTI].idType == IT::IDTYPE::F)
				{
					X.push(Y.top());
					Y.pop();
					if (Y.empty())
						break;
				}
			}
			Y.push(lextable.table[lextable_pos]);
			continue;
		case LEX_MINUS:
			if (!Y.empty())
			{
				while (priorityIs(lextable.table[lextable_pos]) < priorityIs(Y.top()) || Y.top().lexema == 'p' || Y.top().lexema == 'a' || idtable.table[Y.top().idxTI].idType == IT::IDTYPE::F)
				{
					X.push(Y.top());
					Y.pop();
					if (Y.empty())
						break;
				}
			}
			Y.push(lextable.table[lextable_pos]);
			continue;
		case LEX_STAR:
			if (!Y.empty())
			{
				while (priorityIs(lextable.table[lextable_pos]) < priorityIs(Y.top()) || Y.top().lexema == 'p' || Y.top().lexema == 'a' || idtable.table[Y.top().idxTI].idType == IT::IDTYPE::F)
				{
					X.push(Y.top());
					Y.pop();
					if (Y.empty())
						break;
				}
			}
			Y.push(lextable.table[lextable_pos]);
			continue;
		case LEX_DIRSLASH:
			if (!Y.empty())
			{
				while (priorityIs(lextable.table[lextable_pos]) < priorityIs(Y.top()) || Y.top().lexema == 'p' || Y.top().lexema == 'a' || idtable.table[Y.top().idxTI].idType == IT::IDTYPE::F)
				{
					X.push(Y.top());
					Y.pop();
					if (Y.empty())
						break;
				}
			}
			Y.push(lextable.table[lextable_pos]);
			continue;
		case LEX_REMDIV:
			if (!Y.empty())
			{
				while (priorityIs(lextable.table[lextable_pos]) < priorityIs(Y.top()) || Y.top().lexema == 'p' || Y.top().lexema == 'a' || idtable.table[Y.top().idxTI].idType == IT::IDTYPE::F)
				{
					X.push(Y.top());
					Y.pop();
					if (Y.empty())
						break;
				}
			}
			Y.push(lextable.table[lextable_pos]);
			continue;
		case LEX_COMMA:
			while (Y.top().lexema != LEX_LEFTHESIS)
			{
				X.push(Y.top());
				Y.pop();
			}
			continue;
		default:
			break;
		}
	}
	while (!Y.empty())
	{
		X.push(Y.top());
		Y.pop();
	}

	while (!X.empty())
	{
		cout << X.front().lexema;
		X.pop();
	}
	cout << endl;
	
}

int priorityIs(LT::Entry entry)
{
	switch (entry.lexema)
	{
	case LEX_LEFTHESIS:
		return 0;
	case LEX_RIGHTHESIS:
		return 0;
	case LEX_COMMA:
		return 1;
	case LEX_PLUS:
		return 2;
	case LEX_MINUS:
		return 2;
	case LEX_STAR:
		return 3;
	case LEX_DIRSLASH:
		return 3;
	case LEX_REMDIV:
		return 3;

	default:
		return -1;
	}
}

char intToChar(int x)
{
	switch (x)
	{
	case 0: return '0';
	case 1: return '1';
	case 2: return '2';
	case 3: return '3';
	case 4: return '4';
	case 5: return '5';
	case 6: return '6';
	case 7: return '7';
	case 8: return '8';
	case 9: return '9';
	default: return '\0';
	}
}
