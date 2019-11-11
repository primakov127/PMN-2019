#pragma once
#define PARM_IN L"-in:"						// ���� ��� ����� ��������� ����
#define PARM_OUT L"-out:"					// ���� ��� ����� ���������� ����
#define PARM_LOG L"-log:"					// ���� ��� ����� �������
#define PARM_TKN L"-tkn:"					// ���� ��� ����� ������� �������
#define PARM_LEX L"-lex:"					// ���� ��� ����� ������� ������
#define PARM_MAX_SIZE 300					// ������������ ����� ������ ���������
#define PARM_OUT_DEFAULT_EXT L".out"		// ���������� ����� ���������� ���� �� ���������
#define PARM_LOG_DEFAULT_EXT L".log"		// ���������� ����� ��������� �� ���������
#define PARM_TKN_DEFAULT_EXT L".tkn"		// ���������� ����� ������� ������� �� ���������
#define PARM_LEX_DEFAULT_EXT L".lex"		// ���������� ����� ������� ������ �� ���������

namespace Parm								// ��������� ������� ����������
{
	struct PARM								// ������� ���������
	{
		wchar_t in[PARM_MAX_SIZE];			// -in:	��� ����� ��������� ����
		wchar_t out[PARM_MAX_SIZE];			// -out: ��� ����� ���������� ����
		wchar_t log[PARM_MAX_SIZE];			// -log: ��� ����� ���������
		wchar_t tkn[PARM_MAX_SIZE];			// -tkn: ��� ����� ������� �������
		wchar_t lex[PARM_MAX_SIZE];			// -lex: ��� ����� ������� ������
	};

	PARM getparm(int argc, _TCHAR* argv[]);	// ������������ struct PARM �� ������ ��������� ������� main
}
