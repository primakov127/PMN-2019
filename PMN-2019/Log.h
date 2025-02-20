#pragma once
#include <fstream>
#include "In.h"
#include "Parm.h"
#include "Error.h"

	// ������ � ����������
namespace Log
{
	struct LOG										//	��������
	{
		wchar_t logfile[PARM_MAX_SIZE];				//	��� ����� ���������
		std::ofstream* stream;						//	�������� ����� ���������
	};

	// ��������� ��������� ������������� LOG
	static const LOG INITLOG = { L"",NULL };		
	// �-��� �������� ��������� LOG
	LOG getlog(wchar_t logfile[]);					
	// �-��� ������ ������������ ����� � ��������
	void WriteLine(LOG log, const char* c, ...);
	// �-��� ������ ������������ ����� � ��������
	void WriteLine(LOG, const wchar_t* c, ...);
	// �-��� ������ ���������� � ��������
	void WriteLog(LOG log);
	// �-��� ������ ���������� � ������� ���������� � ��������
	void WriteParm(LOG log, Parm::PARM parm);
	// �-��� ������ ���������� � ������� ������ � �������� 
	void WriteIn(LOG log, In::IN in);
	// �-��� ������ ���������� �� ������ � �������� 
	void WriteError(LOG log, Error::ERROR error);
	// �-��� �������� ���������	
	void Close(LOG log);	


}