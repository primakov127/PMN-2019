#include "pch.h"

namespace LT
{
	LexTable Create(int size)								//	�-��� �������� ������� ������
	{
		if (size > LT_MAXSIZE)								//	������, ���� size > LT_MAXSIZE
			throw ERROR_THROW(120);

		LexTable lextable;									//	�������� ������� ������
		lextable.maxsize = size;							//	������ ������� ������
		lextable.size = 0;									//	������� ������ ������� ������
		lextable.table = new Entry[lextable.maxsize];		//	������ ����� ������ ������

		return lextable;									//	���������� ����������� ���������
	}

	void Add(LexTable& lextable, Entry entry)				//	���������� ������ � ������� ������
	{
		if (lextable.size > lextable.maxsize)				//	��������: ���� �� ��������� ����� � ������� ������
			throw ERROR_THROW(121);							//	���� ���, �� ������

		lextable.table[lextable.size] = entry;				//	���������� ������ � ������� ��� �������� = �������� ������� �������
		lextable.size++;									//	���������� �������� ������� �������, �.�. ���� ��������� ����� ������
	}

	Entry GetEntry(LexTable& lextable, int n)				//	��������� ������ ������� ������
	{
		if (n > (lextable.size - 1))						//	��������: ���� �� ������ � ����� ������� ������ � ������� ������
			throw ERROR_THROW(122);							//	���� ���, �� ������

		return lextable.table[n];							//	���������� ������ ������� ���������������
	}

	void Delete(LexTable& lextable)							//	�������� ������� ������ (������������ ������)
	{
		delete[] lextable.table;							//	������������ ����� ���������� ������
	}

	void SaveLexTableInFile(LexTable lextable, wchar_t outfile[])
	{
		std::ofstream out(outfile);
		if (!out.is_open())
			throw ERROR_THROW(114);

		int line = 0;
		out << std::right << std::setw(3) << line << "  ";
		for (int i = 0; i < lextable.size; i++)
		{
			if (lextable.table[i].sn == line)
			{
				out << lextable.table[i].lexema;
			}
			else
			{
				out << std::endl;
				line += (lextable.table[i].sn - line);
				out << std::right << std::setw(3) << line << "  " << lextable.table[i].lexema;

			}

		}

		out.close();
	}
}