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

// работа с протоколом
#include "Log.h"
// обработка ошибок
#include "Error.h"
// обработка параметров
#include "Parm.h"
// ввод исходного файла
#include "In.h"

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
