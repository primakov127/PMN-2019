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

		In::IN in = In::getin(parm.in, parm.out);
		Log::WriteIn(log, in);

		// Разбиение на слова(ТОКЕНЫ)
		TOKEN::TokenTable tokentable = TOKEN::tokenize(in);
		TOKEN::SaveTokenTableInFile(tokentable, parm.tkn);

		// Лексический анализ
		Lexer::LEX lex = Lexer::fillingInTables(tokentable);
		LT::showTable(lex.lextable, parm.lex);
		IT::showTable(lex.idtable, parm.out);

		// Синтаксический анализ
		log = Log::getlog(parm.sin);
		MFST_TRACE_START(log)
			MFST::Mfst mfst(lex, GRB::getGreibach());
		mfst.start(log);
		mfst.savededucation();
		mfst.printrules(log);

		CallPolishNotation(lex.lextable, lex.idtable);
		//LT::showTable(lex.lextable, parm.lex);
		//IT::showTable(lex.idtable, parm.out);
	//	// 17
	//	// 62
	//	// 130
	//	LT::outTable(lex.lextable, parm.out);
		
		Log::Close(log);
	}
	catch (Error::ERROR e)
	{
		Log::WriteError(log, e);
	}
	return 0;
}