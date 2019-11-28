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

	Entry createEntry(int lineLT, std::string id, IDDATATYPE idDataType, IDTYPE idType)
	{
		Entry result;
		result.idxfirstLE = lineLT;
		result.id = id;
		result.idDataType = idDataType;
		result.idType = idType;
		return result;
	}

	Entry createEntry(int lineLT, std::string id, IDDATATYPE idDataType, IDTYPE idType, int vint)
	{
		Entry result;
		result.idxfirstLE = lineLT;
		result.id = id;
		result.idDataType = idDataType;
		result.idType = idType;
		result.value.vint = vint;
		return result;
	}

	Entry createEntry(int lineLT, std::string id, IDDATATYPE idDataType, IDTYPE idType, std::string vstr)
	{
		Entry result;
		result.idxfirstLE = lineLT;
		result.id = id;
		result.idDataType = idDataType;
		result.idType = idType;
		result.value.vstr.str = vstr;
		result.value.vstr.len = vstr.size();
		return result;
	}

	void showTable(IdTable& idtable, wchar_t outfile[])
	{
		std::ofstream file(outfile);
		if (!file.is_open())
			throw ERROR_THROW(114);

		int iddatatype;
		int idtype;
		int counter = 0;

		file << std::setfill('=') << std::setw(43) << "ID TABLE" << std::setw(40) << "\n\n";
		file << '+' << std::setfill('-') << std::setw(6) << '+' << std::setw(13) << '+' << std::setw(16) << '+' << std::setw(16) << '+'
			<< std::setw(16) << '+' << std::setw(13) << '+' << std::endl;
		file << '|' << std::setfill(' ')  << std::setw(5) << std::left << "�" << '|' << std::setw(12) << std::left << "Name" << '|'
			<< std::setw(15) << std::left << "Type" << '|' << std::setw(15) << std::left << "Data type" << '|' <<
			std::setw(15) << std::left << "First in LT" << '|' << std::setw(12) << std::left << "Value" << '|' << std::endl;

		for (int i = 0; i < idtable.size; i++)
		{
			iddatatype = idtable.table[i].idDataType;
			idtype = idtable.table[i].idType;
			file << '|' << std::setfill(' ') << std::setw(5) << std::left << i;
			file << '|' << std::setfill(' ') << std::setw(12) << std::left << idtable.table[i].id;// << std::setw(15);


			switch (idtype)
			{
			case IDTYPE::F:
				file << '|' << std::setw(15) << std::left << "Function";
				break;
			case IDTYPE::V:
				file << '|' << std::setw(15) << std::left << "Variable";
				break;
			case IDTYPE::P:
				file << '|' << std::setw(15) << std::left << "Patameter";
				break;
			case IDTYPE::L:
				file << '|' << std::setw(15) << std::left << "Literal";
				break;
			case IDTYPE::N:
				file << '|' << std::setw(15) << std::left << "NuN";
				break;
			}

			switch (iddatatype)
			{
			case IDDATATYPE::STR:
				file << '|' << std::setw(15) << std::left << "String";
				break;
			case IDDATATYPE::INT:
				file << '|' << std::setw(15) << std::left << "Integer";
				break;
			case IDDATATYPE::BOOL:
				file << '|' << std::setw(15) << std::left << "Bool";
				break;
			case IDDATATYPE::NON:
				file << '|' << std::setw(15) << std::left << "NuN";
				break;
			}

			file << '|' << std::setw(15) << std::left << idtable.table[i].idxfirstLE;

			if (idtype == IDTYPE::L)
			{
				switch (iddatatype)
				{
				case IDDATATYPE::INT:
					file << '|' << std::setw(12) << std::left << idtable.table[i].value.vint;
					break;
				case IDDATATYPE::STR:
					file << '|' << std::setw(12) << std::left << idtable.table[i].value.vstr.str;
					break;
				}
			}
			else
			{
				file << '|' << std::setw(12) << std::left << '-';
			}


			file << '|';
			file << std::endl;
			
		}
		//file << std::setw(25) << std::setfill('-') << std::setw(25);
		
		file.close();
	}
}