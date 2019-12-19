#pragma once
#include "pch.h"

#define LEXEMA_FIXSIZE 1                // ������������� ������ �������
#define LT_MAXSIZE 4096                 // ������������ ���������� ����� � ������� ������
#define LT_TI_NULLTDX 0xffffffff        // ��� �������� ������� ����������������

#define LEX_DIG		    'd'             // ������� ��� dig
#define LEX_STRING      's'             // ������� ��� str
#define LEX_BOOL		'b'				// ������� ��� bool
#define LEX_ID          'i'             // ������� ��� ��������������
#define LEX_LITERAL     'l'             // ������� ��� ��������
#define LEX_IF			'q'				// ������� ��� if
#define LEX_ELSE		'2'				// ������� ��� else
#define LEX_WHILE		'w'				// ������� ��� while
#define LEX_FUNCTION    'f'             // ������� ��� function
#define LEX_NEW		    'n'             // ������� ��� new
#define LEX_RETURN      'r'             // ������� ��� return
#define LEX_OUT			'o'             // ������� ��� out
#define LEX_OUTL		'_'				// ������� ��� outl
#define LEX_MAIN		'm'				// ������� ��� main
#define LEX_POW			'p'				// ������� ��� ���������� �-��� pow()
#define LEX_ABS			'a'				// ������� ��� ���������� �-��� abs()
#define LEX_LESS		'<'				// ������� ��� <
#define LEX_GREAT		'>'				// ������� ��� >
#define LEX_SEMICOLON   ';'             // ������� ��� ;
#define LEX_COMMA       ','             // ������� ��� ,
#define LEX_LEFTBRACE   '{'             // ������� ��� {
#define LEX_RIGHTBRACE  '}'             // ������� ��� }
#define LEX_LEFTHESIS   '('             // ������� ��� (
#define LEX_RIGHTHESIS  ')'             // ������� ��� )
#define LEX_PLUS        '+'             // ������� ��� +
#define LEX_MINUS       '-'             // ������� ��� -
#define LEX_STAR        '*'             // ������� ��� *
#define LEX_DIRSLASH    '/'             // ������� ��� /
#define LEX_REMDIV		'%'				// ������� ��� %
#define LEX_EQUAL		'='				// ������� ��� =
#define LEX_EQUALEQUAL	'&'				// ������� ��� ==
#define LEX_NOTEQUAL	'!'				// ������� ��� !=

namespace LT                            // ������� ������
{
	struct Entry                        // ������ ������� ������
	{
		char lexema;
		int sn;                         // ����� ������ � �������� ������
		int idxTI;                      // ������ � ������� ���������������� ��� LT_TI_NULLIDX
	};

	struct LexTable                     // ��������� ������� ������
	{
		int maxsize;                    // ������� ������� ������ < LT_MAXSIZE
		int size;                       // ������� ������ ������� ������ < maxsize
		Entry* table;                   // ������ ����� ������� ������
	};

	LexTable Create(                    // ������� ������� ������
		int size                        // ������� ������� ������ < LT_MAXSIZE
	);

	void Add(                           // �������� ������ � ������� ������
		LexTable& lextable,             // ��������� ������� ������
		Entry entry                     // ������ ������� ������
	);

	Entry GetEntry(                     // �������� ������ ������� ������
		LexTable& lextable,             // ��������� ������� ������
		int n                           // ����� ���������� ������
	);

	void Delete(LexTable& lextable);    // ������� ������� ������ (���������� ������)
	void SaveLexTableInFile(LexTable lextable, wchar_t outfile[]);
	void showTable(LexTable& lextable, wchar_t outfile[]);
	Entry createEntry(char lexema, int line);
	Entry createEntry(char lexema, int line, int idTI);
};