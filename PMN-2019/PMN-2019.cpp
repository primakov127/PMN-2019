#include "pch.h"
#include <locale>
#include <cwchar>
			


int _tmain(int argc, _TCHAR ** argv)
{
	setlocale(LC_ALL, "rus");
	Log::LOG log = Log::INITLOG;
	//LT::LexTable lextable = LT::Create(LT_MAXSIZE);
	//IT::IdTable idtable = IT::Create(TI_MAXSIZE);
	//LEX::LEX lex;
	//lex.lextable = lextable;
	//lex.idtable = idtable;
	try
	{
		Parm::PARM parm = Parm::getparm(argc, argv);
		log = Log::getlog(parm.log);
		//Log::WriteLine(log, L"Тест", L" Без ошибок", L"");
		Log::WriteLog(log);
		Log::WriteParm(log, parm);
		In::IN in = In::getin(parm.in, parm.out);
		Log::WriteIn(log, in);
		TOKEN::TokenTable tokentable = TOKEN::tokenize(in);
		TOKEN::SaveTokenTableInFile(tokentable, parm.tkn);
		Lex::LEX lex = Lex::fillingInTables(tokentable);
		LT::showTable(lex.lextable, parm.lex);
		IT::showTable(lex.idtable, parm.out);
	//	LEX::LexAnal(parm.in, parm.out, lex.lextable, lex.idtable);

	//	//polishNotation(62, lextable, idtable);
	//	//polishNotation(17, lextable, idtable);


	//	MFST_TRACE_START
	//		MFST::Mfst mfst(lex, GRB::getGreibach());
	//	mfst.start();
	//	mfst.savededucation();
	//	mfst.printrules();


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