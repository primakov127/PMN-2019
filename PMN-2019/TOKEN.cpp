#include "pch.h"

namespace TOKEN
{
	TokenTable* tokenize(In::IN in)
	{
		TokenTable tokens = CreateTokenTable(TOKEN_MAXSIZE);
		char temp[64];
		int NumOfCharRecorded = 0;
		int CurrentLine = 0;


		for (int CharPointer = 0; in.text[CharPointer] != IN_CODE_ENDL; CharPointer++)
		{
			

		}
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

	TokenTable CreateTokenTable(int size)
	{
		if (size > TOKEN_MAXSIZE)								//	������, ���� size > LT_MAXSIZE
			throw ERROR_THROW(130);

		TokenTable tokentable;									//	�������� ������� ������
		tokentable.maxsize = size;								//	������ ������� ������
		tokentable.size = 0;									//	������� ������ ������� ������
		tokentable.table = new Token[tokentable.maxsize];		//	������ ����� ������ ������

		return tokentable;
	}

	void addToken(TokenTable* tokens, char token[], int line)
	{
		Token item;
		strcpy(item.token, token);
		item.line = line;
	}
}