
#pragma once
#include "stdafx.h"
#include "Helper.h"
#include "Config.h"
#include <conio.h>


void helper::solve()
{
	std::cout << "Algorytm Kognitywistyczny rozpoczyna pracÍ." << std::endl;
	while (won == false)
	{
	help();
	display();
	act();
	}			
}

void helper::createPriorityList()
{
	const int SIZE = b->size;
	int sizeSq = SIZE*SIZE;
	int index = 0;
	for (int ob = 0; ob < SIZE - 3; ob++)
	{
		int k;
		for (k = 1; k <= SIZE - ob; k++)
		{
			priorities[index++] = ob*SIZE + k;
		}
		for (int w = k - 1 + ob + SIZE*(ob + 1); w <= sizeSq - SIZE; w += SIZE)
		{
			priorities[index++] = w - ob;
		}
		priorities[index++] = sizeSq - ob - 1;
	}
	for (int w = SIZE - 3; w < SIZE; w++)
	{
		for (int k = 0; k < 3; k++)
		{
			priorities[index++] = w*SIZE + k + 1;
		}
	}
	priorities[index - 1] = sizeSq;//flagowy koncowy
}
int helper::findPriority()
{
	checkForImpassC();
	int prio = priorities[prioIndex++];
	states[prio] = 1;
	return prio;


}
void helper::goFarRight()
{
	bool moved = false;
	bool moved1 = false;
	bool moved2 = false;


	do {
		moved1 = moved2 = false;
		if (b->posOfZero.x < b->size - 1)
			if (states[b->tab[b->posOfZero.y][b->posOfZero.x + 1]] == 0)
				moved1 = b->move(pos::keyToDelta(RIGHT));


		if (b->posOfZero.y < b->size - 1)
			if (states[b->tab[b->posOfZero.y + 1][b->posOfZero.x]] == 0)
				moved2 = b->move(pos::keyToDelta(DOWN));

		display();
		moved = moved1 || moved2;
	} while (moved == true);//tak d≥ugo jak siÍ poruszy≥
}
bool helper::checkForImpassC()
{//s≥uøy do wkrÍcania ostatnich pionÛw
	int sizeSq = b->size*b->size;
	int min = sizeSq - (b->size - 3);
	for (min;min < sizeSq;min++)
	{
		if (states[min] == true && won == false && b->getValueAtIndex(min) == min)
		{//
			impass = 'C';
			goFarRight();
			resolveImpassC(min);
			return 1;
		}
	}
	return 0;
}
bool helper::checkForImpassA()
{
	//gotoxy(1, KOGNIYPOS);
	//b->display();
	int c = b->posOfZero.x;
	int r = b->posOfZero.y;
	if (r - 1 >= 0 && c + 1 < b->size)
	{
		if (states[b->getNumber(r + -1, c + 1)] == 1)
			return false;
	}
	else return false;
	//szukamy jakiejkolwiek luki u gÛry
	for (int i = r - 1; i >= 0; i--)//moøliwa mikrooptymalizacja do i > r - 3, powinno styknπÊ sprawdziÊ 2 w gÛrÍ(ostroønie z 0???)
	{
		if (states[b->getNumber(i, c)] == 0)//jest luka, to tam idü
			return false;
	}
	//szukamy jakiejkolwiek luki u w prawo
	for (int i = c + 1; i < b->size; i++)
	{
		if (states[b->getNumber(r, i)] == 0)//jest luka, to tam idü
			return false;
	}
	return true;
}
bool helper::checkForImpassB()
{
	int down = b->size - 1, left = 0;
	if (b->posOfZero == pos{ down,left }
		&&	states[b->tab[down + 0][left + 1]] == 1//x right
		&& states[b->tab[down - 1][left + 0]] == 1)//y up
		return true;
	return false;

}

