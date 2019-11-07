#ifndef PCH_H
#define PCH_H

#define _CRT_SECURE_NO_WARNINGS

#include <SDKDDKVer.h>
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <fstream>
#include <ctime>
#include <mbstring.h>

// Работа с протоколом
#include "Log.h"
// Обработка ошибок
#include "Error.h"
// Обработка параметров
#include "Parm.h"
// Ввод исходного файла
#include "In.h"
// Разбиение на лексемы
#include "TOKEN.h"

//#include "LT.h"
//#include "IT.h"
// реализация КА + ф-ция разбора
//#include "FST.h"
// лексический анализатор
//#include "LEX.h"
// польская запись
//#include "PolishNotation.h"
//#include "Greibach.h"
//#include "MFST.h"

#endif //PCH_H
