#include "pch.h"

namespace TOKEN
{
	TokenTable tokenize(In::IN in)
	{
		TokenTable tokens = CreateTokenTable(TOKEN_MAXSIZE);
		char buffer[512];
		int NumOfCharRecorded = 0;
		int CurrentLine = 0;
		int LinePosition = 0;


		for (int CharPointer = 0; in.text[CharPointer] != IN_CODE_ENDL; CharPointer++)
		{
			if (isSeparator(in.text[CharPointer]))
			{
				if (NumOfCharRecorded)
				{
					buffer[NumOfCharRecorded] = IN_CODE_ENDL;
					addToken(tokens, buffer, CurrentLine);
					NumOfCharRecorded = 0;
				}

				if (in.text[CharPointer] == '\n')
				{
					CurrentLine++;
					LinePosition = 0;
				}

				if (in.text[CharPointer] != ' ' && in.text[CharPointer] != '\t' && in.text[CharPointer] != '\n')
					addToken(tokens, sepToken(in.text[CharPointer]), CurrentLine);

				continue;
			}

			if (in.text[CharPointer] == '\'')
			{
				if (NumOfCharRecorded)
					throw ERROR_THROW_IN(132, CurrentLine, LinePosition);

				do
				{
					if (in.text[CharPointer] == '\n')
						throw ERROR_THROW_IN(133, CurrentLine, 0);
					if (NumOfCharRecorded == 256)
						throw ERROR_THROW_IN(135, CurrentLine, 0);


					buffer[NumOfCharRecorded] = in.text[CharPointer];
					CharPointer++;
					NumOfCharRecorded++;
				} while (in.text[CharPointer] != '\'');
				buffer[NumOfCharRecorded] = in.text[CharPointer];
				NumOfCharRecorded++;
				
				buffer[NumOfCharRecorded] = IN_CODE_ENDL;
				addToken(tokens, buffer, CurrentLine);
				NumOfCharRecorded = 0;

				continue;
			}
			
			buffer[NumOfCharRecorded] = in.text[CharPointer];
			NumOfCharRecorded++;
			LinePosition++;
		}

		return tokens;
	}

	bool isSeparator(char ch)
	{
		char separators[] = TOKEN_SEPARATORS;
		int index = 0;

		while (separators[index] != IN_CODE_ENDL)
		{
			if (ch == separators[index])
				return true;
			index++;
		}

		return false;
	}

	char* sepToken(char sep)
	{
		char* separator = new char[2];
		separator[0] = sep;
		separator[1] = IN_CODE_ENDL;

		return separator;
	}

	TokenTable CreateTokenTable(int size)
	{
		if (size > TOKEN_MAXSIZE)								//	Ошибка, если size > LT_MAXSIZE
			throw ERROR_THROW(130);

		TokenTable tokentable;									//	Создание таблицы лексем
		tokentable.maxsize = size;								//	Размер таблицы лексем
		tokentable.size = 0;									//	Текущий размер таблица лексем
		tokentable.table = new Token[tokentable.maxsize];		//	Массив строк таблиц лексем

		return tokentable;
	}

	void addToken(TokenTable& tokens, char* token, int line)
	{
		if (tokens.size > tokens.maxsize)
			throw ERROR_THROW(131);

		Token item;
		strcpy(item.token, token);
		item.line = line;

		tokens.table[tokens.size] = item;
		tokens.size++;
	}

	void SaveTokenTableInFile(TokenTable tokens, wchar_t outfile[])
	{
		std::ofstream out(outfile);
		if (!out.is_open())
			throw ERROR_THROW(113);

		int line = 0;
		out << std::right << std::setw(3) << line << "  ";
		for (int i = 0; i < tokens.size; i++)
		{
			if (tokens.table[i].line == line)
			{
				out << tokens.table[i].token;
			}
			else
			{
				out << std::endl;
				line += (tokens.table[i].line - line);
				out << std::right << std::setw(3) << line << "  " << tokens.table[i].token;
			}

		}

		out.close();
	}
}