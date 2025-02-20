#pragma once
#include "Greibach.h"

#define GRB_ERROR_SERIES 600
#define NS(n)	GRB::Rule::Chain::N(n)
#define TS(n)	GRB::Rule::Chain::T(n)
#define ISNS(n)	GRB::Rule::Chain::isN(n)

namespace GRB
{
	Greibach greibach(
		NS('S'), TS('$'),                     // ��������� ������, ��� �����
		9,									  // ���������� ������
		Rule(
			NS('S'), GRB_ERROR_SERIES + 0,    // �������� ��������� ���������
			8,                                // 
			Rule::Chain(5, TS('m'), TS('{'), NS('N'), TS('}'), TS(';')),
			Rule::Chain(6, TS('m'), TS('{'), NS('N'), TS('}'), TS(';'), NS('S')),
			Rule::Chain(11, TS('d'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS('{'), NS('N'), TS('}'), TS(';'), NS('S')),
			Rule::Chain(10, TS('d'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS('{'), NS('N'), TS('}'), TS(';')),
			Rule::Chain(11, TS('b'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS('{'), NS('N'), TS('}'), TS(';'), NS('S')),
			Rule::Chain(10, TS('b'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS('{'), NS('N'), TS('}'), TS(';')),
			Rule::Chain(11, TS('s'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS('{'), NS('N'), TS('}'), TS(';'), NS('S')),
			Rule::Chain(10, TS('s'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS('{'), NS('N'), TS('}'), TS(';'))
		),
		Rule(
			NS('N'), GRB_ERROR_SERIES + 1,    // ����������� � ��������
			26,                               // 
			Rule::Chain(5, TS('n'), NS('T'), TS('i'), TS(';'), NS('N')),
			Rule::Chain(7, TS('n'), NS('T'), TS('i'), TS('='), NS('E'), TS(';'), NS('N')),
			Rule::Chain(4, TS('n'), NS('T'), TS('i'), TS(';')),
			Rule::Chain(6, TS('n'), NS('T'), TS('i'), TS('='), NS('E'), TS(';')),
			Rule::Chain(4, TS('i'), TS('='), NS('E'), TS(';')),
			Rule::Chain(5, TS('i'), TS('='), NS('E'), TS(';'), NS('N')),
			Rule::Chain(4, TS('o'), NS('L'), TS(';'), NS('N')),
			Rule::Chain(3, TS('o'), NS('L'), TS(';')),
			Rule::Chain(4, TS('_'), NS('L'), TS(';'), NS('N')),
			Rule::Chain(3, TS('_'), NS('L'), TS(';')),
			Rule::Chain(6, TS('p'), TS('('), NS('W'), TS(')'), TS(';'), NS('N')),
			Rule::Chain(5, TS('p'), TS('('), NS('W'), TS(')'), TS(';')),
			Rule::Chain(6, TS('a'), TS('('), NS('W'), TS(')'), TS(';'), NS('N')),
			Rule::Chain(5, TS('a'), TS('('), NS('W'), TS(')'), TS(';')),
			Rule::Chain(6, TS('i'), TS('('), NS('W'), TS(')'), TS(';'), NS('N')),
			Rule::Chain(5, TS('i'), TS('('), NS('W'), TS(')'), TS(';')),
			Rule::Chain(5, TS('i'), TS('('), TS(')'), TS(';'), NS('N')),
			Rule::Chain(4, TS('i'), TS('('), TS(')'), TS(';')),
			Rule::Chain(6, TS('q'), NS('Q'), TS('{'), NS('N'), TS('}'), NS('N')),
			Rule::Chain(5, TS('q'), NS('Q'), TS('{'), NS('N'), TS('}')),
			Rule::Chain(9, TS('q'), NS('Q'), TS('{'), NS('N'), TS('}'), TS('2'), TS('{'), NS('N'), TS('}')),
			Rule::Chain(10, TS('q'), NS('Q'), TS('{'), NS('N'), TS('}'), TS('2'), TS('{'), NS('N'), TS('}'), NS('N')),
			Rule::Chain(6, TS('w'), NS('Q'), TS('{'), NS('N'), TS('}'), NS('N')),
			Rule::Chain(5, TS('w'), NS('Q'), TS('{'), NS('N'), TS('}')),
			Rule::Chain(4, TS('r'), NS('E'), TS(';'), NS('N')),
			Rule::Chain(3, TS('r'), NS('E'), TS(';'))
		),
		Rule(
			NS('E'), GRB_ERROR_SERIES + 2,    // ������ � ���������
			14,                               // 
			Rule::Chain(1, TS('i')),
			Rule::Chain(1, TS('l')),
			Rule::Chain(3, TS('('), NS('E'), TS(')')),
			Rule::Chain(4, TS('i'), TS('('), NS('W'), TS(')')),
			Rule::Chain(3, TS('i'), TS('('), TS(')')),
			Rule::Chain(4, TS('p'), TS('('), NS('W'), TS(')')),
			Rule::Chain(4, TS('a'), TS('('), NS('W'), TS(')')),
			Rule::Chain(2, TS('i'), NS('M')),
			Rule::Chain(2, TS('l'), NS('M')),
			Rule::Chain(4, TS('('), NS('E'), TS(')'), NS('M')),
			Rule::Chain(5, TS('i'), TS('('), NS('W'), TS(')'), NS('M')),
			Rule::Chain(4, TS('i'), TS('('), TS(')'), NS('M')),
			Rule::Chain(5, TS('p'), TS('('), NS('W'), TS(')'), NS('M')),
			Rule::Chain(5, TS('a'), TS('('), NS('W'), TS(')'), NS('M'))
		),
		Rule(
			NS('F'), GRB_ERROR_SERIES + 3,    // ������ � ���������� �������
			6,                                // 
			Rule::Chain(2, TS('d'), TS('i')),
			Rule::Chain(2, TS('s'), TS('i')),
			Rule::Chain(2, TS('b'), TS('i')),
			Rule::Chain(4, TS('d'), TS('i'), TS(','), NS('F')),
			Rule::Chain(4, TS('s'), TS('i'), TS(','), NS('F')),
			Rule::Chain(4, TS('b'), TS('i'), TS(','), NS('F'))
		),
		Rule(
			NS('W'), GRB_ERROR_SERIES + 4,    // ������ � ���������� ���������� ������� 
			12,                                // 
			Rule::Chain(1, TS('i')),
			Rule::Chain(1, TS('l')),
			Rule::Chain(3, TS('i'), TS(','), NS('W')),
			Rule::Chain(3, TS('l'), TS(','), NS('W')),
			Rule::Chain(3, TS('i'), TS('('), TS(')')),
			Rule::Chain(5, TS('i'), TS('('), TS(')'), TS(','), NS('W')),
			Rule::Chain(4, TS('i'), TS('('), NS('W'), TS(')')),
			Rule::Chain(6, TS('i'), TS('('), NS('W'), TS(')'), TS(','), NS('W')),
			Rule::Chain(4, TS('p'), TS('('), NS('W'), TS(')')),
			Rule::Chain(6, TS('p'), TS('('), NS('W'), TS(')'), TS(','), NS('W')),
			Rule::Chain(4, TS('a'), TS('('), NS('W'), TS(')')),
			Rule::Chain(6, TS('a'), TS('('), NS('W'), TS(')'), TS(','), NS('W'))
		),
		Rule(
			NS('M'), GRB_ERROR_SERIES + 5,    // ��������
			14,								  //
			Rule::Chain(2, TS('+'), NS('E')),
			Rule::Chain(3, TS('+'), NS('E'), NS('M')),
			Rule::Chain(2, TS('-'), NS('E')),
			Rule::Chain(3, TS('-'), NS('E'), NS('M')),
			Rule::Chain(2, TS('/'), NS('E')),
			Rule::Chain(3, TS('/'), NS('E'), NS('M')),
			Rule::Chain(2, TS('*'), NS('E')),
			Rule::Chain(3, TS('*'), NS('E'), NS('M')),
			Rule::Chain(2, TS('%'), NS('E')),
			Rule::Chain(3, TS('%'), NS('E'), NS('M')),
			Rule::Chain(2, TS('!'), NS('L')),
			Rule::Chain(2, TS('&'), NS('L')),
			Rule::Chain(2, TS('>'), NS('L')),
			Rule::Chain(2, TS('<'), NS('L'))
		),
		Rule(
			NS('Q'), GRB_ERROR_SERIES + 6,		// �������� ���������
			4,									// Q->  (L<L)  |  (L>L)
			Rule::Chain(5, TS('('), NS('L'), TS('<'), NS('L'), TS(')')),
			Rule::Chain(5, TS('('), NS('L'), TS('>'), NS('L'), TS(')')),
			Rule::Chain(5, TS('('), NS('L'), TS('!'), NS('L'), TS(')')),
			Rule::Chain(5, TS('('), NS('L'), TS('&'), NS('L'), TS(')'))
		),
		Rule(
			NS('L'), GRB_ERROR_SERIES + 6,		// �������� � ��������������
			2,									// L->  (l)  |  (i)
			Rule::Chain(1, TS('l')),
			Rule::Chain(1, TS('i'))
		),
		Rule(
			NS('T'), GRB_ERROR_SERIES + 7,
			3,
			Rule::Chain(1, TS('d')),
			Rule::Chain(1, TS('s')),
			Rule::Chain(1, TS('b'))
		)
	);
}