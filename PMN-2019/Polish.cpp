#include "pch.h"
#include "Polish.h"

using namespace std;

void CallPolishNotation(LT::LexTable& lextable, IT::IdTable& idtable)
{
	for (int i = 0; i < lextable.size; i++)
	{
		if (lextable.table[i].lexema == LEX_EQUAL && (idtable.table[lextable.table[i - 1].idxTI].idDataType != IT::IDDATATYPE::BOOL || idtable.table[lextable.table[i + 1].idxTI].idType == IT::IDTYPE::F))
		{
			polishNotation(++i, lextable, idtable);
		}
	}
}

void polishNotation(int lextable_pos, LT::LexTable& lextable, IT::IdTable& idtable)
{
	queue<LT::Entry> X;
	stack<LT::Entry> Y;
	LT::Entry forbidden = {'#', LT_TI_NULLTDX, LT_TI_NULLTDX};
	int countOfLex = 0;
	int posOfFirstLex = lextable_pos;

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
			if (idtable.table[lextable.table[lextable_pos].idxTI].idType == IT::IDTYPE::F)
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
			if (!Y.empty())
			{
				while (Y.top().lexema != LEX_LEFTHESIS)
				{
					X.push(Y.top());
					Y.pop();
				}
				Y.pop();	// Удаляем (
			}
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
			continue;
		}
	}
	while (!Y.empty())
	{
		X.push(Y.top());
		Y.pop();
	}

	for (int i = 0; i < countOfLex; i++)
	{
		if (!X.empty())
		{
			switch (X.front().lexema)
			{
			case LEX_ID:
				if (posOfFirstLex <= idtable.table[X.front().idxTI].idxfirstLE && idtable.table[X.front().idxTI].idxfirstLE < posOfFirstLex + countOfLex)		// Проверка является ли эта лексема первым вхождение в LT
				{
					lextable.table[posOfFirstLex + i] = X.front();
					idtable.table[X.front().idxTI].idxfirstLE = posOfFirstLex + i;									// Меняем индекс первого вхождения
					X.pop();
				}
				else
				{
					lextable.table[posOfFirstLex + i] = X.front();
					X.pop();
				}
				continue;
			case LEX_LITERAL:
				lextable.table[posOfFirstLex + i] = X.front();
				idtable.table[X.front().idxTI].idxfirstLE = posOfFirstLex + i;										// Меняем индекс первого вхождения
				X.pop();
				continue;
			case LEX_POW:
				lextable.table[posOfFirstLex + i] = X.front();
				X.pop();
				continue;
			case LEX_ABS:
				lextable.table[posOfFirstLex + i] = X.front();
				X.pop();
				continue;
			default:
				lextable.table[posOfFirstLex + i] = X.front();
				X.pop();
				continue;
			}
		}
		else
		{
			lextable.table[posOfFirstLex + i] = forbidden;
		}
	}	
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