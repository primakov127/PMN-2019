#pragma once
#define IN_MAX_LEN_TEXT 1024*1024
#define IN_CODE_ENDL '\0'
// Таблица проверки входной информации, индекс = код(Windows-1251) символа
// Значение IN::F - запрещенный символ | IN::T-разрешенный символ | IN::I-игнорировать(не вводить)

#define IN_CODE_TABLE {\
			/*00*/ /*01*/ /*02*/ /*03*/ /*04*/ /*05*/ /*06*/ /*07*/ /*08*/ /*09*/ /*0A*/ /*0B*/ /*0C*/ /*0D*/ /*0E*/ /*0F*/\
	/*00*/	IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::T, IN::T, IN::F, IN::F, IN::F, IN::F, IN::F,\
	/*10*/	IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F,\
	/*20*/	IN::T, IN::T, IN::T, IN::F, IN::F, IN::T, IN::F, IN::F, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T,\
	/*30*/	IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T,\
	/*40*/	IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T,\
	/*50*/	IN::F, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::I, IN::T, IN::T, IN::F, IN::F, IN::F, IN::F, IN::F,\
	/*60*/	IN::F, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T,\
	/*70*/	IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::F, IN::T, IN::F, IN::F,\
	\
	/*80*/	IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F,\
	/*90*/	IN::F, IN::F, IN::F, IN::T, IN::T, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F,\
	/*A0*/	IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F,\
	/*B0*/	IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F,\
	/*C0*/	IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T,\
	/*D0*/	IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T,\
	/*E0*/	IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T,\
	/*F0*/	IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T,\
}

namespace In
{
	struct IN										// Исходные данные
	{
		enum { T = 1024, F = 2048, I = 4096 };		// Т - допустимый символ | F - недопустимый | I - игнорировать иначе заменить
		int size;									// Размер исходного кода
		int lines;									// Количество строк
		int ignor;									// Количество проигнорированных строк
		unsigned char* text;						// Исходный текст
		int code[256];								// Таблица проверки: T, F, I новое значение
	};

	// Ф-ция вывода и проверки входного потока 
	IN getin(wchar_t infile[], wchar_t outfile[]);
}