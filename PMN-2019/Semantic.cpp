#include "pch.h"
#include "Semantic.h"

void CallSemantic(LT::LexTable& lextable, IT::IdTable& idtable)
{
	Functions functions = Create(255);
	CheckTypeMatching(lextable, idtable);
	FillFunctions(functions, idtable);
	CheckFunParam(functions, idtable, lextable);
	CheckBuiltInFunParam(lextable, idtable);
	CheckReturnType(lextable, idtable);
	
}

void CheckTypeMatching(LT::LexTable& lextable, IT::IdTable& idtable)
{
	for (int i = 0; i < lextable.size; i++)
	{
		if (lextable.table[i].lexema == LEX_EQUAL)
		{
			if (idtable.table[lextable.table[i - 1].idxTI].idType != IT::IDTYPE::V && idtable.table[lextable.table[i - 1].idxTI].idType != IT::IDTYPE::P)
				throw ERROR_THROW_IN(148, lextable.table[i - 1].sn, 0);
			IT::IDDATATYPE type = idtable.table[lextable.table[i - 1].idxTI].idDataType;

			int indexB = 0;
			bool isFirst = true;
			IT::IDDATATYPE type1 = IT::IDDATATYPE::NON;

			switch (type)
			{
			case IT::IDDATATYPE::BOOL:											// Если слева стоит идентификатор bool
				
				while (lextable.table[i + indexB].lexema != LEX_SEMICOLON)
				{
					if (lextable.table[i + indexB].lexema == LEX_PLUS || lextable.table[i + indexB].lexema == LEX_MINUS
						|| lextable.table[i + indexB].lexema == LEX_DIRSLASH || lextable.table[i + indexB].lexema == LEX_STAR || lextable.table[i + indexB].lexema == LEX_REMDIV)
						throw ERROR_THROW_IN(602, lextable.table[i + indexB].sn, 0);

					if (lextable.table[i + indexB].lexema == LEX_ID || lextable.table[i + indexB].lexema == LEX_LITERAL)
					{
						if (isFirst)
						{
							type1 = idtable.table[lextable.table[i + indexB].idxTI].idDataType;
							isFirst = false;
						}

						if (idtable.table[lextable.table[i + indexB].idxTI].idDataType != type1)
							throw ERROR_THROW_IN(143, lextable.table[i + indexB].sn, 0);
					}

					
					indexB++;
					continue;
				}
				break;
			case IT::IDDATATYPE::STR:
				for (int j = 0; lextable.table[i + j].lexema != LEX_SEMICOLON; j++)
				{
					if (lextable.table[i + j].lexema == LEX_PLUS || lextable.table[i + j].lexema == LEX_MINUS
						|| lextable.table[i + j].lexema == LEX_DIRSLASH || lextable.table[i + j].lexema == LEX_STAR
						|| lextable.table[i + j].lexema == LEX_REMDIV || lextable.table[i + j].lexema == LEX_LESS
						|| lextable.table[i + j].lexema == LEX_GREAT || lextable.table[i + j].lexema == LEX_EQUALEQUAL
						|| lextable.table[i + j].lexema == LEX_NOTEQUAL)
						throw ERROR_THROW_IN(152, lextable.table[i + j].sn, 0);
					if (lextable.table[i + j].lexema == LEX_ID || lextable.table[i + j].lexema == LEX_LITERAL)
					{
						if (idtable.table[lextable.table[i + j].idxTI].idType == IT::IDTYPE::F)
						{
							if (idtable.table[lextable.table[i + j].idxTI].idDataType != type)
								throw ERROR_THROW_IN(143, lextable.table[i + j].sn, 0);
							int countOfHesis = 0;
							if (lextable.table[i + j + 1].lexema != LEX_LEFTHESIS)
								throw ERROR_THROW_IN(150, lextable.table[i + j].sn, 0);
							do
							{
								j++;
								if (lextable.table[i + j].lexema == LEX_LEFTHESIS)
									countOfHesis++;
								if (lextable.table[i + j].lexema == LEX_RIGHTHESIS)
									countOfHesis--;
							} while (countOfHesis != 0);
						}
						else if (idtable.table[lextable.table[i + j].idxTI].idDataType != type)
							throw ERROR_THROW_IN(143, lextable.table[i + j].sn, 0);

					}
						
				}

				break;
			case IT::IDDATATYPE::INT:															// Если слева стоит идентификатор string или dig
				int index = 0;
				while (lextable.table[i + index].lexema != LEX_SEMICOLON)
				{
					if (lextable.table[i + index].lexema == LEX_LESS || lextable.table[i + index].lexema == LEX_GREAT 
						|| lextable.table[i + index].lexema == LEX_EQUALEQUAL || lextable.table[i + index].lexema == LEX_NOTEQUAL)
						throw ERROR_THROW_IN(602, lextable.table[i + index].sn, 0);
					if (lextable.table[i + index].lexema == LEX_ID || lextable.table[i + index].lexema == LEX_LITERAL
						|| lextable.table[i + index].lexema == LEX_POW || lextable.table[i + index].lexema == LEX_ABS)
					{
						if (idtable.table[lextable.table[i + index].idxTI].idType == IT::IDTYPE::F)
						{
							if (idtable.table[lextable.table[i + index].idxTI].idDataType != type)
								throw ERROR_THROW_IN(143, lextable.table[i + index].sn, 0);
							int countOfHesis = 0;
							if (lextable.table[i + index + 1].lexema != LEX_LEFTHESIS)
								throw ERROR_THROW_IN(150, lextable.table[i + index].sn, 0);
							do
							{
								index++;
								if (lextable.table[i + index].lexema == LEX_LEFTHESIS)
									countOfHesis++;
								if (lextable.table[i + index].lexema == LEX_RIGHTHESIS)
									countOfHesis--;
							} while (countOfHesis != 0);
						}
						else if (lextable.table[i + index].lexema == LEX_POW || lextable.table[i + index].lexema == LEX_ABS)
						{
							if (type != IT::IDDATATYPE::INT)
								throw ERROR_THROW_IN(143, lextable.table[i + index].sn, 0);
							int countOfHesis = 0;
							do
							{
								index++;
								if (lextable.table[i + index].lexema == LEX_LEFTHESIS)
									countOfHesis++;
								if (lextable.table[i + index].lexema == LEX_RIGHTHESIS)
									countOfHesis--;
							} while (countOfHesis != 0);
						}
						else
						{
							if (idtable.table[lextable.table[i + index].idxTI].idDataType != type)
								throw ERROR_THROW_IN(143, lextable.table[i + index].sn, 0);
						}
					}
					index++;
					continue;
				}

				break;
			}
		}
	}
}