pos helper::findSimpleMove()
{
	pos out = pos{ 0,0 };
	//horizontal normal

	bool l;
	bool r;
	bool t;
	bool d;



	if (blankDeltaPos.x > 0 && !tempSideX && !states[b->tab[b->posOfZero.y][b->posOfZero.x + 1]])
	{
		//move right
		out.x = 1;
		tempSideY = false;
	}
	else if (blankDeltaPos.x < 0 && !tempSideX && !states[b->tab[b->posOfZero.y][b->posOfZero.x - 1]])
	{
		//move left
		out.x = -1;
		tempSideY = false;
	}
	//vertical normal
	else if (blankDeltaPos.y < 0 && !tempSideY && !states[b->tab[b->posOfZero.y - 1][b->posOfZero.x]])
	{
		//move up
		out.y = -1;
		tempSideX = false;
	}
	else if (blankDeltaPos.y > 0 && !tempSideY && !states[b->tab[b->posOfZero.y + 1][b->posOfZero.x]])
	{
		//move down
		out.y = 1;
		tempSideX = false;
	}
	//horizontal okolo														//potencjalnie wychodzπce za tablice, jeúli koniunkcja nie wyjdzie
	else if (blankDeltaPos.x == 0 && b->posOfZero.x + 1 < b->size	&& states[b->tab[b->posOfZero.y][b->posOfZero.x + 1]] == 0)
	{
		//wanna stay but can  move right
		out.x = +1;
		tempSideX = true;
	}
	else if (blankDeltaPos.x == 0 && b->posOfZero.x - 1 >= 0 && states[b->tab[b->posOfZero.y][b->posOfZero.x - 1]] == 0)
	{
		//wanna stay but can  move left
		out.x = -1;
		tempSideX = true;
	}
	else if (blankDeltaPos.y == 0 && b->posOfZero.y + 1 < b->size	&& states[b->tab[b->posOfZero.y + 1][b->posOfZero.x]] == 0)
	{
		//wanna stay but can  move down
		out.y = +1;
		tempSideY = true;
	}
	else if (blankDeltaPos.y == 0 && b->posOfZero.y - 1 >= 0 && states[b->tab[b->posOfZero.y - 1][b->posOfZero.x]] == 0)
	{

		//// jesli idziesz ustawiamy pion,
		//if (lata && blankDeltaPos.x > 0 && b->posOfZero.x - 1 >= 0 && states[b->tab[b->posOfZero.y][b->posOfZero.x - 1]] == 0)
		//{
		//	//wanna go right but can  move left
		//	out.x = -1;
		//	tempSideX = true;

		//}
		//	else
		{
			out.y = -1;
			tempSideY = true;
		}

		//wanna stay but can  move up

	}
	else if (blankDeltaPos.y < 0 && b->posOfZero.y + 1 < b->size		&& states[b->tab[b->posOfZero.y + 1][b->posOfZero.x]] == 0)
	{
		//wanna go up but can only move down
		out.y = +1;
		tempSideY = true;
	}
	else if (blankDeltaPos.x > 0 && b->posOfZero.x - 1 >= 0 && states[b->tab[b->posOfZero.y][b->posOfZero.x - 1]] == 0)
	{
		//wanna go right but can  move left
		out.x = -1;
		tempSideX = true;
	}
	else if (blankDeltaPos.y > 0 && b->posOfZero.y - 1 >= 0 && states[b->tab[b->posOfZero.y - 1][b->posOfZero.x]] == 0)
	{
		//wanna go down but can only move up
		out.y = -1;
		tempSideY = true;
	}

	else
	{
		out.x = 9;
		out.y = 9;
	}
	return out;


}
void helper::displayStates()
{
	std::cout << "tablica gotowych pÛl: ";
	for (int i = 1; i <= b->size*b->size; i++)
	{
		std::cout << states[i];
	}
}
void helper::resolveImpassA()
{
	tempSideX = 0;
	tempSideY = 0;
	const int num = 9;
	int moves[9] = { LEFT,UP,RIGHT,RIGHT,DOWN,LEFT,UP,LEFT,DOWN };
	for (int i = 0; i < num; i++)
	{
		b->move(pos::keyToDelta(moves[i]));
		if(i!=num-1)
		display();
	}

}
void helper::resolveImpassB()
{
	tempSideX = 0;
	tempSideY = 0;
	const int num = 8;
	int moves[9] = { UP,RIGHT,DOWN,RIGHT,UP,LEFT,LEFT,DOWN };
	for (int i = 0; i < num; i++)
	{
		b->move(pos::keyToDelta(moves[i]));
		if (i != num - 1)
			display();

	}


}

void helper::resolveImpassC(int wkrecana)//wkrÍcanie '15'
{


	tempSideY = 0;
	pos position = b->getNumberToCord(wkrecana);
	if (b->getNumber(position.y, position.x + 1) == 0)
	{
		b->move(pos::keyToDelta(LEFT));
			display();
		return;
	}

	if (b->getNumber(position.y, position.x - 1) == 0)
	{
		b->move(pos::keyToDelta(UP));
		display();

		b->move(pos::keyToDelta(RIGHT));
		display();

	}
	const int num = 9;
	int moves[9] = { UP,RIGHT,DOWN,DOWN,LEFT,UP,RIGHT,UP,LEFT };
	for (int i = 0; i < num; i++)
	{
		b->move(pos::keyToDelta(moves[i]));
		if (i != num - 1)
			display();
	}
}

