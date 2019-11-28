#include "pch.h"

namespace IT
{
	IdTable Create(int size)								//	Ф-ция создания таблицы идентификаторов
	{
		if (size > TI_MAXSIZE)								//	Ошибка, если size > TI_MAXSIZE
			throw ERROR_THROW(123);

		IdTable idtable;
		idtable.maxsize = size;								//	Создание таблицы идентификаторов
		idtable.size = 0;									//	Размер таблицы идентификаторов
		idtable.table = new Entry[idtable.maxsize];			//	Текущий размер таблица идентификаторов

		return idtable;										//	Возвращает заполненную структуру
	}

	void Add(IdTable& idtable, Entry entry)					//	Добавление строки в таблице идентификаторов
	{
		if (idtable.size > idtable.maxsize)					//	Проверка: есть ли свободное место в таблице идентификаторов
			throw ERROR_THROW(124);							//	Если нет, то ошибка

		idtable.table[idtable.size] = entry;				//	Добавление строки в таблицу под индексом = текущему размеру таблицы
		idtable.size++;										//	Увеличение текущего размера таблицы, т.к. была добавлена новая строка
	}

	Entry GetEntry(IdTable& idtable, int n)					//	Получение строки таблицы идентификатора
	{
		if (n > (idtable.size - 1))							//	Проверка: есть ли строка с таким номером входит в таблицу идентификаторов
			throw ERROR_THROW(125);							//	Если нет, то ошибка

		return idtable.table[n];							//	Возвращает строку таблицы идентификаторов
	}

	int IsId(IdTable& idtable, std::string id)
	{
		if (idtable.size > 0)								//	Проверка: есть ли в строки в таблице идентификаторов или она пустая
		{
			for (int i = 0; i < idtable.size; i++)			//	Перебирает все строки таблицы идентификаторов
			{
				if (idtable.table[i].id == id)
				{
					return i;
				}
			}
		}

		return TI_NULLIDX;									//	Возвращает, если строка не найдена
	}

	void Delete(IdTable& idtable)							//	Удаление таблицы идентификаторов (Освобождение памяти)
	{
		delete[] idtable.table;								//	Освобождение ранее выделенной памяти
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
		file << '|' << std::setfill(' ')  << std::setw(5) << std::left << "№" << '|' << std::setw(12) << std::left << "Name" << '|'
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