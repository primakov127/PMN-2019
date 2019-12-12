#pragma once
#define PARM_IN L"-in:"						// ���� ��� ����� ��������� ����
#define PARM_OUT L"-out:"					// ���� ��� ����� ���������� ����
#define PARM_LOG L"-log:"					// ���� ��� ����� �������
#define PARM_TKN L"-tkn:"					// ���� ��� ����� ������� �������
#define PARM_LEX L"-lex:"					// ���� ��� ����� ������� ������
#define PARM_ID L"-id:"					// ���� ��� ����� ������� ���������������
#define PARM_SIN L"-sin:"					// ���� ��� ������ �������
#define PARM_MAX_SIZE 300					// ������������ ����� ������ ���������
#define PARM_OUT_DEFAULT_EXT L".out"		// ���������� ����� ���������� ���� �� ���������
#define PARM_LOG_DEFAULT_EXT L".log"		// ���������� ����� ��������� �� ���������
#define PARM_TKN_DEFAULT_EXT L".tkn"		// ���������� ����� ������� ������� �� ���������
#define PARM_LEX_DEFAULT_EXT L".lex"		// ���������� ����� ������� ������ �� ���������
#define PARM_ID_DEFAULT_EXT L".id"			// ���������� ����� ������� ��������������� �� ���������
#define PARM_SIN_DEFAULT_EXT L".sin"		// ���������� ����� ������ ������� �� ���������

namespace Parm								// ��������� ������� ����������
{
	struct PARM								// ������� ���������
	{
		wchar_t in[PARM_MAX_SIZE];			// -in:	��� ����� ��������� ����
		wchar_t out[PARM_MAX_SIZE];			// -out: ��� ����� ���������� ����
		wchar_t log[PARM_MAX_SIZE];			// -log: ��� ����� ���������
		wchar_t tkn[PARM_MAX_SIZE];			// -tkn: ��� ����� ������� �������
		wchar_t lex[PARM_MAX_SIZE];			// -lex: ��� ����� ������� ������
		wchar_t id[PARM_MAX_SIZE];			// -id: ��� ����� ������� ���������������
		wchar_t sin[PARM_MAX_SIZE];			// -sin: ��� ����� ������ �������
	};

	PARM getparm(int argc, _TCHAR* argv[]);	// ������������ struct PARM �� ������ ��������� ������� main
}
