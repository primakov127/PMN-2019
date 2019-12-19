#pragma once
#include "pch.h"

#define LEXEMA_FIXSIZE 1                // фиксированный размер лексемы
#define LT_MAXSIZE 4096                 // максимальное количество строк в таблице лексем
#define LT_TI_NULLTDX 0xffffffff        // нет элемента таблицы индентификаторов

#define LEX_DIG		    'd'             // лексема для dig
#define LEX_STRING      's'             // лексема для str
#define LEX_BOOL		'b'				// лексема для bool
#define LEX_ID          'i'             // лексема для идентификатора
#define LEX_LITERAL     'l'             // лексема для литерала
#define LEX_IF			'q'				// лексема для if
#define LEX_ELSE		'2'				// лексема для else
#define LEX_WHILE		'w'				// лексема для while
#define LEX_FUNCTION    'f'             // лексема для function
#define LEX_NEW		    'n'             // лексема для new
#define LEX_RETURN      'r'             // лексема для return
#define LEX_OUT			'o'             // лексема для out
#define LEX_OUTL		'_'				// лексема для outl
#define LEX_MAIN		'm'				// лексема для main
#define LEX_POW			'p'				// лексема для встроенной ф-ции pow()
#define LEX_ABS			'a'				// лексема для встроенной ф-ции abs()
#define LEX_LESS		'<'				// лексема для <
#define LEX_GREAT		'>'				// лексема для >
#define LEX_SEMICOLON   ';'             // лексема для ;
#define LEX_COMMA       ','             // лексема для ,
#define LEX_LEFTBRACE   '{'             // лексема для {
#define LEX_RIGHTBRACE  '}'             // лексема для }
#define LEX_LEFTHESIS   '('             // лексема для (
#define LEX_RIGHTHESIS  ')'             // лексема для )
#define LEX_PLUS        '+'             // лексема для +
#define LEX_MINUS       '-'             // лексема для -
#define LEX_STAR        '*'             // лексема для *
#define LEX_DIRSLASH    '/'             // лексема для /
#define LEX_REMDIV		'%'				// лексема для %
#define LEX_EQUAL		'='				// лексема для =
#define LEX_EQUALEQUAL	'&'				// лексема для ==
#define LEX_NOTEQUAL	'!'				// лексема для !=

namespace LT                            // таблица лексем
{
	struct Entry                        // строка таблицы лексем
	{
		char lexema;
		int sn;                         // номер строки в исходном тексте
		int idxTI;                      // индекс в таблице индентификаторов или LT_TI_NULLIDX
	};

	struct LexTable                     // экземпляр таблицы лексем
	{
		int maxsize;                    // емкость таблицы лексем < LT_MAXSIZE
		int size;                       // текущий размер таблицы лексем < maxsize
		Entry* table;                   // массив строк таблицы лексем
	};

	LexTable Create(                    // создать таблицу лексем
		int size                        // емкость таблицы лексем < LT_MAXSIZE
	);

	void Add(                           // добавить строку в таблицу лексем
		LexTable& lextable,             // экземпляр таблицы лексем
		Entry entry                     // строка таблицы лексем
	);

	Entry GetEntry(                     // получить строку таблицы лексем
		LexTable& lextable,             // экземпляр таблицы лексем
		int n                           // номер получаемой строки
	);

	void Delete(LexTable& lextable);    // удалить таблицу лексем (освободить память)
	void SaveLexTableInFile(LexTable lextable, wchar_t outfile[]);
	void showTable(LexTable& lextable, wchar_t outfile[]);
	Entry createEntry(char lexema, int line);
	Entry createEntry(char lexema, int line, int idTI);
};