#ifndef PCH_H
#define PCH_H
#define LENGTHOF(x)(sizeof(x)/sizeof(*x))
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE
#define INTEGER_MAX 255

#include <SDKDDKVer.h>
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <fstream>
#include <ctime>
#include <mbstring.h>
#include <iomanip>
#include <string>
#include <stack>

// Работа с протоколом
#include "Log.h"
// Обработка ошибок
#include "Error.h"
// Обработка параметров
#include "Parm.h"
// Ввод исходного файла
#include "In.h"
// Разбиение на токены
#include "TOKEN.h"
// Таблица лексем
#include "LT.h"
// Таблица идентификаторов
#include "IT.h"
// Реализация КА + ф-ция разбора
#include "FST.h"
// Графы для КА
#include "Graphs.h"
// Лексический анализатор
#include "LEX.h"
// Грамматика Грейбах
#include "Greibach.h"
// Реализация КА с магазинной памятью
#include "MFST.h"


// польская запись
//#include "PolishNotation.h"
//#include "Greibach.h"
//#include "MFST.h"

#endif //PCH_H
