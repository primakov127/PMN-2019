#include "pch.h"
#include "In.h"
#include "Error.h"
#include "FST.h"
#include <fstream>
#include <string>
#include <iostream>

namespace In
{

	IN getin(wchar_t infile[], wchar_t outfile[])
	{
		int currentLine = 0, currentCol = 0;
		IN Info{ 0, 0, 0, nullptr, IN_CODE_TABLE };									//uniform инициализация (альтернатива == списки инициализации)
		std::ifstream in(infile);													//открывает файл для чтения
		std::ofstream out(outfile);													//открывает файл для записи
		if (!out.is_open())															//проверка на открытие файла иначе ошибка
			throw ERROR_THROW(110);
		if (!in.is_open())															//проверка на открытие файла иначе ошибка
			throw ERROR_THROW(110);
		std::string fulltext;
		std::string temp;
		while (!in.eof())															//пока открыт файл
		{
			Info.lines++;															//считаем кол-во линий

			std::getline(in, temp);													//запись строки в tеmp
			temp += "\n";															//знак окончания строки
			fulltext += temp;
		}
		Info.text = new unsigned char[fulltext.size() + 1];							//выделяем память для текста
		unsigned char * Ptemp = Info.text;											//указатель на участок пямати
		for (int i = 0; i < fulltext.size(); ++i)
		{
			if (Info.code[(unsigned char)fulltext[i]] == IN::F)						//Если запр символ => ошибка
			{
				throw ERROR_THROW_IN(111, currentLine, currentCol)
			}
			else if (Info.code[(unsigned char)fulltext[i]] == IN::I)				// Если игнор символ 
				++Info.ignor;
			else if (Info.code[(unsigned char)fulltext[i]] == IN::T)				// Если разрешенный символ 
			{
				*Ptemp = fulltext[i];
				++Ptemp;
			}
			else																	//Если не указан символ ,  увелич счетчик игнор элем на 1 (замена символа)
			{
				*Ptemp = Info.code[(unsigned char)fulltext[i]];
				++Ptemp;
			}
			if (fulltext[i] == '\n')												//если конец строки, увелич счетчик строки на 1 
			{
				++currentLine;
				currentCol = 0;
			}
			else
				++currentCol;
		}
		*Ptemp = IN_CODE_ENDL;														//признак конца строки
		Info.size = strlen((char*)Info.text) - Info.lines;							//количество символо = количество всех элем - \n
		//out << Info.text;
		// LAB 13
		//int j = 0;
		//for (short i = 0; i < Info.lines; i++)
		//{
		//	short count = 0;														// переменная для подсчета кол-ва сиволов в строке
		//	while (1)																// подсчет кол-ва символов
		//	{
		//		/*if (Info.text[j] == '|')
		//			break;*/
		//		if (Info.text[j] == '\n')
		//			break;
		//		count++;
		//		j++;
		//	}
		//	j = j - count;															// возврат к началу слова
		//	char *str = new char[count + 1];										// создаем массив для строки

		//	for (short k = 0; k < count; k++)										// копируем строку из текста
		//	{
		//		str[k] = Info.text[j];
		//		j++;
		//	}
		//	j++;																	// перемещение на следующее слово
		//	str[count] = '\0';


		//	FST::FST fst1(
		//		str,
		//		25,
		//		FST::NODE(1, FST::RELATION('m', 1)),														// состояние 0 (начальное)
		//		FST::NODE(1, FST::RELATION('a', 2)),														// состояние 1
		//		FST::NODE(1, FST::RELATION('i', 3)),														// состояние 2
		//		FST::NODE(1, FST::RELATION('n', 4)),														// состояние 3
		//		FST::NODE(3, FST::RELATION(' ', 4), FST::RELATION(' ', 5), FST::RELATION(' ', 16)),			// состояние 4
		//		FST::NODE(2, FST::RELATION('w', 6), FST::RELATION('s', 7)),									// состояние 5
		//		FST::NODE(1, FST::RELATION('a', 8)),														// состояние 6
		//		FST::NODE(2, FST::RELATION('h', 9), FST::RELATION('e', 10)),								// состояние 7
		//		FST::NODE(1, FST::RELATION('i', 11)),														// состояние 8
		//		FST::NODE(1, FST::RELATION('o', 12)),														// состояние 9
		//		FST::NODE(1, FST::RELATION('n', 13)),														// состояние 10
		//		FST::NODE(1, FST::RELATION('t', 14)),														// состояние 11
		//		FST::NODE(1, FST::RELATION('w', 14)),														// состояние 12
		//		FST::NODE(1, FST::RELATION('d', 14)),														// состояние 13
		//		FST::NODE(1, FST::RELATION(';', 15)),														// состояние 14
		//		FST::NODE(3, FST::RELATION(' ', 5), FST::RELATION(' ', 15), FST::RELATION(' ', 16)),		// состояние 15
		//		FST::NODE(2, FST::RELATION(' ', 16), FST::RELATION(' ', 17)),								// состояние 16
		//		FST::NODE(1, FST::RELATION('r', 18)),														// состояние 17
		//		FST::NODE(1, FST::RELATION('e', 19)),														// состояние 18
		//		FST::NODE(1, FST::RELATION('t', 20)),														// состояние 19
		//		FST::NODE(1, FST::RELATION('u', 21)),														// состояние 20
		//		FST::NODE(1, FST::RELATION('r', 22)),														// состояние 21
		//		FST::NODE(1, FST::RELATION('n', 23)),														// состояние 22
		//		FST::NODE(1, FST::RELATION(';', 24)),														// состояние 23
		//		FST::NODE()																					// состояние 24 (конечное)
		//	);

		//	if (FST::execute(fst1))																			// запись в файл
		//		out << "Цепочка " << str << " распознана\n";
		//	else out << "Цепочка " << str << " не распознана\n";


		//	delete[] str;

		//}

		out.close();
		in.close();
		return Info;
	}
}

