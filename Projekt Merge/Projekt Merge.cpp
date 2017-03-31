// Projekt Merge.cpp : Defines the entry point for the console application.
//

#pragma once
#include "stdafx.h"
#include "Helper.h"
#include "Config.h"
#include <time.h>
#include <stdlib.h>
#include <conio.h>

class Analizer {

	int ticks = 1;
	clock_t begin_time;
	clock_t endtime;
	clock_t deltatime;
	double avg;
public:
	Analizer()
	{
		srand(time(NULL));
	}
	void tick()
	{
		begin_time = clock();
	}
	void tack() {
		endtime = clock();
		deltatime = endtime - begin_time;
		avg = ((float)deltatime / ticks + avg*(ticks - 1) / ticks);
		std::cout << "time:" << deltatime << std::endl;
		std::cout << "avg time:" << avg << std::endl;
		std::cout << "i:" << ticks << std::endl;
		ticks++;
	}
	void tackAndTick()
	{
		tack();
		tick();
	}
};
int main()
{
	board * b = new board(BOARDSIZE);
	helper * h = new helper(b);
	Analizer anal;
	//player * p = new player(b, h);
	//unsigned int tic = clock();	
	if (WAITFORSTART)
		_getch();

	anal.tick();

	while (true)
	{
		gotoxy(1, 2);
		h->help();
		h->display();
		//h->displayHelp();
		if (h->won)
		{
			std::cout << "moves:" << b->timesMoved << std::endl;
			anal.tackAndTick();
			gotoxy(1, 2);
			h->display();
			
			if (TESTCONSTWIN == false)
				_getch();
			b->shuffle();
			h->reset();
		}
		else
		{
			h->act();//p->turn();	
		}
	}
	return 0;
}