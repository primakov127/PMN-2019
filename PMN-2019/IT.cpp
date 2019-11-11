#include "pch.h"

namespace IT
{
	IdTable Create(int size)								//	�-��� �������� ������� ���������������
	{
		if (size > TI_MAXSIZE)								//	������, ���� size > TI_MAXSIZE
			throw ERROR_THROW(123);

		IdTable idtable;
		idtable.maxsize = size;								//	�������� ������� ���������������
		idtable.size = 0;									//	������ ������� ���������������
		idtable.table = new Entry[idtable.maxsize];			//	������� ������ ������� ���������������

		return idtable;										//	���������� ����������� ���������
	}

	void Add(IdTable& idtable, Entry entry)					//	���������� ������ � ������� ���������������
	{
		if (idtable.size > idtable.maxsize)					//	��������: ���� �� ��������� ����� � ������� ���������������
			throw ERROR_THROW(124);							//	���� ���, �� ������

		idtable.table[idtable.size] = entry;				//	���������� ������ � ������� ��� �������� = �������� ������� �������
		idtable.size++;										//	���������� �������� ������� �������, �.�. ���� ��������� ����� ������
	}

	Entry GetEntry(IdTable& idtable, int n)					//	��������� ������ ������� ��������������
	{
		if (n > (idtable.size - 1))							//	��������: ���� �� ������ � ����� ������� ������ � ������� ���������������
			throw ERROR_THROW(125);							//	���� ���, �� ������

		return idtable.table[n];							//	���������� ������ ������� ���������������
	}

	int IsId(IdTable& idtable, std::string id)
	{
		if (idtable.size > 0)								//	��������: ���� �� � ������ � ������� ��������������� ��� ��� ������
		{
			for (int i = 0; i < idtable.size; i++)			//	���������� ��� ������ ������� ���������������
			{
				if (idtable.table[i].id == id)
				{
					return i;
				}
			}
		}

		return TI_NULLIDX;									//	����������, ���� ������ �� �������
	}

	void Delete(IdTable& idtable)							//	�������� ������� ��������������� (������������ ������)
	{
		delete[] idtable.table;								//	������������ ����� ���������� ������
	}
}