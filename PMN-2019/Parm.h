#pragma once
#define PARM_IN L"-in:"						//ключ для файла исходного кода
#define PARM_OUT L"-out:"					//ключ для файла объектного кода
#define PARM_LOG L"-log:"					//ключ для файла журнала
#define PARM_TKN L"-tkn:"					//ключ для файла таблицы токенов
#define PARM_MAX_SIZE 300					//максимальная длина строки параметра
#define PARM_OUT_DEFAULT_EXT L".out"		//расширение файла объектного кода по умолчанию
#define PARM_LOG_DEFAULT_EXT L".log"		//расширение файла протокола по умолчанию
#define PARM_TKN_DEFAULT_EXT L".tkn"		//расширение файла таблицы токенов по умолчанию

namespace Parm								//обработка входных параметров
{
	struct PARM								//входные параметры
	{
		wchar_t in[PARM_MAX_SIZE];			//-in:	имя файла исходного кода
		wchar_t out[PARM_MAX_SIZE];			//-out:	имя файла объектного кода
		wchar_t log[PARM_MAX_SIZE];			//-log:	имя файла протокола
		wchar_t tkn[PARM_MAX_SIZE];			//-tkn: имя файла таблицы токенов
	};

	PARM getparm(int argc, _TCHAR* argv[]);	//сформировать struct PARM на основе парметров функции main
}
