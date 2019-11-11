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
}