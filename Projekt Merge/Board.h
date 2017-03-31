#pragma once
#include "Pos.h"
class board
{
public:
	int ** tab;
	int ** copyOfOriginal;
	pos posOfZero;
	int size;
	int timesMoved;
	board(int size);
	bool move(int dy, int dx);
	bool move(pos dir);
	void display(int xx, int yy);
	void display();
	int getCordToNumber(int y, int x);
	pos getNumberToCord(int number);
	int getNumber(pos pos);
	int getNumber(int y, int x);
	int getValueAtIndex(int pos);
	pos findPosOf(int number);
	void shuffle();
	void saveCopyToFile(std::ofstream &myfile);
private:
	void makeACopy();
	void riskyShuffle();
	bool isSolvable();
	~board();

	bool isPossible(int y, int x);
	bool mySwap(int y, int x, int ny, int nx);

};