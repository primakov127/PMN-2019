#pragma once

#define LEXEMA_FIXSIZE 1                // фиксированный размер лексемы
#define LT_MAXSIZE 4096                 // максимальное количество строк в таблице лексем
#define LT_TI_NULLTDX 0xffffffff        // нет элемента таблицы индентификаторов

#define LEX_INTEGER     't'             // лексема для integer
#define LEX_STRING      's'             // лексема для string
#define LEX_ID          'i'             // лексема для идентификатора
#define LEX_LITERAL     'l'             // лексема для литерала
#define LEX_FUNCTION    'f'             // лексема для function
#define LEX_DECLARE     'd'             // лексема для declare
#define LEX_RETURN      'r'             // лексема для return
#define LEX_PRINT       'p'             // лексема для print
#define LEX_SEMICOLON   ';'             // лексема для ;
#define LEX_COMMA       ','             // лексема для ,
#define LEX_LEFTBRACE   '{'             // лексема для {
#define LEX_BRACELET    '}'             // лексема для }
#define LEX_LEFTHESIS   '('             // лексема для (
#define LEX_RIGHTHESIS  ')'             // лексема для )
#define	LEX_OPERATOR	'v'				// лексема для операторов
#define LEX_PLUS        '+'             // лексема для +
#define LEX_MINUS       '-'             // лексема для -
#define LEX_STAR        '*'             // лексема для *
#define LEX_DIRSLASH    '/'             // лексема для /
#define LEX_REMDIV		'%'				// лексема для %

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

};