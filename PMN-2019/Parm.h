#pragma once
#define PARM_IN L"-in:"						// Ключ для файла исходного кода
#define PARM_OUT L"-out:"					// Ключ для файла объектного кода
#define PARM_LOG L"-log:"					// Ключ для файла журнала
#define PARM_TKN L"-tkn:"					// Ключ для файла таблицы токенов
#define PARM_LEX L"-lex:"					// Ключ для файла таблицы лексем
#define PARM_MAX_SIZE 300					// Максимальная длина строки параметра
#define PARM_OUT_DEFAULT_EXT L".out"		// Расширение файла объектного кода по умолчанию
#define PARM_LOG_DEFAULT_EXT L".log"		// Расширение файла протокола по умолчанию
#define PARM_TKN_DEFAULT_EXT L".tkn"		// Расширение файла таблицы токенов по умолчанию
#define PARM_LEX_DEFAULT_EXT L".lex"		// Расширение файла таблицы лексем по умолчанию

namespace Parm								// Обработка входных параметров
{
	struct PARM								// Входные параметры
	{
		wchar_t in[PARM_MAX_SIZE];			// -in:	имя файла исходного кода
		wchar_t out[PARM_MAX_SIZE];			// -out: имя файла объектного кода
		wchar_t log[PARM_MAX_SIZE];			// -log: имя файла протокола
		wchar_t tkn[PARM_MAX_SIZE];			// -tkn: имя файла таблицы токенов
		wchar_t lex[PARM_MAX_SIZE];			// -lex: имя файла таблицы лексем
	};

	PARM getparm(int argc, _TCHAR* argv[]);	// Сформировать struct PARM на основе парметров функции main
}
