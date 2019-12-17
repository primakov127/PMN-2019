#pragma once

#define TI_MAXSIZE      4096                    // ������������ ���������� ����� � ������� ���������������
#define TI_INT_DEFAULT  0x00000000              // �������� �� ��������� ��� ���� integer
#define TI_STR_DEFAULT  0x00                    // �������� �� ��������� ��� ���� string
#define TI_NULLIDX      0xffffffff              // ��� �������� ������� ���������������
#define TI_STR_MAXSIZE  255                     // ������������ ������ ������

namespace IT                                    // ������� ���������������
{
	enum IDDATATYPE 
	{ NON = 0, INT = 1, STR = 2, BOOL = 3 };					// ���� ������ ���������������: integer, string 

	enum IDTYPE 
	{ 
		N = 0,			// ��� ����
		F = 1,			// �������
		V = 2,			// ����������
		P = 3,			// �������� � �������
		L = 4			// �������
	};		// ���� ���������������: ����������, �������, ��������, �������

	struct Entry                                // ������ ������� ���������������
	{
		int         idxfirstLE;                 // ������ ������� ��������� � ������� ������
		std::string id;							// �������������
		IDDATATYPE  idDataType;                 // ��� ������
		IDTYPE      idType;                     // ��� ���������������
		struct
		{
			int vint;                           // �������� integer
			struct
			{
				int len;						// ���������� �������� � string
				std::string str;				// ������� string
			} vstr;								// �������� string
		} value;                                // �������� ��������������
	};

	struct IdTable                              // ��������� ������� ���������������
	{
		int maxsize;                            // ������� ������� ��������������� < TI_MAXSIZE
		int size;                               // ������� ������ ������� ��������������� < maxsize
		Entry* table;                           // ������ ����� ������� ���������������
	};

	IdTable Create(                             // ������� ������� ���������������
		int size                                // ������� ������� ��������������� < TI_MAXSIZE
	);

	void Add(                                   // �������� ������ � ������� ���������������
		IdTable& idtable,                       // ��������� ������� ���������������
		Entry entry                             // ������ ������� ���������������
	);

	Entry GetEntry(                             // �������� ������ ������� ���������������
		IdTable& idtable,                       // ��������� ������� ���������������
		int n                                   // ����� ���������� ������
	);

	int IsId(                                   // �������: ����� ������ (���� ����), TI_NULLDX(���� ���)
		IdTable& idtable,                       // ��������� ������� ���������������
		std::string id							// �������������
	);

	void Delete(IdTable& idtable);              // ������� ������� ������ (���������� ������)
	Entry createEntry(int lineLT, std::string id, IDDATATYPE idDataType, IDTYPE idType);
	Entry createEntry(int lineLT, std::string id, IDDATATYPE idDataType, IDTYPE idType, int vint);
	Entry createEntry(int lineLT, std::string id, IDDATATYPE idDataType, IDTYPE idType, std::string vstr);
	void showTable(IdTable& idtable, wchar_t outfile[]);
}