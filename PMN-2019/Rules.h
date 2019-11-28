#pragma once
#include "Greibach.h"

#define GRB_ERROR_SERIES 600
#define NS(n)	GRB::Rule::Chain::N(n)
#define TS(n)	GRB::Rule::Chain::T(n)
#define ISNS(n)	GRB::Rule::Chain::isN(n)

namespace GRB
{
	Greibach greibach(
		NS('S'), TS('$'),                     // стартовый символ, дно стека
		7,									  // количество правил
		Rule(
			NS('S'), GRB_ERROR_SERIES + 0,    // неверная структура программы
			8,                                // 
			Rule::Chain(8, TS('m'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}'), TS(';')),
			Rule::Chain(14, TS('d'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}'), TS(';'), NS('S')),
			Rule::Chain(13, TS('d'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}'), TS(';')),
			Rule::Chain(14, TS('b'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}'), TS(';'), NS('S')),
			Rule::Chain(13, TS('b'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}'), TS(';')),
			Rule::Chain(14, TS('s'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}'), TS(';'), NS('S')),
			Rule::Chain(13, TS('s'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}'), TS(';')),
			Rule::Chain(9, TS('m'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}'), TS(';'), NS('S'))
		),
		Rule(
			NS('N'), GRB_ERROR_SERIES + 1,    // конструкции в функциях
			24,                               // 
			Rule::Chain(5, TS('n'), TS('d'), TS('i'), TS(';'), NS('N')),
			Rule::Chain(5, TS('n'), TS('s'), TS('i'), TS(';'), NS('N')),
			Rule::Chain(5, TS('n'), TS('b'), TS('i'), TS(';'), NS('N')),
			Rule::Chain(4, TS('i'), TS('='), NS('E'), TS(';')),
			Rule::Chain(5, TS('i'), TS('='), NS('E'), TS(';'), NS('N')),
			//Rule::Chain(9, TS('n'), TS('d'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS(';'), NS('N')),
			//Rule::Chain(9, TS('n'), TS('s'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS(';'), NS('N')),
			Rule::Chain(4, TS('o'), TS('i'), TS(';'), NS('N')),
			Rule::Chain(4, TS('o'), TS('l'), TS(';'), NS('N')),
			Rule::Chain(4, TS('o'), NS('E'), TS(';'), NS('N')),
			Rule::Chain(3, TS('o'), NS('E'), TS(';')),
			Rule::Chain(4, TS('n'), TS('d'), TS('i'), TS(';')),
			Rule::Chain(4, TS('n'), TS('s'), TS('i'), TS(';')),
			Rule::Chain(4, TS('n'), TS('b'), TS('i'), TS(';')),
			//Rule::Chain(8, TS('n'), TS('d'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS(';')),
			//Rule::Chain(8, TS('n'), TS('s'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS(';')),
			Rule::Chain(3, TS('o'), TS('i'), TS(';')),
			Rule::Chain(3, TS('o'), TS('l'), TS(';')),
			Rule::Chain(6, TS('p'), TS('('), TS('W'), TS(')'), TS(';'), TS('N')),
			Rule::Chain(5, TS('p'), TS('('), TS('W'), TS(')'), TS(';')),
			Rule::Chain(6, TS('a'), TS('('), TS('W'), TS(')'), TS(';'), TS('N')),
			Rule::Chain(5, TS('a'), TS('('), TS('W'), TS(')'), TS(';')),
			Rule::Chain(6, TS('i'), TS('('), TS('W'), TS(')'), TS(';'), TS('N')),
			Rule::Chain(5, TS('i'), TS('('), TS('W'), TS(')'), TS(';')),
			Rule::Chain(6, TS('q'), NS('Q'), TS('{'), NS('N'), TS('}'), NS('N')),
			Rule::Chain(5, TS('q'), NS('Q'), TS('{'), NS('N'), TS('}')),
			Rule::Chain(9, TS('q'), NS('Q'), TS('{'), NS('N'), TS('}'), TS('2'), TS('{'), NS('N'), TS('}')),
			Rule::Chain(10, TS('q'), NS('Q'), TS('{'), NS('N'), TS('}'), TS('2'), TS('{'), NS('N'), TS('}'), NS('N'))
		),
		Rule(
			NS('E'), GRB_ERROR_SERIES + 2,    // ошибка в выражении
			8,                                // 
			Rule::Chain(1, TS('i')),
			Rule::Chain(1, TS('l')),
			Rule::Chain(3, TS('('), NS('E'), TS(')')),
			Rule::Chain(4, TS('i'), TS('('), NS('W'), TS(')')),
			Rule::Chain(2, TS('i'), NS('M')),
			Rule::Chain(2, TS('l'), NS('M')),
			Rule::Chain(4, TS('('), NS('E'), TS(')'), NS('M')),
			Rule::Chain(5, TS('i'), TS('('), NS('W'), TS(')'), NS('M'))
		),
		Rule(
			NS('F'), GRB_ERROR_SERIES + 3,    // ошибка в параметрах функции
			6,                                // 
			Rule::Chain(2, TS('d'), TS('i')),
			Rule::Chain(2, TS('s'), TS('i')),
			Rule::Chain(2, TS('b'), TS('i')),
			Rule::Chain(4, TS('d'), TS('i'), TS(','), NS('F')),
			Rule::Chain(4, TS('s'), TS('i'), TS(','), NS('F')),
			Rule::Chain(4, TS('b'), TS('i'), TS(','), NS('F'))
		),
		Rule(
			NS('W'), GRB_ERROR_SERIES + 4,    // ошибка в параметрах вызываемой функции 
			4,                                // 
			Rule::Chain(1, TS('i')),
			Rule::Chain(1, TS('l')),
			Rule::Chain(3, TS('i'), TS(','), NS('W')),
			Rule::Chain(3, TS('l'), TS(','), NS('W'))
		),
		Rule(
			NS('M'), GRB_ERROR_SERIES + 5,    // оператор
			10,								  //
			Rule::Chain(2, TS('+'), NS('E')),
			Rule::Chain(3, TS('+'), NS('E'), NS('M')),
			Rule::Chain(2, TS('-'), NS('E')),
			Rule::Chain(3, TS('-'), NS('E'), NS('M')),
			Rule::Chain(2, TS('/'), NS('E')),
			Rule::Chain(3, TS('/'), NS('E'), NS('M')),
			Rule::Chain(2, TS('*'), NS('E')),
			Rule::Chain(3, TS('*'), NS('E'), NS('M')),
			Rule::Chain(2, TS('%'), NS('E')),
			Rule::Chain(3, TS('%'), NS('E'), NS('M'))
		),
		Rule(
			NS('Q'), GRB_ERROR_SERIES + 6,		// Условные операторы
			3,									// Q->  (R<R)  |  (R>R)
			Rule::Chain(5, TS('('), NS('E'), TS('<'), NS('E'), TS(')')),
			Rule::Chain(5, TS('('), NS('E'), TS('>'), NS('E'), TS(')')),
			Rule::Chain(3, NS('E'))
		)
		//Rule(
		//	NS('I'), GRB_ERROR_SERIES + 9,		// if
		//	4,									// 
		//	Rule::Chain(8, TS('q'), TS('('), NS('Q'), TS(')'), TS('{'), NS('N'), TS('}'), NS('N')),
		//	Rule::Chain(7, TS('q'), TS('('), NS('Q'), TS(')'), TS('{'), NS('N'), TS('}')),
		//	Rule::Chain(11, TS('q'), TS('('), NS('Q'), TS(')'), TS('{'), NS('N'), TS('}'), TS('2'), TS('{'), NS('N'), TS('}')),
		//	Rule::Chain(12, TS('q'), TS('('), NS('Q'), TS(')'), TS('{'), NS('N'), TS('}'), TS('2'), TS('{'), NS('N'), TS('}'), NS('N'))
		//)
	);
}