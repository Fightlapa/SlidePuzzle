#pragma once
#include "Board.h"
#include "Pos.h"
class helper {
private:
	int currentPriority;
	int prioIndex;
	Board * b;
	bool * states;
	int * priorities;
	bool * tabOfVerticalNeeds = {};

#define LEFT 4
#define RIGHT 6
#define UP 8
#define DOWN 2


	bool tempSideY = false;
	bool tempSideX = false;
	bool lata = false;
	pos currentPos;
	pos desiredPos;
	pos deltaPos;
	pos dirPos;

	pos blankDesiredPos;
	pos blankDeltaPos;
	pos blankDirPos;

	pos nextMove;
	int impass = '0';
	void createPriorityList();
	int findPriority();
	void goFarRight();
	bool checkForImpassC();
	bool checkForImpassA();
	bool checkForImpassB();

	pos findSimpleMove();
	void displayStates();
	void resolveImpassA();
	void resolveImpassB();

	void resolveImpassC(int wkrecana);

	bool areThereAnyImpasses();

	void populateUnorderedSet();
	void specialCasesSuperLatka();
public:

	bool won = false;
	void reset();
	helper();
	helper(Board * b);
	bool checkForWin();
	void display();
	void displayHelp();
	void solve();
	void help();
	void act();
};