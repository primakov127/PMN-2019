#pragma once

#define TI_MAXSIZE      4096                    // Максимальное количество строк в таблице идентификаторов
#define TI_INT_DEFAULT  0x00000000              // Значение по умолчанию для типа integer
#define TI_STR_DEFAULT  0x00                    // Значение по умолчанию для типа string
#define TI_NULLIDX      0xffffffff              // Нет элемента таблицы идентификаторов
#define TI_STR_MAXSIZE  255                     // Максимальный размер строки

namespace IT                                    // Таблица идентификаторов
{
	enum IDDATATYPE { INT = 1, STR = 2 };					// типы данных идентификаторов: integer, string
	enum IDTYPE { V = 1, F = 2, P = 3, L = 3 };				// типы идентификаторов: переменная, функция, параметр, литерал

	struct Entry                                // Строка таблицы идентификаторов
	{
		int         idxfirstLE;                 // Индекс первого вхождения в таблице лексем
		std::string id;							// Идентификатор
		IDDATATYPE  iddatatype;                 // Тип данных
		IDTYPE      idtype;                     // Тип идентификаторов
		struct
		{
			int vint;                           // Значение integer
			struct
			{
				char len;                       // Количество символов в string
				std::string str;				// Символы string
			} vstr;								// Значение string
		} value;                                // Значение идентификатора
	};

	struct IdTable                              // Экземпляр таблицы идентификаторов
	{
		int maxsize;                            // Емкость таблицы идентификаторов < TI_MAXSIZE
		int size;                               // Текущий размер таблицы идентификаторов < maxsize
		Entry* table;                           // Массив строк таблицы идентификаторов
	};

	IdTable Create(                             // Создать таблицу идентификаторов
		int size                                // Емкость таблицы идентификаторов < TI_MAXSIZE
	);

	void Add(                                   // Добавить строку в таблицу идентификаторов
		IdTable& idtable,                       // Экземпляр таблицы идентификаторов
		Entry entry                             // Строка таблицы идентификаторов
	);

	Entry GetEntry(                             // Получить строку таблицы идентификаторов
		IdTable& idtable,                       // Экземпляр таблицы идентификаторов
		int n                                   // Номер получаемой строки
	);

	int IsId(                                   // Возврат: номер строки (если есть), TI_NULLDX(если нет)
		IdTable& idtable,                       // Экземпляр таблицы идентификаторов
		std::string id							// Идентификатор
	);

	void Delete(IdTable& idtable);              // Удалить таблицу лексем (освободить память)
}