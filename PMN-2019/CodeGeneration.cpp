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
		generation << "\ttrue BYTE \'true', 0\n";
		generation << "\tfalse BYTE \'false', 0\n";
		for (int i = 0; i < lex.idtable.size; i++)
		{
			if (lex.idtable.table[i].idType == IT::L)
			{
				generation << "\t" << lex.idtable.table[i].id;
				if (lex.idtable.table[i].idDataType == IT::STR)
				{
					generation << " DWORD " << lex.idtable.table[i].value.vstr.str << ", 0\n";
				}
				else if (lex.idtable.table[i].idDataType == IT::INT)
				{
					generation << " SDWORD " << lex.idtable.table[i].value.vint << endl;
				}
				else
				{
					generation << " DWORD " << lex.idtable.table[i].value.vint << endl;
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
					generation << " DWORD 0\n";
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
			num_of_ends = 0,
			num_of_boolCompare = 0,
			num_of_while = 0,
			num_of_if = 0;
		string strret = "",
			func_name = "";					// имя локальной функции
		bool flag_func = false,					// внутри локальной функции?
			flag_return = false,					// был ret?
			flag_main = false,					// внутри главной функции?
			flag_if = false,					// внутри if?
			flag_then = false,					// внутри then?
			flag_while = false,
			flag_else = false;					// внутри then/else?
		generation << "\n.CODE\n\n";

		for (int i = 0; i < lex.lextable.size; i++)
		{
			switch (lex.lextable.table[i].lexema)
			{
				case LEX_FUNCTION:
				{
					generation << (func_name = lex.idtable.table[lex.lextable.table[++i].idxTI].id) << " PROC ";
					int ind = i;
					for (; lex.lextable.table[ind].lexema != LEX_RIGHTHESIS; ind++);

					i = ind;
					while (lex.lextable.table[ind].lexema != LEX_LEFTHESIS)
					{
						if (lex.idtable.table[lex.lextable.table[ind].idxTI].idType == IT::P)
						{
							generation << lex.idtable.table[lex.lextable.table[ind].idxTI].id << " : ";
							if (lex.idtable.table[lex.lextable.table[ind].idxTI].idDataType == IT::INT)
							{
								generation << "SDWORD";
							}
							else if (lex.idtable.table[lex.lextable.table[ind].idxTI].idDataType == IT::STR)
							{
								generation << "DWORD";
							}
							else
							{
								generation << "DWORD";
							}
						}
						if (lex.lextable.table[ind].lexema == LEX_COMMA)
						{
							generation << ", ";
						}
						//i++;
						ind--;
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
								if (lex.lextable.table[i + 1].lexema == LEX_GREAT || lex.lextable.table[i + 1].lexema == LEX_LESS
									|| lex.lextable.table[i + 1].lexema == LEX_EQUALEQUAL || lex.lextable.table[i + 1].lexema == LEX_NOTEQUAL)
								{
									switch (lex.lextable.table[i + 1].lexema)
									{
									case LEX_GREAT:
										if (lex.idtable.table[lex.lextable.table[i].idxTI].value.vint > lex.idtable.table[lex.lextable.table[i + 2].idxTI].value.vint)
											generation << "\tpush " << 1 << endl;
										else
											generation << "\tpush " << 0 << endl;
										break;
									case LEX_LESS:
										if (lex.idtable.table[lex.lextable.table[i].idxTI].value.vint < lex.idtable.table[lex.lextable.table[i + 2].idxTI].value.vint)
											generation << "\tpush " << 1 << endl;
										else
											generation << "\tpush " << 0 << endl;
										break;
									case LEX_EQUALEQUAL:
										if (lex.idtable.table[lex.lextable.table[i].idxTI].value.vint == lex.idtable.table[lex.lextable.table[i + 2].idxTI].value.vint)
											generation << "\tpush " << 1 << endl;
										else
											generation << "\tpush " << 0 << endl;
										break;
									case LEX_NOTEQUAL:
										if (lex.idtable.table[lex.lextable.table[i].idxTI].value.vint != lex.idtable.table[lex.lextable.table[i + 2].idxTI].value.vint)
											generation << "\tpush " << 1 << endl;
										else
											generation << "\tpush " << 0 << endl;
										break;
									default:
										break;
									}
									i += 2;
									break;
								}
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
								if (lex.lextable.table[i + 1].lexema == LEX_GREAT || lex.lextable.table[i + 1].lexema == LEX_LESS
									|| lex.lextable.table[i + 1].lexema == LEX_EQUALEQUAL || lex.lextable.table[i + 1].lexema == LEX_NOTEQUAL)
								{
									switch (lex.lextable.table[i + 1].lexema)
									{
									case LEX_GREAT:
										if (lex.idtable.table[lex.lextable.table[i].idxTI].value.vint > lex.idtable.table[lex.lextable.table[i + 2].idxTI].value.vint)
											generation << "\tpush " << 1 << endl;
										else
											generation << "\tpush " << 0 << endl;
										break;
									case LEX_LESS:
										if (lex.idtable.table[lex.lextable.table[i].idxTI].value.vint < lex.idtable.table[lex.lextable.table[i + 2].idxTI].value.vint)
											generation << "\tpush " << 1 << endl;
										else
											generation << "\tpush " << 0 << endl;
										break;
									case LEX_EQUALEQUAL:
										if (lex.idtable.table[lex.lextable.table[i].idxTI].value.vint == lex.idtable.table[lex.lextable.table[i + 2].idxTI].value.vint)
											generation << "\tpush " << 1 << endl;
										else
											generation << "\tpush " << 0 << endl;
										break;
									case LEX_NOTEQUAL:
										if (lex.idtable.table[lex.lextable.table[i].idxTI].value.vint != lex.idtable.table[lex.lextable.table[i + 2].idxTI].value.vint)
											generation << "\tpush " << 1 << endl;
										else
											generation << "\tpush " << 0 << endl;
										break;
									default:
										break;
									}
									i += 2;
									break;
								}
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
					if (flag_main && !flag_else && !num_of_if && !flag_func && !num_of_while)
					{
						if (flag_return)
						{
							generation << "theend:\n";
							flag_return = false;
						}
						generation << END;
					}
					if (flag_func && lex.lextable.table[i + 1].lexema == LEX_SEMICOLON)
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
					if (num_of_if && !flag_else && !num_of_while)
					{
						if (lex.lextable.table[i + 1].lexema == LEX_ELSE)
						{
							generation << "\tjmp ifEnd" << num_of_if << endl;
						}
						else
						{
							generation << "else" << num_of_if << ":\n";
							num_of_if--;
						}
					}
					if (flag_else)
					{
						generation << "ifEnd" << num_of_if << ":\n";
						flag_else = false;
						num_of_if--;
					}
					if (num_of_while)
					{
						generation << "jmp " << "while" << num_of_while << "\n";
						generation << "whileEnd" << num_of_while-- << ":\n";
					}
					break;
				}
				case LEX_LEFTBRACE:
					if (num_of_if && !flag_else && flag_if)
					{
						generation << "ifi" << num_of_if << ":\n";
						flag_if = false;
					}
					if (flag_else && lex.lextable.table[i - 1].lexema == LEX_ELSE)
					{
						generation << "else" << num_of_if << ":\n";
					}
					if (num_of_while && flag_while)
					{
						generation << "whileT" << num_of_while << ":\n";
						flag_while = false;
					}
					break;
				case LEX_IF:
				{
					flag_if = true;
					//flag_then = true;
					num_of_if++;
					break;
				}
				case LEX_LEFTHESIS:
				{
					if (num_of_if && lex.lextable.table[i - 1].lexema == LEX_IF)
					{
						generation << "\tmov eax, " << lex.idtable.table[lex.lextable.table[i + 1].idxTI].id << endl;
						generation << "\tcmp eax, " << lex.idtable.table[lex.lextable.table[i + 3].idxTI].id << endl;
						if (lex.lextable.table[i + 2].lexema == LEX_GREAT)
						{
							generation << "\t\tjg ifi" << num_of_if << endl;
							generation << "\t\tjle else" << num_of_if << endl;
						}
						else if (lex.lextable.table[i + 2].lexema == LEX_LESS)
						{
							generation << "\t\tjl ifi" << num_of_if << endl;
							generation << "\t\tjge else" << num_of_if << endl;
						}
						else if (lex.lextable.table[i + 2].lexema == LEX_EQUALEQUAL)
						{
							generation << "\t\tjz ifi" << num_of_if << endl;
							generation << "\t\tjnz else" << num_of_if << endl;
						}
						else if (lex.lextable.table[i + 2].lexema == LEX_NOTEQUAL)
						{
							generation << "\t\tjnz ifi" << num_of_if << endl;
							generation << "\t\tjz else" << num_of_if << endl;
						}
						
					}
					else if (num_of_while && lex.lextable.table[i - 1].lexema == LEX_WHILE)
					{
						generation << "while" << num_of_while << ":" << endl;
						generation << "\tmov eax, " << lex.idtable.table[lex.lextable.table[i + 1].idxTI].id << endl;
						generation << "\tcmp eax, " << lex.idtable.table[lex.lextable.table[i + 3].idxTI].id << endl;
						if (lex.lextable.table[i + 2].lexema == LEX_GREAT)
						{
							generation << "\t\tjg whileT" << num_of_while << endl;
							generation << "\t\tjle whileEnd" << num_of_while << endl;
						}
						else if (lex.lextable.table[i + 2].lexema == LEX_LESS)
						{
							generation << "\t\tjl whileT" << num_of_while << endl;
							generation << "\t\tjge whileEnd" << num_of_while << endl;
						}
						else if (lex.lextable.table[i + 2].lexema == LEX_EQUALEQUAL)
						{
							generation << "\t\tjz whileT" << num_of_while << endl;
							generation << "\t\tjnz whileEnd" << num_of_while << endl;
						}
						else if (lex.lextable.table[i + 2].lexema == LEX_NOTEQUAL)
						{
							generation << "\t\tjnz whileT" << num_of_while << endl;
							generation << "\t\tjz whileEnd" << num_of_while << endl;
						}
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
						generation << "\tmov eax, " << lex.idtable.table[lex.lextable.table[i + 1].idxTI].id << endl;
						generation << "\tcmp eax, 0" << endl;
						generation << "\t\tjz " << lex.idtable.table[lex.lextable.table[i + 1].idxTI].id << num_of_boolCompare << "T" << endl;
						generation << "\t\tjnz " << lex.idtable.table[lex.lextable.table[i + 1].idxTI].id << num_of_boolCompare << "F" << endl;
						generation << "\n" << lex.idtable.table[lex.lextable.table[i + 1].idxTI].id << num_of_boolCompare << "T:" << endl;;
						generation << "\npush offset false" << "\ncall soutl\n";
						generation << "\njmp " << lex.idtable.table[lex.lextable.table[i + 1].idxTI].id << num_of_boolCompare << endl;
						generation << "\n" << lex.idtable.table[lex.lextable.table[i + 1].idxTI].id << num_of_boolCompare << "F:" << endl;;
						generation << "\npush offset true" << "\ncall soutl\n";
						generation << "\n" << lex.idtable.table[lex.lextable.table[i + 1].idxTI].id << num_of_boolCompare << ":" << endl;;

						num_of_boolCompare++;
						break;
					case IT::IDDATATYPE::STR:
						if (lex.idtable.table[lex.lextable.table[i + 1].idxTI].idType == IT::IDTYPE::L)
							generation << "\npush offset " << lex.idtable.table[lex.lextable.table[i + 1].idxTI].id << "\ncall sout\n";
						else generation << "\npush " << lex.idtable.table[lex.lextable.table[i + 1].idxTI].id << "\ncall sout\n";
						break;
					}
					break;
				}
				case LEX_OUTL:
				{
					switch (lex.idtable.table[lex.lextable.table[i + 1].idxTI].idDataType)
					{
					case IT::IDDATATYPE::INT:
						generation << "\npush " << lex.idtable.table[lex.lextable.table[i + 1].idxTI].id << "\ncall noutl\n";
						break;
					case IT::IDDATATYPE::BOOL:
						generation << "\tmov eax, " << lex.idtable.table[lex.lextable.table[i + 1].idxTI].id << endl;
						generation << "\tcmp eax, 0" << endl;
						generation << "\t\tjz " << lex.idtable.table[lex.lextable.table[i + 1].idxTI].id << num_of_boolCompare << "T" << endl;
						generation << "\t\tjnz " << lex.idtable.table[lex.lextable.table[i + 1].idxTI].id << num_of_boolCompare << "F" << endl;
						generation << "\n" << lex.idtable.table[lex.lextable.table[i + 1].idxTI].id << num_of_boolCompare << "T:" << endl;;
						generation << "\npush offset false" << "\ncall soutl\n";
						generation << "\njmp " << lex.idtable.table[lex.lextable.table[i + 1].idxTI].id << num_of_boolCompare << endl;
						generation << "\n" << lex.idtable.table[lex.lextable.table[i + 1].idxTI].id << num_of_boolCompare << "F:" << endl;;
						generation << "\npush offset true" << "\ncall soutl\n";
						generation << "\n" << lex.idtable.table[lex.lextable.table[i + 1].idxTI].id << num_of_boolCompare << ":" << endl;;

						num_of_boolCompare++;
						break;
					case IT::IDDATATYPE::STR:
						if (lex.idtable.table[lex.lextable.table[i + 1].idxTI].idType == IT::IDTYPE::L)
							generation << "\npush offset " << lex.idtable.table[lex.lextable.table[i + 1].idxTI].id << "\ncall soutl\n";
						else generation << "\npush " << lex.idtable.table[lex.lextable.table[i + 1].idxTI].id << "\ncall soutl\n";
						break;
					}
					break;
				}
				case LEX_WHILE:
				{
					flag_while = true;
					num_of_while++;
					break;
				}
			}
		}
		generation.close();
	}
}