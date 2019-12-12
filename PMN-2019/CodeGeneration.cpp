#include "pch.h"
#include "CodeGeneration.h"

namespace CodeGeneration
{
	void CodeGeneration(Lexer::LEX lex, Log::LOG log)
	{
		*(log.stream) << BEGIN;
		*(log.stream) << EXTERN;

		*(log.stream) << ".CONST\n";
		*(log.stream) << "\tnull_division BYTE \'ERROR: DIVISION BY ZERO\', 0\n";
		for (int i = 0; i < lex.idtable.size; i++)
		{
			if (lex.idtable.table[i].idType == IT::L)
			{
				*(log.stream) << "\t" << lex.idtable.table[i].id;
				if (lex.idtable.table[i].idDataType == IT::STR)
				{
					*(log.stream) << " BYTE " << lex.idtable.table[i].value.vstr.str << ", 0\n";
				}
				else if (lex.idtable.table[i].idDataType == IT::INT)
				{
					*(log.stream) << " SDWORD " << lex.idtable.table[i].value.vint << endl;
				}
				else
				{
					*(log.stream) << " BYTE " << lex.idtable.table[i].value.vint << endl;
				}
			}
		}

		*(log.stream) << ".DATA\n";
		for (int i = 0; i < lex.idtable.size; i++)
		{
			if (lex.idtable.table[i].idType == IT::IDTYPE::V)
			{
				*(log.stream) << "\t" << lex.idtable.table[i].id;
				if (lex.idtable.table[i].idDataType == IT::BOOL)
				{
					*(log.stream) << " BYTE 0\n";
				}
				if (lex.idtable.table[i].idDataType == IT::STR)
				{
					*(log.stream) << " DWORD ?\n";
				}
				if (lex.idtable.table[i].idDataType == IT::INT)
				{
					*(log.stream) << " SDWORD 0\n";
				}
			}
		}

		stack<string> stk;
		int num_of_points = 0,
			num_of_ret = 0,
			num_of_ends = 0;
		string strret = "",
			func_name = "";					// имя локальной функции
		bool flag_func = false,					// внутри локальной функции?
			flag_return = false,					// был ret?
			flag_main = false,					// внутри главной функции?
			flag_if = false,					// внутри if?
			flag_then = false,					// внутри then?
			flag_else = false;					// внутри then/else?
		*(log.stream) << "\n.CODE\n\n";

		for (int i = 0; i < lex.lextable.size; i++)
		{
			switch (lex.lextable.table[i].lexema)
			{
				case LEX_FUNCTION:
				{
					*(log.stream) << (func_name = lex.idtable.table[lex.lextable.table[++i].idxTI].id) << " PROC ";
					while (lex.lextable.table[i].lexema != LEX_RIGHTHESIS)
					{
						if (lex.idtable.table[lex.lextable.table[i].idxTI].idType == IT::P)
						{
							*(log.stream) << lex.idtable.table[lex.lextable.table[i].idxTI].id << " : ";
							if (lex.idtable.table[lex.lextable.table[i].idxTI].idDataType == IT::INT)
							{
								*(log.stream) << "SDWORD";
							}
							else if (lex.idtable.table[lex.lextable.table[i].idxTI].idDataType == IT::STR)
							{
								*(log.stream) << "BYTE";
							}
							else
							{
								*(log.stream) << "BYTE";
							}
						}
						if (lex.lextable.table[i].lexema == LEX_COMMA)
						{
							*(log.stream) << ", ";
						}
						i++;
					}
					flag_func = true;
					*(log.stream) << endl;
					break;
				}
				case LEX_MAIN:
				{
					flag_main = true;
					*(log.stream) << "main PROC\n";
					break;
				}
				case LEX_EQUAL:
				{
					int result_position = i - 1;
					while (lex.lextable.table[i].lexema != LEX_SEMICOLON)
					{
					
						switch (lex.lextable.table[i].lexema)
						{
							case LEX_POW:
								*(log.stream) << "\t\tcall power\n\tpush eax\n";
								break;
							case LEX_ABS:
								*(log.stream) << "\t\tcall abser\n\tpush eax\n";
								break;
							case LEX_LITERAL:
							{
								if (lex.idtable.table[lex.lextable.table[i].idxTI].idDataType == IT::IDDATATYPE::INT)
								{
									*(log.stream) << "\tpush " << lex.idtable.table[lex.lextable.table[i].idxTI].id << endl;
									stk.push(lex.idtable.table[lex.lextable.table[i].idxTI].id);
									break;
								}
								else
								{
									*(log.stream) << "\tpush offset " << lex.idtable.table[lex.lextable.table[i].idxTI].id << endl;
									stk.push("offset" + (string)lex.idtable.table[lex.lextable.table[i].idxTI].id);
									break;
								}
							}
							case LEX_ID:
							{
								if (lex.idtable.table[lex.lextable.table[i].idxTI].idType == IT::IDTYPE::F)
								{
									*(log.stream) << "\t\tcall " << lex.idtable.table[lex.lextable.table[i].idxTI].id << "\n\tpush eax\n";
									break;
								}
								*(log.stream) << "\tpush " << lex.idtable.table[lex.lextable.table[i].idxTI].id << endl;
								stk.push(lex.idtable.table[lex.lextable.table[i].idxTI].id);
								break;
							}
							case LEX_STAR:
							{
								*(log.stream) << "\tpop eax\n\tpop ebx\n";
								*(log.stream) << "\tmul ebx\n\tpush eax\n";
								break;
							}
							case LEX_PLUS:
							{
								*(log.stream) << "\tpop eax\n\tpop ebx\n";
								*(log.stream) << "\tadd eax, ebx\n\tpush eax\n";
								break;
							}
							case LEX_MINUS:
							{
								*(log.stream) << "\tpop ebx\n\tpop eax\n";
								*(log.stream) << "\tsub eax, ebx\n\tpush eax\n";
								break;
							}
							case LEX_DIRSLASH:
							{
								*(log.stream) << "\tpop ebx\n\tpop eax\n";
								*(log.stream) << "\tcmp ebx,0\n"\
									"\tje SOMETHINGWRONG\n";
								*(log.stream) << "\tcdq\n";
								*(log.stream) << "\tidiv ebx\n\tpush eax\n";
								break;
							}
							case LEX_REMDIV:
							{

								*(log.stream) << "\tpop ebx\n\tpop eax\n";
								*(log.stream) << "\tcmp ebx,0\n"\
									"\tje SOMETHINGWRONG\n";
								*(log.stream) << "\tcdq\n";
								*(log.stream) << "\tidiv ebx\n\tpush edx\n";
								break;
							}
							default:
								break;
						}
						i++;
					}
					*(log.stream) << "\tpop " << lex.idtable.table[lex.lextable.table[result_position].idxTI].id << "\n";
					*(log.stream) << endl;
					break;
				}
				case LEX_RETURN:
				{
					*(log.stream) << "\tpush ";
					i++;
					if (lex.idtable.table[lex.lextable.table[i].idxTI].idType == IT::L)
					{
						*(log.stream) << lex.idtable.table[lex.lextable.table[i++].idxTI].value.vint << endl;
					}
					else
					{
						*(log.stream) << lex.idtable.table[lex.lextable.table[i++].idxTI].id << endl;
					}
					if (flag_func)
					{
						*(log.stream) << "\t\tjmp local" << num_of_ret << endl;
						flag_return = true;
					}
					if (flag_main)
					{
						*(log.stream) << "\t\tjmp theend\n";
						flag_return = true;
					}
					break;
				}
				case LEX_RIGHTBRACE:
				{
					if (flag_main && !flag_then && !flag_else && !flag_func)
					{
						if (flag_return)
						{
							*(log.stream) << "theend:\n";
							flag_return = false;
						}
						*(log.stream) << END;
					}
					if (flag_func)
					{
						if (flag_return)
						{
							*(log.stream) << "local" << num_of_ret++ << ":\n";
							*(log.stream) << "\tpop eax\n\tret\n";
							flag_return = false;
						}
						*(log.stream) << func_name << " ENDP\n\n";
						flag_func = false;
					}
					if (flag_then)
					{
						flag_then = false;
						if (flag_else)
						{
							*(log.stream) << "\tjmp e" << num_of_ends << endl;
							flag_else = false;
						}
						*(log.stream) << "m" << num_of_points++ << ":\n";
					}
					if (flag_else)
					{
						flag_else = false;
						*(log.stream) << "e" << num_of_ends++ << ":\n";
					}
					break;
				}
				case LEX_LEFTBRACE:
					if (flag_then)
					{
						*(log.stream) << "m" << num_of_points++ << ":\n";
					}
					break;
				case LEX_IF:
				{
					flag_if = true;
					flag_then = true;
					break;
				}
				case LEX_LEFTHESIS:
				{
					if (flag_if)
					{
						*(log.stream) << "\tmov eax, " << lex.idtable.table[lex.lextable.table[i + 1].idxTI].id << endl;
						*(log.stream) << "\tcmp eax, " << lex.idtable.table[lex.lextable.table[i + 3].idxTI].id << endl;
						if (lex.lextable.table[i + 2].lexema == LEX_GREAT)
						{
							*(log.stream) << "\t\tjg m" << num_of_points << endl;
							*(log.stream) << "\t\tjl m" << num_of_points + 1 << endl;
						}
						else if (lex.lextable.table[i + 2].lexema == LEX_LESS)
						{
							*(log.stream) << "\t\tjl m" << num_of_points << endl;
							*(log.stream) << "\t\tjg m" << num_of_points + 1 << endl;
						}
						else if (lex.lextable.table[i + 2].lexema == LEX_EQUALEQUAL)
						{
							*(log.stream) << "\t\tjz m" << num_of_points << endl;
							*(log.stream) << "\t\tjnz m" << num_of_points + 1 << endl;
						}
						else if (lex.lextable.table[i + 2].lexema == LEX_NOTEQUAL)
						{
							*(log.stream) << "\t\tjnz m" << num_of_points << endl;
							*(log.stream) << "\t\tjz m" << num_of_points + 1 << endl;
						}
						*(log.stream) << "\t\tje m" << num_of_points + 1 << endl;
						int j = i;
						while (lex.lextable.table[j++].lexema != LEX_RIGHTBRACE)
						{
							if (lex.lextable.table[j + 1].lexema == LEX_ELSE)
							{
								flag_else = true;
								break;
							}
						}
						if (!flag_else)
							flag_then = true;
						flag_if = false;
					}
					break;
				}
				case LEX_ELSE:
				{
					flag_else = true;
					break;
				}
				case LEX_OUT:
				{
					switch (lex.idtable.table[lex.lextable.table[i + 1].idxTI].idDataType)
					{
					case IT::IDDATATYPE::INT:
						*(log.stream) << "\npush " << lex.idtable.table[lex.lextable.table[i + 1].idxTI].id << "\ncall nout\n";
						break;
					case IT::IDDATATYPE::BOOL:
					case IT::IDDATATYPE::STR:
						if (lex.idtable.table[lex.lextable.table[i + 1].idxTI].idType == IT::IDTYPE::L)
							*(log.stream) << "\npush offset " << lex.idtable.table[lex.lextable.table[i + 1].idxTI].id << "\ncall sout\n";
						else *(log.stream) << "\npush " << lex.idtable.table[lex.lextable.table[i + 1].idxTI].id << "\ncall sout\n";
						break;
					}
					break;
				}
			}
		}
		Log::Close(log);
	}
}