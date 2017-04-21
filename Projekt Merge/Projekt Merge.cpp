// Projekt Merge.cpp : Defines the entry point for the console application.
//

#pragma once
#include "stdafx.h"
#include "Helper.h"
#include "Config.h"
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include "Riddle.h"

class Analiser {

	double ticks = 1;
	clock_t begin_time;
	clock_t endtime;
	clock_t deltatime;
	double avg;
	double avgMoves;
public:
	void reset()
	{
		ticks = 1;
		avg = 0;
		avgMoves = 0;
	}
	Analiser()
	{
		reset();
		srand(time(NULL));
	}
	void tick()
	{
		begin_time = clock();
	}
	void tack(int moves) {
		endtime = clock();
		deltatime = endtime - begin_time;
		avg = ((double)deltatime / ticks + avg*(ticks - 1) / ticks);
		avgMoves = ((double)moves / ticks + avgMoves*(ticks - 1) / ticks);
		if (SHOWHELP == false)
			std::cout << "time:  " << deltatime << " [ms]" << std::endl;
		std::cout << "moves: " << moves << std::endl;

		ticks++;
	}

};
int BOARDSIZE = 3;
int SHOWHELP = 0;
int STOPOWANIE = 1;
int ABANDON = 0;
int main()
{
	Analiser anal;

	while (1)
	{
		system("cls");
		cout << "Solver uk³adanki 3x3 +" << endl;
		cout << "Jakub Jab³oñski i Krzysztof Œwiêtnicki SI 2017" << endl;
		cout << "(uwaga, interfejs nieodporny na niepoprawny input typu rozmiar uk³adanki -2)" << endl;
		cout << endl;
		cout << "Podaj rozmiar uk³adanki, np. 3." << endl;
		cin >> BOARDSIZE;

		cout << endl << "Wybierz algorytm:" << endl;
		cout << "1 - kognitywistyczny" << endl;
		cout << "2 - heurystyka inwersji" << endl;
		cout << "3 - heurystyka onplace" << endl;
		cout << "4 - heurystyka dystansu" << endl;
		cout << "5 - zwyk³y dfs" << endl;
		cout << "6 - zwyk³y bfs" << endl;
		int algo;
		cin >> algo;
		cout << endl;


		cout << "Czy wyœwietlaæ algorytm krok po kroku 1-tak?, 0-nie." << endl;
		cin >> SHOWHELP;
		if (SHOWHELP == 1 && algo == 1)
		{
			cout << "Czy wyœwietlaæ stany co klik, czy ma lataæ szybko. 1-klik, 0-szybko." << endl;
			cin >> STOPOWANIE;
		}
		cout << endl;
		if (algo == 2 || algo == 3 || algo == 4)
		{
			cout << "Czy algorytm mo¿e porzucaæ ga³êzie, gdy inne s¹ lepiej rokuj¹ce/wczeœniej dodane?  1-tak, 0-nie." << endl;

			cin >> ABANDON;
		}
		Board * b = new Board(BOARDSIZE);
		Riddle * r = new Riddle(BOARDSIZE);
		helper * h = new helper(b);

		anal.tick();
		switch (algo)
		{
		case 1:
			h->solve();
			break;
		case 2:
			r->solveByInversions();
			break;
		case 3:
			r->solveByOnPlace();
			break;
		case 4:
			r->solveByDistance();
			break;
		case 5:
			r->solveByDFS();
			break;
		case 6:
			r->solveByBFS();
			break;
		default:
			break;
		}
		if (algo == 1)
			anal.tack(b->timesMoved);
		else
			anal.tack(r->iloscwyw);



		delete h;
		delete r;
		delete b;

		cout << "Zakoñczono, wpisz 1, jeœli chcesz od nowa, lub 0 jesli chcesz zakonczyc" << endl;
		bool decision;
		cin >> decision;
		if (decision == 0)
			break;
	}

	return 0;
}