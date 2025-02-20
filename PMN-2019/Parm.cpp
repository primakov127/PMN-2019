#include "pch.h"

namespace Parm
{
	PARM getparm(int argc, _TCHAR* argv[])
	{
		PARM Input = {};
		for (int i = 1; i < argc; i++)
		{
			if (wcslen(argv[i]) > PARM_MAX_SIZE)
			{
				throw ERROR_THROW(11)
			}
			if (wcsstr(argv[i], PARM_IN))
				wcscpy_s(Input.in, argv[i] + wcslen(PARM_IN));
			else if (wcsstr(argv[i], PARM_OUT))
				wcscpy_s(Input.out, argv[i] + wcslen(PARM_OUT));
			else if (wcsstr(argv[i], PARM_LOG))
				wcscpy_s(Input.log, argv[i] + wcslen(PARM_LOG));
			else if (wcsstr(argv[i], PARM_TKN))
				wcscpy_s(Input.tkn, argv[i] + wcslen(PARM_TKN));
			else if (wcsstr(argv[i], PARM_LEX))
				wcscpy_s(Input.lex, argv[i] + wcslen(PARM_LEX));
			else if (wcsstr(argv[i], PARM_ID))
				wcscpy_s(Input.lex, argv[i] + wcslen(PARM_ID));
			else if (wcsstr(argv[i], PARM_SIN))
				wcscpy_s(Input.sin, argv[i] + wcslen(PARM_SIN));
		}
		if (wcslen(Input.in) == 0)
			throw ERROR_THROW(10);
		if (wcslen(Input.out) == 0)
		{
			wcscpy_s(Input.out, Input.in);
			wcsncat_s(Input.out, PARM_OUT_DEFAULT_EXT, wcslen(PARM_OUT_DEFAULT_EXT));
		}
		if (wcslen(Input.log) == 0)
		{
			wcscpy_s(Input.log, Input.in);
			wcsncat_s(Input.log, PARM_LOG_DEFAULT_EXT, wcslen(PARM_LOG_DEFAULT_EXT));
		}
		if (wcslen(Input.tkn) == 0)
		{
			wcscpy_s(Input.tkn, Input.in);
			wcsncat_s(Input.tkn, PARM_TKN_DEFAULT_EXT, wcslen(PARM_TKN_DEFAULT_EXT));
		}
		if (wcslen(Input.lex) == 0)
		{
			wcscpy_s(Input.lex, Input.in);
			wcsncat_s(Input.lex, PARM_LEX_DEFAULT_EXT, wcslen(PARM_LEX_DEFAULT_EXT));
		}
		if (wcslen(Input.id) == 0)
		{
			wcscpy_s(Input.id, Input.in);
			wcsncat_s(Input.id, PARM_ID_DEFAULT_EXT, wcslen(PARM_ID_DEFAULT_EXT));
		}
		if (wcslen(Input.sin) == 0)
		{
			wcscpy_s(Input.sin, Input.in);
			wcsncat_s(Input.sin, PARM_SIN_DEFAULT_EXT, wcslen(PARM_SIN_DEFAULT_EXT));
		}
		return Input;
	}
}