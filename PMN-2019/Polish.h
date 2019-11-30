#pragma once
#include "pch.h"
#include "LT.h"
#include "IT.h"
#include <iostream>
#include <stack>
#include <queue>

void CallPolishNotation(LT::LexTable& lextable, IT::IdTable& idtable);
void polishNotation(int lextable_pos, LT::LexTable& lextable, IT::IdTable& idtable);
int priorityIs(LT::Entry entry);
char intToChar(int x);
//void operatorCase(stack<LT::Entry>& stack, queue<LT::Entry>& queue, LT::LexTable& lextable);s