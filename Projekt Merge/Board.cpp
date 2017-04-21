#pragma once
#pragma warning(disable:4996)
#include "stdafx.h"
#include "Board.h"
#include "Config.h"
#include <fstream>

	Board::Board(int size)
	{
		this->size = size;
		tab = new int*[size];
		copyOfOriginal = new int*[size];
		for (int i = 0; i < size; i++)
		{
			tab[i] = new int[size];
			copyOfOriginal[i] = new int[size];
		}
		shuffle();
	}
	Board::Board() {};
	Board::~Board()
	{
		/*for (int i = 0; i < 3; i++)
		{
			delete tab[i];
		}
		delete tab;*/
	}
	bool Board::move(int dy, int dx)//by d
	{
		pos dir = { dy,dx };
		return move(dy, dx);
	}
	bool Board::move(pos dir)//z perspektywy 0;
	{
		timesMoved++;
		if (mySwap(posOfZero.y, posOfZero.x, posOfZero.y + dir.y, posOfZero.x + dir.x))
		{
			posOfZero = posOfZero + dir;
			return true;
		}
		return false;
	}
	void Board::display(int xx, int yy)
	{
		gotoxy(xx, yy);
		for (int y = 0; y < size; y++)
		{
			for (int x = 0; x < size; x++)
			{
				if (tab[y][x] != 0)
					std::cout << tab[y][x];
				else std::cout << " ";
			}
			gotoxy(xx, yy + y + 1);
		}
	}
	void Board::display()
	{
		for (int y = 0; y < size; y++)
		{
			for (int x = 0; x < size; x++)
			{
				if (tab[y][x] != 0)
					std::cout << tab[y][x] << "\t";
				else std::cout << "   \t";
			}
			std::cout << std::endl;
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}
	int Board::getCordToNumber(int y, int x)
	{
		return y*size + x + 1;
	}
	pos Board::getNumberToCord(int number)
	{
		number--;
		pos wynik;
		wynik.y = number / size;
		wynik.x = number % size;
		return wynik;
	}
	int Board::getNumber(pos pos) {
		return tab[pos.y][pos.x];
	}
	int Board::getNumber(int y, int x) {
		return tab[y][x];
	}
	int Board::getValueAtIndex(int pos)
	{
		return getNumber(getNumberToCord(pos));
	}
	pos Board::findPosOf(int number)
	{
		pos p;
		for (int y = 0; y < size; y++)
		{
			for (int x = 0; x < size; x++)
			{
				if (tab[y][x] == number)
				{
					p.x = x;
					p.y = y;
					return p;
				}
			}
		}
	}

	void Board::shuffle()
	{
		timesMoved = 0;
		/*if (INPUTBOARD)
		{
			for (int y = 0; y < size; y++)
			{
				for (int x = 0; x < size; x++)
				{
					std::cin >> tab[y][x];
				}
			}
		}
		else*/
		{
			bool solvable = false;
			while (solvable == false)
			{
				riskyShuffle();
				solvable = isSolvable();
			}
		}
		posOfZero = findPosOf(0);
		//makeACopy();
		//display();
	}
	void Board::saveCopyToFile(std::ofstream &myfile)
	{

		for (int y = 0; y < size; y++)
		{
			for (int x = 0; x < size; x++)
			{
				myfile << copyOfOriginal[y][x] << "\t";

			}
			myfile << std::endl;
			myfile << std::endl;
		}
		myfile << std::endl;

	}

	void Board::makeACopy()
	{
		for (int y = 0; y < size; y++)
		{
			for (int x = 0; x < size; x++)
			{
				copyOfOriginal[y][x] = tab[y][x];
			}
		}
	}
	void Board::riskyShuffle()
	{
		int * nums = new int[size*size];
		for (int i = 0; i < size*size; i++)
		{
			nums[i] = i;
		}
		int numOfNums = size*size - 1;
		for (int y = 0; y < size; y++)
		{
			for (int x = 0; x < size; x++)
			{
				int r = 0;
				if (numOfNums != 0)//ostatni obieg
					r = rand() % numOfNums;
				tab[y][x] = nums[r];
				std::swap(nums[r], nums[numOfNums]);
				numOfNums--;
			}
		}
		delete[] nums;
	}
	bool Board::isSolvable()
	{
		int inversions = 0;
		for (int y = 0; y < size; y++)
		{
			for (int x = 0; x < size; x++)
			{
				if (tab[y][x] != 0)
					inversions += abs(tab[y][x] - getCordToNumber(y, x));
			}
		}
		if (size % 2 == 1)//3,5,7...
		{
			if (inversions % 2 == 0)
				return true;
			else
				return false;
		}
		else
		{
			if (findPosOf(0).y % 2 == 0)//tile at eben
			{
				if (inversions % 2 == 1)
					return true;
				else
					return false;
			}
			else
			{
				if (inversions % 2 == 0)
					return true;
				else
					return false;
			}
		}
	}



	bool Board::isPossible(int y, int x)
	{
		if (x >= 0 && x < size && y >= 0 && y < size)
			return true;
		else
			return false;
	}
	bool Board::mySwap(int y, int x, int ny, int nx)//newy
	{
		if (isPossible(ny, nx) == false)
			return false;
		std::swap(tab[y][x], tab[ny][nx]);
		return true;
	}
	bool Board::operator<(const Board& rhs) const
	{
		if (this->priority - rhs.priority == 0)
			return false;
		return this->priority > rhs.priority;
	}
