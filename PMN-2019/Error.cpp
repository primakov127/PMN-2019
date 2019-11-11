#include "pch.h"
#include "Error.h"
#include <iostream>
#include <cstring>

namespace Error
{
	// 0-99		 C�������� ������ ����
	// 100-109	 ������ ����������
	// 110-119	 ������ �������� � ������ ������
	// 120-129	 ������ ���������� ������ ������ � ���������������
	// 130-139	 ������ ���������� ������� �������

	// ������� ������
	ERROR errors[ERROR_MAX_ENTRY] =
	{
		// ��� ������ ��� ��������� 0 - ERROR_MAX_ENTRY
		ERROR_ENTRY(0,"������������ ��� ������"),
		ERROR_ENTRY(1,"��������� ����"),
		ERROR_ENTRY_NODEF(2),ERROR_ENTRY_NODEF(3),ERROR_ENTRY_NODEF(4),ERROR_ENTRY_NODEF(5),
		ERROR_ENTRY_NODEF(6),ERROR_ENTRY_NODEF(7),ERROR_ENTRY_NODEF(8),ERROR_ENTRY_NODEF(9),
		ERROR_ENTRY_NODEF10(10),ERROR_ENTRY_NODEF10(20),ERROR_ENTRY_NODEF10(30),ERROR_ENTRY_NODEF10(40),ERROR_ENTRY_NODEF10(50),
		ERROR_ENTRY_NODEF10(60),ERROR_ENTRY_NODEF10(70),ERROR_ENTRY_NODEF10(80),ERROR_ENTRY_NODEF10(90),
		ERROR_ENTRY(100,"�������� -in ������ ���� �����"),
		ERROR_ENTRY_NODEF(101),ERROR_ENTRY_NODEF(102),ERROR_ENTRY_NODEF(103),
		ERROR_ENTRY(104,"��������� ������ �������� ���������"),
		ERROR_ENTRY_NODEF(105),ERROR_ENTRY_NODEF(106),ERROR_ENTRY_NODEF(107),
		ERROR_ENTRY_NODEF(108),ERROR_ENTRY_NODEF(109),
		ERROR_ENTRY(110,"������ ��� �������� ����� � �������� ����� (-in)"),
		ERROR_ENTRY(111,"������������ ������ � �������� ����� (-in)"),
		ERROR_ENTRY(112,"������ ��� �������� ����� ��������� (-log)"),
		ERROR_ENTRY(113,"������ ��� �������� ����� � �������� ������� (-tkn)"),
		ERROR_ENTRY(114,"������ ��� �������� ����� � �������� ������ (-lex)"),
		ERROR_ENTRY_NODEF(115),
		ERROR_ENTRY_NODEF(116),ERROR_ENTRY_NODEF(117),ERROR_ENTRY_NODEF(118),ERROR_ENTRY_NODEF(119),
		ERROR_ENTRY(120, "��������� ������� ������� ������"),
		ERROR_ENTRY(121, "��������� ���������� ����� � ������� ������"),
		ERROR_ENTRY(122, "� ������� ������ ����������� ������ � �������� �������"),
		ERROR_ENTRY(123, "��������� ������� ������� ���������������"),
		ERROR_ENTRY(124, "��������� ���������� ����� � ������� ���������������"),
		ERROR_ENTRY(125, "� ������� ��������������� ����������� ������ � �������� �������"),
		ERROR_ENTRY_NODEF(126),ERROR_ENTRY_NODEF(127),ERROR_ENTRY_NODEF(128),ERROR_ENTRY_NODEF(129),
		ERROR_ENTRY(130, "��������� ������� ������� �������"),
		ERROR_ENTRY(131, "��������� ����������� ������� � ������� �������"),
		ERROR_ENTRY(132, "������ � ���������� ��������� ������ �� ������"),
		ERROR_ENTRY(133, "������ � �������� ���������� ��������"),
		ERROR_ENTRY(134, "����������� ������� �� ����� ������"),
		ERROR_ENTRY_NODEF(135),ERROR_ENTRY_NODEF(136),ERROR_ENTRY_NODEF(137),ERROR_ENTRY_NODEF(138),ERROR_ENTRY_NODEF(139),
		ERROR_ENTRY_NODEF10(140),ERROR_ENTRY_NODEF10(150),
		ERROR_ENTRY_NODEF10(160),ERROR_ENTRY_NODEF10(170),ERROR_ENTRY_NODEF10(180),ERROR_ENTRY_NODEF10(190),
		ERROR_ENTRY_NODEF100(200),ERROR_ENTRY_NODEF100(300),ERROR_ENTRY_NODEF100(400),ERROR_ENTRY_NODEF100(500),
		ERROR_ENTRY(600, "�������� ��������� ���������"),
		ERROR_ENTRY(601, "��������� ��������"),
		ERROR_ENTRY(602, "������ � ���������"),
		ERROR_ENTRY(603, "������ � ���������� �������"),
		ERROR_ENTRY(604, "������ � ���������� ���������� �������"),
		ERROR_ENTRY_NODEF(605), ERROR_ENTRY_NODEF(606), ERROR_ENTRY_NODEF(607), ERROR_ENTRY_NODEF(609),
		ERROR_ENTRY_NODEF10(610), ERROR_ENTRY_NODEF10(620), ERROR_ENTRY_NODEF10(630), ERROR_ENTRY_NODEF10(640),
		ERROR_ENTRY_NODEF10(660), ERROR_ENTRY_NODEF10(670), ERROR_ENTRY_NODEF10(680), ERROR_ENTRY_NODEF10(690),
		ERROR_ENTRY_NODEF100(700),ERROR_ENTRY_NODEF100(800),ERROR_ENTRY_NODEF100(900),
	};

	ERROR geterror(int id)
	{
		ERROR error_info;
		if (id > 0 && id < ERROR_MAXSIZE_MESSAGE)
		{
			error_info.id = errors[id].id;
			strcpy(error_info.message, errors[id].message);
			error_info.inext.col = -1;
			error_info.inext.line = -1;
		}
		else
		{
			error_info.id = errors[0].id;
			strcpy(error_info.message, errors[0].message);
		}
		return error_info;
	}

	ERROR geterrorin(int id, int line, int col)
	{
		ERROR error_info;
		if (id > 0 && id < ERROR_MAXSIZE_MESSAGE)
		{
			error_info.id = errors[id].id;
			error_info.inext.col = col + 1;
			error_info.inext.line = line + 1;
			strcpy(error_info.message, errors[id].message);
			return error_info;
		}
		else
		{
			error_info.id = 0;
			error_info.inext.col = -1;
			error_info.inext.line = -1;
			strcpy(error_info.message, errors[0].message);
			return error_info;
		}
	};
};