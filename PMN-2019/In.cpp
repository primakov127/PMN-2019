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
		IN Info{ 0, 0, 0, nullptr, IN_CODE_TABLE };									//uniform ������������� (������������ == ������ �������������)
		std::ifstream in(infile);													//��������� ���� ��� ������
		std::ofstream out(outfile);													//��������� ���� ��� ������
		if (!out.is_open())															//�������� �� �������� ����� ����� ������
			throw ERROR_THROW(110);
		if (!in.is_open())															//�������� �� �������� ����� ����� ������
			throw ERROR_THROW(110);
		std::string fulltext;
		std::string temp;
		while (!in.eof())															//���� ������ ����
		{
			Info.lines++;															//������� ���-�� �����

			std::getline(in, temp);													//������ ������ � t�mp
			temp += "\n";															//���� ��������� ������
			fulltext += temp;
		}
		Info.text = new unsigned char[fulltext.size() + 1];							//�������� ������ ��� ������
		unsigned char * Ptemp = Info.text;											//��������� �� ������� ������
		for (int i = 0; i < fulltext.size(); ++i)
		{
			if (Info.code[(unsigned char)fulltext[i]] == IN::F)						//���� ���� ������ => ������
			{
				throw ERROR_THROW_IN(111, currentLine, currentCol)
			}
			else if (Info.code[(unsigned char)fulltext[i]] == IN::I)				// ���� ����� ������ 
				++Info.ignor;
			else if (Info.code[(unsigned char)fulltext[i]] == IN::T)				// ���� ����������� ������ 
			{
				*Ptemp = fulltext[i];
				++Ptemp;
			}
			else																	//���� �� ������ ������ ,  ������ ������� ����� ���� �� 1 (������ �������)
			{
				*Ptemp = Info.code[(unsigned char)fulltext[i]];
				++Ptemp;
			}
			if (fulltext[i] == '\n')												//���� ����� ������, ������ ������� ������ �� 1 
			{
				++currentLine;
				currentCol = 0;
			}
			else
				++currentCol;
		}
		*Ptemp = IN_CODE_ENDL;														//������� ����� ������
		Info.size = strlen((char*)Info.text) - Info.lines;							//���������� ������� = ���������� ���� ���� - \n
		//out << Info.text;
		// LAB 13
		//int j = 0;
		//for (short i = 0; i < Info.lines; i++)
		//{
		//	short count = 0;														// ���������� ��� �������� ���-�� ������� � ������
		//	while (1)																// ������� ���-�� ��������
		//	{
		//		/*if (Info.text[j] == '|')
		//			break;*/
		//		if (Info.text[j] == '\n')
		//			break;
		//		count++;
		//		j++;
		//	}
		//	j = j - count;															// ������� � ������ �����
		//	char *str = new char[count + 1];										// ������� ������ ��� ������

		//	for (short k = 0; k < count; k++)										// �������� ������ �� ������
		//	{
		//		str[k] = Info.text[j];
		//		j++;
		//	}
		//	j++;																	// ����������� �� ��������� �����
		//	str[count] = '\0';


		//	FST::FST fst1(
		//		str,
		//		25,
		//		FST::NODE(1, FST::RELATION('m', 1)),														// ��������� 0 (���������)
		//		FST::NODE(1, FST::RELATION('a', 2)),														// ��������� 1
		//		FST::NODE(1, FST::RELATION('i', 3)),														// ��������� 2
		//		FST::NODE(1, FST::RELATION('n', 4)),														// ��������� 3
		//		FST::NODE(3, FST::RELATION(' ', 4), FST::RELATION(' ', 5), FST::RELATION(' ', 16)),			// ��������� 4
		//		FST::NODE(2, FST::RELATION('w', 6), FST::RELATION('s', 7)),									// ��������� 5
		//		FST::NODE(1, FST::RELATION('a', 8)),														// ��������� 6
		//		FST::NODE(2, FST::RELATION('h', 9), FST::RELATION('e', 10)),								// ��������� 7
		//		FST::NODE(1, FST::RELATION('i', 11)),														// ��������� 8
		//		FST::NODE(1, FST::RELATION('o', 12)),														// ��������� 9
		//		FST::NODE(1, FST::RELATION('n', 13)),														// ��������� 10
		//		FST::NODE(1, FST::RELATION('t', 14)),														// ��������� 11
		//		FST::NODE(1, FST::RELATION('w', 14)),														// ��������� 12
		//		FST::NODE(1, FST::RELATION('d', 14)),														// ��������� 13
		//		FST::NODE(1, FST::RELATION(';', 15)),														// ��������� 14
		//		FST::NODE(3, FST::RELATION(' ', 5), FST::RELATION(' ', 15), FST::RELATION(' ', 16)),		// ��������� 15
		//		FST::NODE(2, FST::RELATION(' ', 16), FST::RELATION(' ', 17)),								// ��������� 16
		//		FST::NODE(1, FST::RELATION('r', 18)),														// ��������� 17
		//		FST::NODE(1, FST::RELATION('e', 19)),														// ��������� 18
		//		FST::NODE(1, FST::RELATION('t', 20)),														// ��������� 19
		//		FST::NODE(1, FST::RELATION('u', 21)),														// ��������� 20
		//		FST::NODE(1, FST::RELATION('r', 22)),														// ��������� 21
		//		FST::NODE(1, FST::RELATION('n', 23)),														// ��������� 22
		//		FST::NODE(1, FST::RELATION(';', 24)),														// ��������� 23
		//		FST::NODE()																					// ��������� 24 (��������)
		//	);

		//	if (FST::execute(fst1))																			// ������ � ����
		//		out << "������� " << str << " ����������\n";
		//	else out << "������� " << str << " �� ����������\n";


		//	delete[] str;

		//}

		out.close();
		in.close();
		return Info;
	}
}

