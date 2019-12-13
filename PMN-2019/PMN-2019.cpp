#include "pch.h"
#include <locale>
#include <cwchar>
			


int _tmain(int argc, _TCHAR ** argv)
{
	setlocale(LC_ALL, "rus");
	Log::LOG log = Log::INITLOG;
	try
	{
		Parm::PARM parm = Parm::getparm(argc, argv);
		log = Log::getlog(parm.log);
		Log::WriteLog(log);
		Log::WriteParm(log, parm);
		ofstream sin(parm.sin);

		// Проверка на запрещенные символы
		In::IN in = In::getin(parm.in, parm.out);
		Log::WriteIn(log, in);
		Log::WriteLine(log, "IN  : Запрещенных символов не найдено\n", "");

		// Разбиение на слова(ТОКЕНЫ)
		Log::WriteLine(log, "TKN : Разбиение на токены ", "");
		TOKEN::TokenTable tokentable = TOKEN::tokenize(in);
		TOKEN::SaveTokenTableInFile(tokentable, parm.tkn);
		Log::WriteLine(log, "- DONE\n", "");

		// Лексический анализ
		Log::WriteLine(log, "LEX : Лексический анализ ", "");
		Lexer::LEX lex = Lexer::fillingInTables(tokentable);
		Log::WriteLine(log, "- DONE\n", "");

		// Синтаксический анализ
		Log::WriteLine(log, "SIN : Синтаксический анализ ", "");
		MFST_TRACE_START(sin)
			MFST::Mfst mfst(lex, GRB::getGreibach());
		mfst.start(sin);
		mfst.savededucation();
		mfst.printrules(sin);
		Log::WriteLine(log, "- DONE\n", "");

		// Семантический анализ
		Log::WriteLine(log, "SEM : Семантический анализ ", "");
		CallSemantic(lex.lextable, lex.idtable);
		Log::WriteLine(log, "- DONE\n", "");

		// Польская нотация
		Log::WriteLine(log, "POL : Польская нотация ", "");
		CallPolishNotation(lex.lextable, lex.idtable);
		Log::WriteLine(log, "- DONE\n", "");

		// Вывод таблиц
		LT::showTable(lex.lextable, parm.lex);
		IT::showTable(lex.idtable, parm.id);

		// Генерация кода
		Log::WriteLine(log, "GEN : Генерация кода ", "");
		CodeGeneration::CodeGeneration(lex, parm.out);
		Log::WriteLine(log, "- DONE\n", "");


		Log::Close(log);
	}
	catch (Error::ERROR e)
	{
		Log::WriteLine(log, "- ERROR\n", "");
		Log::WriteError(log, e);
	}
	return 0;
}