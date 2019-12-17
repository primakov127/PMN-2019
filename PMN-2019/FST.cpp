#include "pch.h"

namespace FST
{
	/*Реализация коснтрукторов структур*/

	RELATION::RELATION(char c, short nn)			// конструктор с параметрами
	{
		symbol = c;
		nnode = nn;
	};

	NODE::NODE()									// конструктор по умолчанию
	{
		n_relation = 0;
		relations = nullptr;
	};

	NODE::NODE(short n, RELATION rel, ...)			// конструктор с параметрами
	{
		n_relation = n;
		RELATION *p = &rel;
		relations = new RELATION[n];
		for (short i = 0; i < n; i++) relations[i] = p[i];
	};

	FST::FST(char* s, short ns, NODE n, ...)		// конструктор с параметрами
	{
		string = s;
		nstates = ns;
		nodes = new NODE[ns];
		NODE *p = &n;
		for (int k = 0; k < ns; k++)
			nodes[k] = p[k];
		rstates = new short[nstates];
		memset(rstates, 0xff, sizeof(short)*nstates);
		rstates[0] = 0;
		position = -1;
	};

	FST::FST(short ns, NODE n, ...)
	{
		nstates = ns;
		nodes = new NODE[ns];
		NODE *p = &n;
		for (int k = 0; k < ns; k++)
			nodes[k] = p[k];
		rstates = new short[nstates];
		memset(rstates, 0xff, sizeof(short)*nstates);
		rstates[0] = 0;
		position = -1;

	}

	FST::FST(char* s, FST& fst)
	{
		this->nodes = new NODE[fst.nstates];
		NODE* temp = fst.nodes;
		short i = 0;
		this->string = s;
		this->nstates = fst.nstates;
		this->rstates = new short[this->nstates];
		while (i < nstates)
		{
			this->nodes[i] = *(temp + i);
			i++;
		};
		rstates[0] = 0;
		position = -1;
	}


	/*Реализация ф-ции execute()*/

	bool step(FST& fst, short* &rstates)							// один шаг автомата
	{
		bool rc = false;
		std::swap(rstates, fst.rstates);							// смена массивов
		for (short i = 0; i < fst.nstates; i++)
		{
			if (rstates[i] == fst.position)
				for (short j = 0; j < fst.nodes[i].n_relation; j++)
				{
					if (fst.nodes[i].relations[j].symbol == fst.string[fst.position])
					{
						fst.rstates[fst.nodes[i].relations[j].nnode] = fst.position + 1;
						rc = true;
					}
				}
		}
		return rc;
	};

	bool execute(FST& fst)												// выполнить распознование цепочки
	{
		short* rstates = new short[fst.nstates];
		memset(rstates, 0xff, sizeof(short)*fst.nstates);
		short lstring = strlen(fst.string);
		bool rc = true;
		for (short i = 0; i < lstring && rc; i++)
		{
			fst.position++;												// продвинули одну позицию
			rc = step(fst, rstates);									// один шаг автомата
		}
		delete[] rstates;
		return (rc ? (fst.rstates[fst.nstates - 1] == lstring) : rc);
	};
}