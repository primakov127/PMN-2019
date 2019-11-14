﻿#ifndef PCH_H
#define PCH_H
#define LENGTHOF(x)(sizeof(x)/sizeof(*x))
#define _CRT_SECURE_NO_WARNINGS

#include <SDKDDKVer.h>
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <fstream>
#include <ctime>
#include <mbstring.h>
#include <iomanip>
#include <string>

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

// лексический анализатор
//#include "LEX.h"
// польская запись
//#include "PolishNotation.h"
//#include "Greibach.h"
//#include "MFST.h"

#endif //PCH_H
