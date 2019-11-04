#pragma once
#include <fstream>
#include "In.h"
#include "Parm.h"
#include "Error.h"

	// Работа с протоколом
namespace Log
{
	struct LOG										//	Протокол
	{
		wchar_t logfile[PARM_MAX_SIZE];				//	Имя файла протокола
		std::ofstream* stream;						//	Выходной поток протокола
	};

	// Структура начальной инициализации LOG
	static const LOG INITLOG = { L"",NULL };		
	// Ф-ция создания структуры LOG
	LOG getlog(wchar_t logfile[]);					
	// Ф-ция вывода конкатинации строк в протокол
	void WriteLine(LOG log, const char* c, ...);
	// Ф-ция вывода конкатенации строк в протокол
	void WriteLine(LOG, const wchar_t* c, ...);
	// Ф-ция вывода заголовока в протокол
	void WriteLog(LOG log);
	// Ф-ция вывода информацию о входных параметров в протокол
	void WriteParm(LOG log, Parm::PARM parm);
	// Ф-ция вывода информации о входном потоке в протокол 
	void WriteIn(LOG log, In::IN in);
	// Ф-ция вывода информацию об ошибке в протокол 
	void WriteError(LOG log, Error::ERROR error);
	// Ф-ция закрытия протокола	
	void Close(LOG log);	


}