void FillFunctions(Functions& functions, IT::IdTable& idtable)
{
	for (int i = 0; i < idtable.size; i++)
	{
		if (idtable.table[i].idType == IT::IDTYPE::F)
		{
			Entry temp = {};
			temp.index = i;
			while (idtable.table[i + 1].idType == IT::IDTYPE::P)
			{
				if (temp.countOfParam > 8)
					throw ERROR_THROW_IN(144, idtable.table[i].idxfirstLE, 0)
				temp.types[temp.countOfParam] = idtable.table[i + 1].idDataType;
				temp.countOfParam++;
				i++;
			}
			Add(functions, temp);
		}
	}
}

void CheckFunParam(Functions& functions, IT::IdTable& idtable, LT::LexTable& lextable)
{
	bool isOkey = false;  // Была ли найдена ф-ция с таким же кол-вом и типами параметрам
	for (int i = 0; i < functions.size; i++)
	{
		for (int j = 0; j < lextable.size; j++)
		{
			if (lextable.table[j].idxTI == functions.table[i].index)
			{
				Entry temp = {};
				for (int k = 1; lextable.table[j + k].lexema != LEX_RIGHTHESIS; k++)
				{
					if (lextable.table[j + k].lexema == LEX_ID || lextable.table[j + k].lexema == LEX_LITERAL)
					{
						if (temp.countOfParam > 8)
							throw ERROR_THROW_IN(144, lextable.table[j].sn, 0);
						temp.types[temp.countOfParam] = idtable.table[lextable.table[j + k].idxTI].idDataType;
						temp.countOfParam++;
					}
				}
				if (!isEqual(temp, functions.table[i]))
					throw ERROR_THROW_IN(146, lextable.table[j].sn, 0);
			}
		}
	}
	

}

void CheckBuiltInFunParam(LT::LexTable& lextable, IT::IdTable& idtable)
{
	for (int i = 0; i < lextable.size; i++)
	{
		if (lextable.table[i].lexema == LEX_POW || lextable.table[i].lexema == LEX_POW)
		{
			int countOfParam = 0;
			int index = i;
			while (lextable.table[i + 1].lexema != LEX_RIGHTHESIS)
			{
				if (idtable.table[lextable.table[i + 1].idxTI].idDataType == IT::IDDATATYPE::STR)
					throw ERROR_THROW_IN(147, lextable.table[i].sn, 0);
				if (lextable.table[i + 1].lexema == LEX_ID || lextable.table[i + 1].lexema == LEX_LITERAL)
					countOfParam++;
				i++;
 			}
			switch (lextable.table[index].lexema)
			{
			case LEX_POW:
				if (countOfParam != 2)
					throw ERROR_THROW_IN(147, lextable.table[i].sn, 0);
				continue;
			case LEX_ABS:
				if (countOfParam != 1)
					throw ERROR_THROW_IN(147, lextable.table[i].sn, 0);
				continue;
			default:
				break;
			}
		}
	}
}

void CheckReturnType(LT::LexTable& lextable, IT::IdTable& idtable)
{
	for (int i = 0; i < idtable.size; i++)
	{
		if (idtable.table[i].idType == IT::IDTYPE::F)
		{
			for (int j = 1; j + idtable.table[i].idxfirstLE < lextable.size; j++)
			{
				if (lextable.table[idtable.table[i].idxfirstLE + j].lexema == LEX_RETURN)
					if (idtable.table[lextable.table[idtable.table[i].idxfirstLE + j + 1].idxTI].idDataType != idtable.table[i].idDataType)
						throw ERROR_THROW_IN(151, lextable.table[idtable.table[i].idxfirstLE + j].sn, 0);
				if (lextable.table[idtable.table[i].idxfirstLE + j].lexema == LEX_FUNCTION || lextable.table[idtable.table[i].idxfirstLE + j].lexema == LEX_MAIN)
					break;
			}
		}
	}
}

Functions Create(int size)
{
	if (size > 255)
		throw ERROR_THROW(1);

	Functions functions;
	functions.maxsize = size;
	functions.size = 0;
	functions.table = new Entry[functions.maxsize];

	return functions;
}

void Add(Functions& functions, Entry entry)
{
	if (functions.size > functions.maxsize)
		throw ERROR_THROW(145);

	functions.table[functions.size] = entry;
	functions.size++;
}

bool isEqual(Entry& entry1, Entry& entry2)
{
	if (entry1.countOfParam == entry2.countOfParam)
	{
		for (int i = 0; i < entry1.countOfParam; i++)
		{
			if (entry1.types[i] != entry2.types[i])
				return false;
		}
		return true;
	}
	else
		return false;
}