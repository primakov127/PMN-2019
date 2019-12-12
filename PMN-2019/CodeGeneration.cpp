#include "pch.h"
#include "CodeGeneration.h"

namespace CodeGeneration
{
	void CodeGeneration(Lexer::LEX lex, wchar_t outfile[])
	{
		ofstream generation(outfile);

		generation << BEGIN;
		generation << EXTERN;

		generation << ".CONST\n";
		generation << "\tnull_division BYTE \'ERROR: DIVISION BY ZERO\', 0\n";
		for (int i = 0; i < lex.idtable.size; i++)
		{
			if (lex.idtable.table[i].idType == IT::L)
			{
				generation << "\t" << lex.idtable.table[i].id;
				if (lex.idtable.table[i].idDataType == IT::STR)
				{
					generation << " BYTE " << lex.idtable.table[i].value.vstr.str << ", 0\n";
				}
				else if (lex.idtable.table[i].idDataType == IT::INT)
				{
					generation << " SDWORD " << lex.idtable.table[i].value.vint << endl;
				}
				else
				{
					generation << " BYTE " << lex.idtable.table[i].value.vint << endl;
				}
			}
		}

		generation << ".DATA\n";
		for (int i = 0; i < lex.idtable.size; i++)
		{
			if (lex.idtable.table[i].idType == IT::IDTYPE::V)
			{
				generation << "\t" << lex.idtable.table[i].id;
				if (lex.idtable.table[i].idDataType == IT::BOOL)
				{
					generation << " BYTE 0\n";
				}
				if (lex.idtable.table[i].idDataType == IT::STR)
				{
					generation << " DWORD ?\n";
				}
				if (lex.idtable.table[i].idDataType == IT::INT)
				{
					generation << " SDWORD 0\n";
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
		generation << "\n.CODE\n\n";

		for (int i = 0; i < lex.lextable.size; i++)
		{
			switch (lex.lextable.table[i].lexema)
			{
				case LEX_FUNCTION:
				{
					generation << (func_name = lex.idtable.table[lex.lextable.table[++i].idxTI].id) << " PROC ";
					while (lex.lextable.table[i].lexema != LEX_RIGHTHESIS)
					{
						if (lex.idtable.table[lex.lextable.table[i].idxTI].idType == IT::P)
						{
							generation << lex.idtable.table[lex.lextable.table[i].idxTI].id << " : ";
							if (lex.idtable.table[lex.lextable.table[i].idxTI].idDataType == IT::INT)
							{
								generation << "SDWORD";
							}
							else if (lex.idtable.table[lex.lextable.table[i].idxTI].idDataType == IT::STR)
							{
								generation << "BYTE";
							}
							else
							{
								generation << "BYTE";
							}
						}
						if (lex.lextable.table[i].lexema == LEX_COMMA)
						{
							generation << ", ";
						}
						i++;
					}
					flag_func = true;
					generation << endl;
					break;
				}
				case LEX_MAIN:
				{
					flag_main = true;
					generation << "main PROC\n";
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
								generation << "\t\tcall power\n\tpush eax\n";
								break;
							case LEX_ABS:
								generation << "\t\tcall abser\n\tpush eax\n";
								break;
							case LEX_LITERAL:
							{
								if (lex.idtable.table[lex.lextable.table[i].idxTI].idDataType == IT::IDDATATYPE::INT)
								{
									generation << "\tpush " << lex.idtable.table[lex.lextable.table[i].idxTI].id << endl;
									stk.push(lex.idtable.table[lex.lextable.table[i].idxTI].id);
									break;
								}
								else
								{
									generation << "\tpush offset " << lex.idtable.table[lex.lextable.table[i].idxTI].id << endl;
									stk.push("offset" + (string)lex.idtable.table[lex.lextable.table[i].idxTI].id);
									break;
								}
							}
							case LEX_ID:
							{
								if (lex.idtable.table[lex.lextable.table[i].idxTI].idType == IT::IDTYPE::F)
								{
									generation << "\t\tcall " << lex.idtable.table[lex.lextable.table[i].idxTI].id << "\n\tpush eax\n";
									break;
								}
								generation << "\tpush " << lex.idtable.table[lex.lextable.table[i].idxTI].id << endl;
								stk.push(lex.idtable.table[lex.lextable.table[i].idxTI].id);
								break;
							}
							case LEX_STAR:
							{
								generation << "\tpop eax\n\tpop ebx\n";
								generation << "\tmul ebx\n\tpush eax\n";
								break;
							}
							case LEX_PLUS:
							{
								generation << "\tpop eax\n\tpop ebx\n";
								generation << "\tadd eax, ebx\n\tpush eax\n";
								break;
							}
							case LEX_MINUS:
							{
								generation << "\tpop ebx\n\tpop eax\n";
								generation << "\tsub eax, ebx\n\tpush eax\n";
								break;
							}
							case LEX_DIRSLASH:
							{
								generation << "\tpop ebx\n\tpop eax\n";
								generation << "\tcmp ebx,0\n"\
									"\tje SOMETHINGWRONG\n";
								generation << "\tcdq\n";
								generation << "\tidiv ebx\n\tpush eax\n";
								break;
							}
							case LEX_REMDIV:
							{

								generation << "\tpop ebx\n\tpop eax\n";
								generation << "\tcmp ebx,0\n"\
									"\tje SOMETHINGWRONG\n";
								generation << "\tcdq\n";
								generation << "\tidiv ebx\n\tpush edx\n";
								break;
							}
							default:
								break;
						}
						i++;
					}
					generation << "\tpop " << lex.idtable.table[lex.lextable.table[result_position].idxTI].id << "\n";
					generation << endl;
					break;
				}
				case LEX_RETURN:
				{
					generation << "\tpush ";
					i++;
					if (lex.idtable.table[lex.lextable.table[i].idxTI].idType == IT::L)
					{
						generation << lex.idtable.table[lex.lextable.table[i++].idxTI].value.vint << endl;
					}
					else
					{
						generation << lex.idtable.table[lex.lextable.table[i++].idxTI].id << endl;
					}
					if (flag_func)
					{
						generation << "\t\tjmp local" << num_of_ret << endl;
						flag_return = true;
					}
					if (flag_main)
					{
						generation << "\t\tjmp theend\n";
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
							generation << "theend:\n";
							flag_return = false;
						}
						generation << END;
					}
					if (flag_func)
					{
						if (flag_return)
						{
							generation << "local" << num_of_ret++ << ":\n";
							generation << "\tpop eax\n\tret\n";
							flag_return = false;
						}
						generation << func_name << " ENDP\n\n";
						flag_func = false;
					}
					if (flag_then)
					{
						flag_then = false;
						if (flag_else)
						{
							generation << "\tjmp e" << num_of_ends << endl;
							flag_else = false;
						}
						generation << "m" << num_of_points++ << ":\n";
					}
					if (flag_else)
					{
						flag_else = false;
						generation << "e" << num_of_ends++ << ":\n";
					}
					break;
				}
				case LEX_LEFTBRACE:
					if (flag_then)
					{
						generation << "m" << num_of_points++ << ":\n";
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
						generation << "\tmov eax, " << lex.idtable.table[lex.lextable.table[i + 1].idxTI].id << endl;
						generation << "\tcmp eax, " << lex.idtable.table[lex.lextable.table[i + 3].idxTI].id << endl;
						if (lex.lextable.table[i + 2].lexema == LEX_GREAT)
						{
							generation << "\t\tjg m" << num_of_points << endl;
							generation << "\t\tjl m" << num_of_points + 1 << endl;
						}
						else if (lex.lextable.table[i + 2].lexema == LEX_LESS)
						{
							generation << "\t\tjl m" << num_of_points << endl;
							generation << "\t\tjg m" << num_of_points + 1 << endl;
						}
						else if (lex.lextable.table[i + 2].lexema == LEX_EQUALEQUAL)
						{
							generation << "\t\tjz m" << num_of_points << endl;
							generation << "\t\tjnz m" << num_of_points + 1 << endl;
						}
						else if (lex.lextable.table[i + 2].lexema == LEX_NOTEQUAL)
						{
							generation << "\t\tjnz m" << num_of_points << endl;
							generation << "\t\tjz m" << num_of_points + 1 << endl;
						}
						generation << "\t\tje m" << num_of_points + 1 << endl;
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
						generation << "\npush " << lex.idtable.table[lex.lextable.table[i + 1].idxTI].id << "\ncall nout\n";
						break;
					case IT::IDDATATYPE::BOOL:
					case IT::IDDATATYPE::STR:
						if (lex.idtable.table[lex.lextable.table[i + 1].idxTI].idType == IT::IDTYPE::L)
							generation << "\npush offset " << lex.idtable.table[lex.lextable.table[i + 1].idxTI].id << "\ncall sout\n";
						else generation << "\npush " << lex.idtable.table[lex.lextable.table[i + 1].idxTI].id << "\ncall sout\n";
						break;
					}
					break;
				}
			}
		}
		generation.close();
	}
}