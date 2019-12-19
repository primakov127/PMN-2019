#pragma once
#include "pch.h"
#include "LEX.h"

#define BEGIN \
".586\n"\
".model flat, stdcall\n"\
"includelib libucrt.lib\n"\
"includelib kernel32.lib\n"\
"includelib \"..\\Debug\\PMN_LIB.lib\"\n"\

#define EXTERN \
"\nExitProcess PROTO:DWORD "\
"\nSYSPAUSE PROTO "\
"\nnout PROTO : SDWORD "\
"\nsout PROTO : BYTE "\
"\nsoutl PROTO : BYTE "\
"\nnoutl PROTO : SDWORD "\
"\npower PROTO  : SDWORD, : SDWORD "\
"\nabser PROTO  : SDWORD "\
"\n\n.STACK 4096\n\n"

#define END \
"\tcall SYSPAUSE"\
"\n\tpush 0"\
"\n\tcall ExitProcess"\
"\nSOMETHINGWRONG::"\
"\n\tpush offset null_division"\
"\n\tcall soutl"\
"\njmp konec"\
"\noverflow::"\
"\n\tpush offset OVER_FLOW"\
"\n\tcall soutl"\
"\nkonec:"\
"\n\tcall SYSPAUSE"\
"\n\tpush -1"\
"\n\tcall ExitProcess"\
"\nmain ENDP\nend main"


namespace CodeGeneration
{
	void CodeGeneration(Lexer::LEX lex, wchar_t outfile[]);
}