bool helper::areThereAnyImpasses()
{
	if (checkForImpassA())
	{
		impass = 'A';
		return true;
	}
	else if (checkForImpassB())
	{
		impass = 'B';
		return true;
	}

	else
		return false;
}

void helper::reset()
{
	b->shuffle();
	won = false;
	tempSideX = 0;
	tempSideY = 0;
	prioIndex = 0;
	for (int i = 0; i < b->size*b->size + 1; i++)
	{
		states[i] = 0;
	}
	currentPriority = findPriority();
}

helper::helper()
{
}

helper::helper(Board * b)
{
	this->b = b;
	int sizeSq = b->size*b->size;
	states = new bool[sizeSq];
	tabOfVerticalNeeds = new bool[sizeSq];
	//NEW BEZ DELETE WYCIEK
	priorities = new int[sizeSq];
	//NEW BEZ DELETE WYCIEK
	createPriorityList();
	reset();
	populateUnorderedSet();
}
bool helper::checkForWin()
{
	return states[b->size*b->size - b->size + 2];
}
void helper::display()
{
	if (SHOWHELP)
	{
		gotoxy(1, KOGNIYPOS);
		b->display();		
		gotoxy(1, KOGNIYPOS+BOARDSIZE*2);
		displayHelp();
		if (won)return;
		if(STOPOWANIE)
		_getch();
	}

}
void helper::displayHelp()
{
	//find simple path of blank

	if (won)
	{
		std::cout << "Wygrana!                                                 "<< std::endl;
		for (int i = 0; i < 5; i++)
		{
			std::cout << "                                                      "<< std::endl;
		}
		return;
	}
	std::cout << "obecnie ustawiany : " << currentPriority << "    " << std::endl;
	//std::cout << "it is at\t: " << currentPos << "\t" << std::endl;
	//std::cout << "it should be at\t: " << desiredPos << "\t" << std::endl;
	//std::cout << "difference is\t: " << deltaPos << "\t" << std::endl;
	//std::cout << "move it\t\t: " << dirPos << "\t" << std::endl;
	//std::cout << "blank is at\t: " << b->posOfZero << "\t" << std::endl;
	//std::cout << "blank sh be at\t: " << blankDesiredPos << "\t" << std::endl;
	//std::cout << "difference is\t: " << blankDeltaPos << "\t" << std::endl;
	//std::cout << "X - " << (tempSideX ? "true" : "false") << "\t" << std::endl;
	//std::cout << "Y - " << (tempSideY ? "true" : "false") << "\t" << std::endl;
	//std::cout << "lata" << lata << "\t" << std::endl;
	displayStates();
	std::cout << std::endl;
	if ((char)impass != '0')
		std::cout << "impass: " << (char)impass <<"                        " <<std::endl;
	else
		std::cout << "next move will be " << nextMove.toString() << "  " << std::endl;
	//

}

void helper::populateUnorderedSet()
{
	int size = b->size;

	for (int k = 3; k < size; k++)
	{
		for (int w = 0; w <= k - 3; w++)
		{
			int wkladany = size*(size - 2 - w) + k + 1;
			//	std::cout << wkladany << " ";
			tabOfVerticalNeeds[wkladany] = true;;

		}
	}
}
void helper::specialCasesSuperLatka()
{

	lata = false;
	if (tabOfVerticalNeeds[currentPriority] == 1)
	{
		lata = true;
		if (deltaPos.y > 0)
			dirPos = pos{ 1,0 };
	}
}
void helper::help()
{
	while (b->getValueAtIndex(currentPriority) == currentPriority)
	{
		currentPriority = findPriority();
	}

	if (won = checkForWin())
	{
		won = true;
		return;
	}

	impass = '0';
	currentPos = b->findPosOf(currentPriority);
	desiredPos = b->getNumberToCord(currentPriority);
	deltaPos = desiredPos - currentPos;
	dirPos = pos::DeltaToDir(deltaPos);
	specialCasesSuperLatka();//sprawdü czy nie powinien najpierw chcieÊ iúÊ w dÛ≥

	blankDesiredPos = currentPos + dirPos;
	blankDeltaPos = blankDesiredPos - b->posOfZero;
	if (b->posOfZero == blankDesiredPos)
	{
		nextMove = (dirPos*-1);
		tempSideY = 0;
		tempSideX = 0;
	}
	else if (areThereAnyImpasses() == false)
		nextMove = findSimpleMove();

}
void helper::act()
{
	if (impass == 'A')
		resolveImpassA();
	else if (impass == 'B')
		resolveImpassB();
	else if (impass == 'C')
		resolveImpassA();
	else if (b->move(nextMove) == 0)
	{

	}

}
