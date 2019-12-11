#include "pch.h"
#pragma once

struct Entry
{
	int index;
	int countOfParam;
	IT::IDDATATYPE types[8];
};

struct Functions
{
	int maxsize;
	int size;
	Entry* table;
};


Functions Create(int size);
void Add(Functions& functions, Entry entry);

void CallSemantic(LT::LexTable& lextable, IT::IdTable& idtable);
void CheckBuiltInFunParam(LT::LexTable& lextable, IT::IdTable& idtable);
void CheckTypeMatching(LT::LexTable& lextable, IT::IdTable& idtable);
void FillFunctions(Functions& functions, IT::IdTable& idtable);
void CheckReturnType(LT::LexTable& lextable, IT::IdTable& idtable);
void CheckFunParam(Functions& functions, IT::IdTable& idtable, LT::LexTable& lextable);
bool isEqual(Entry& entry1, Entry& entry2);