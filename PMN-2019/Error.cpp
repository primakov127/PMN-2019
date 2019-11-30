#include "pch.h"
#include "Error.h"
#include <iostream>
#include <cstring>

namespace Error
{
	// 0-99		 Cистемные ошибки САНЯ
	// 100-109	 Ошибки параметров
	// 110-119	 Ошибки открытия и чтения файлов
	// 120-129	 Ошибки заполнения таблиц Лексем и Идентификаторов
	// 130-139	 Ошибки заполнения таблицы токенов

	// Таблица ошибок
	ERROR errors[ERROR_MAX_ENTRY] =
	{
		// Код ошибки вне диапазона 0 - ERROR_MAX_ENTRY
		ERROR_ENTRY(0,"Недопустимый код ошибки"),
		ERROR_ENTRY(1,"Системный сбой"),
		ERROR_ENTRY_NODEF(2),ERROR_ENTRY_NODEF(3),ERROR_ENTRY_NODEF(4),ERROR_ENTRY_NODEF(5),
		ERROR_ENTRY_NODEF(6),ERROR_ENTRY_NODEF(7),ERROR_ENTRY_NODEF(8),ERROR_ENTRY_NODEF(9),
		ERROR_ENTRY_NODEF10(10),ERROR_ENTRY_NODEF10(20),ERROR_ENTRY_NODEF10(30),ERROR_ENTRY_NODEF10(40),ERROR_ENTRY_NODEF10(50),
		ERROR_ENTRY_NODEF10(60),ERROR_ENTRY_NODEF10(70),ERROR_ENTRY_NODEF10(80),ERROR_ENTRY_NODEF10(90),
		ERROR_ENTRY(100,"Параметр -in должен быть задан"),
		ERROR_ENTRY_NODEF(101),ERROR_ENTRY_NODEF(102),ERROR_ENTRY_NODEF(103),
		ERROR_ENTRY(104,"Превышена длинна входного параматра"),
		ERROR_ENTRY_NODEF(105),ERROR_ENTRY_NODEF(106),ERROR_ENTRY_NODEF(107),
		ERROR_ENTRY_NODEF(108),ERROR_ENTRY_NODEF(109),
		ERROR_ENTRY(110,"Ошибка при открытии файла с исходным кодом (-in)"),
		ERROR_ENTRY(111,"Недопустимый символ в исходном файле (-in)"),
		ERROR_ENTRY(112,"Ошибка при создании файла протокола (-log)"),
		ERROR_ENTRY(113,"Ошибка при открытии файла с таблицой токенов (-tkn)"),
		ERROR_ENTRY(114,"Ошибка при открытии файла с таблицой лексем (-lex)"),
		ERROR_ENTRY_NODEF(115),
		ERROR_ENTRY_NODEF(116),ERROR_ENTRY_NODEF(117),ERROR_ENTRY_NODEF(118),ERROR_ENTRY_NODEF(119),
		ERROR_ENTRY(120, "Превышена емкость таблицы лексем"),
		ERROR_ENTRY(121, "Превышено количество строк в таблице лексем"),
		ERROR_ENTRY(122, "В таблице лексем отсутствует строка с заданным номером"),
		ERROR_ENTRY(123, "Превышена емкость таблицы идентификаторов"),
		ERROR_ENTRY(124, "Превышено количество строк в таблице идентификаторов"),
		ERROR_ENTRY(125, "В таблице идентификаторов отсутствует строка с заданным номером"),
		ERROR_ENTRY(126, "Не удалось определить тип лексемы"),
		ERROR_ENTRY_NODEF(127),ERROR_ENTRY_NODEF(128),ERROR_ENTRY_NODEF(129),
		ERROR_ENTRY(130, "Превышена емкость таблицы токенов"),
		ERROR_ENTRY(131, "Превышено колличество токенов в таблице токенов"),
		ERROR_ENTRY(132, "Ошибка с разбиением исходного текста на токены"),
		ERROR_ENTRY(133, "Ошибка с разбором строкового литерала"),
		ERROR_ENTRY(134, "Неожиданный переход на новую строку"),
		ERROR_ENTRY(135, "Превышена длина строки в 255 символов"),
		ERROR_ENTRY(136, "Функция main уже имеет реализацию"),
		ERROR_ENTRY(137, "Превышена длина лексемы(идентификатора)"),
		ERROR_ENTRY(138, "Превышено значение INT (1 bite)"),
		ERROR_ENTRY(139, "Не найдена точка входа в программу (main)"),
		ERROR_ENTRY(140, "Идентификатор с таким именем не найден"),
		ERROR_ENTRY(141, "Повторное объявление индентификатора"),
		ERROR_ENTRY_NODEF(142),
		ERROR_ENTRY_NODEF(143), ERROR_ENTRY_NODEF(144), ERROR_ENTRY_NODEF(145),
		ERROR_ENTRY_NODEF(146), ERROR_ENTRY_NODEF(147), ERROR_ENTRY_NODEF(148),
		ERROR_ENTRY_NODEF(149),
		ERROR_ENTRY_NODEF10(150),
		ERROR_ENTRY_NODEF10(160),ERROR_ENTRY_NODEF10(170),ERROR_ENTRY_NODEF10(180),ERROR_ENTRY_NODEF10(190),
		ERROR_ENTRY_NODEF100(200),ERROR_ENTRY_NODEF100(300),ERROR_ENTRY_NODEF100(400),ERROR_ENTRY_NODEF100(500),
		ERROR_ENTRY(600, "Неверная структура программы"),
		ERROR_ENTRY(601, "Ошибочный оператор"),
		ERROR_ENTRY(602, "Ошибка в выражении"),
		ERROR_ENTRY(603, "Ошибка в параметрах функции"),
		ERROR_ENTRY(604, "Ошибка в параметрах вызываемой функции"),
		ERROR_ENTRY_NODEF(605), ERROR_ENTRY_NODEF(606), ERROR_ENTRY_NODEF(607), ERROR_ENTRY_NODEF(609),
		ERROR_ENTRY_NODEF10(610), ERROR_ENTRY_NODEF10(620), ERROR_ENTRY_NODEF10(630), ERROR_ENTRY_NODEF10(640),
		ERROR_ENTRY_NODEF10(660), ERROR_ENTRY_NODEF10(670), ERROR_ENTRY_NODEF10(680), ERROR_ENTRY_NODEF10(690),
		ERROR_ENTRY_NODEF100(700),ERROR_ENTRY_NODEF100(800),ERROR_ENTRY_NODEF100(900),
	};

	ERROR geterror(int id)
	{
		ERROR error_info;
		if (id > 0 && id < ERROR_MAXSIZE_MESSAGE)
		{
			error_info.id = errors[id].id;
			strcpy(error_info.message, errors[id].message);
			error_info.inext.col = -1;
			error_info.inext.line = -1;
		}
		else
		{
			error_info.id = errors[0].id;
			strcpy(error_info.message, errors[0].message);
		}
		return error_info;
	}

	ERROR geterrorin(int id, int line, int col)
	{
		ERROR error_info;
		if (id > 0 && id < ERROR_MAXSIZE_MESSAGE)
		{
			error_info.id = errors[id].id;
			error_info.inext.col = col + 1;
			error_info.inext.line = line + 1;
			strcpy(error_info.message, errors[id].message);
			return error_info;
		}
		else
		{
			error_info.id = 0;
			error_info.inext.col = -1;
			error_info.inext.line = -1;
			strcpy(error_info.message, errors[0].message);
			return error_info;
		}
	};
};