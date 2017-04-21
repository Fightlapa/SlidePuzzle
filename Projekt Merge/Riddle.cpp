

#pragma once
#include "stdafx.h"
#include <iostream>     // std::cout
#include <algorithm>    // std::random_shuffle
#include <ctime>        // std::time
#include <cstdlib>
#include <time.h>
#include <math.h>
#include <list>
#include <stack>
#include "RedBlackTree.h"
#include "Riddle.h"
#include "Config.h"

int Riddle::countInversions(int** rows)
{
	int k = 0;
	int j = 0;
	int inversions = 0;
	while (j != size*size)
	{
		k = j + 1;
		while (k != size*size)
		{
			int temp = 0;
			temp = rows[(k) / size][(k) % size];
			if (temp != 0)
			{
				if (rows[j / size][j%size] > temp)
					inversions++;
			}
			k++;
		}
		j++;
	}
	return inversions;
}
Riddle::Riddle(int size)
{
	this->size = size;
	losujuklad();
}
void Riddle::losujuklad()
{
	iloscwyw = 0;
	vector<int> myvector;
	rows = new int*[size];
	for (int i = 0; i < size; ++i)
		rows[i] = new int[size];
	bool correct = false;
	for (int i = 0; i < size*size; ++i) myvector.push_back(i);
	do
	{
		random_shuffle(myvector.begin(), myvector.end());
		int j = 0;
		for (auto& e : myvector)
		{
			rows[j / size][j%size] = e;
			j++;
		}
	} while (!checkSolvability(rows, size));
}
bool Riddle::checkSolvability(int** rows, int size)
{
	int j = 0;
	int k = 0;
	int inversions = countInversions(rows);;
	if (size % 2 == 1)
	{
		if (inversions % 2 == 0)
			return true;
		else
			return false;
	}
	else
	{
		int location;
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				if (rows[i][j] == 0)
					location = i;
			}
		}
		if ((size - location) % 2 == 1 && inversions % 2 == 0)
			return true;
		else if ((size - location) % 2 == 0 && inversions % 2 == 1)
			return true;
		else
			return false;
	}
}
void Riddle::display(int** riddle)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (riddle[i][j] == 0)
				cout << " " << "   \t";
			else
				cout << riddle[i][j] << "   \t";
		}
		cout << endl;
		std::cout << std::endl;
	}
	cout << endl;
}
void Riddle::multiDisplay(Board states[4], int priorities[4][6])
{
	cout << "Mo¿liwe ruchy:" << endl;
	for (int i = 0; i < size + 1; i++)
	{
		for (int k = 0; k < 4; k++)
		{
			if (priorities[k][0] == -1)
				break;
			if (i != 0)
			{
				for (int j = 0; j < size; j++)
				{
					if (states[k].tab[i - 1][j] == 0)
						cout << " " << "  \t";
					else
					cout << states[k].tab[i - 1][j] << "   \t";
				}
				cout << "\t";
			}
			else
			{
				cout << "D:" << priorities[k][2] << " I:" << priorities[k][3] << " O:" << priorities[k][4] << "\t\t\t";
				if (size == 4)
					cout << "\t";
			}
		}
		cout << endl;
		std::cout << std::endl;
		if (i == 0)
			cout << endl;
	}
	cout << endl;
}
bool Riddle::checkIfDone(int ** actualState)
{
	int next = 1;
	bool done = true;
	int kejs = 0;
	switch (kejs)
	{
	case 0:
	{
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				if (actualState[i][j] == next)
				{
					next++;
				}
				else if (actualState[i][j] == 0 && i == size - 1 && j == size - 1)
				{
					continue;
				}
				else
					return false;
			}
		}
		break;
	}
	case 1:
	{for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (actualState[i][j] == next)
			{
				next++;
				continue;
			}
			else if (i == (size - 1) && (j == size - 1) && actualState[i][j] == 0)
			{
				continue;
			}
			else
				return false;
		}
	}
	}
	}
	return done;
}
bool Riddle::checkIfIWasHere(int** riddle)
{
	return tree->search(riddle);
}
void Riddle::IWasHere(int** riddle)
{
	tree->insert(riddle);
}
int Riddle::countNotOnPlace(int** rows)
{
	int counter = 0;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (rows[i][j] != i * size + j + 1 && rows[i][j] != 0)
				counter++;
			else if (i != size - 1 && j != size - 1 && rows[i][j] == 0)
				counter++;
		}
	}
	return counter;
}
Board* Riddle::copy(Board* state)
{
	Board* temp = new Board;
	temp->tab = new int*[size];
	for (int i = 0; i < size; ++i)
		temp->tab[i] = new int[size];
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			temp->tab[i][j] = state->tab[i][j];
		}
	}
	temp->priority = state->priority;
	return temp;
}
int** Riddle::copyRiddle(int** riddle)
{
	int** temp = new int*[size];
	for (int i = 0; i < size; ++i)
		temp[i] = new int[size];
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			temp[i][j] = riddle[i][j];
		}
	}
	return temp;
}
void Riddle::solveByDistance()
{
	Search(DISTANCE, ABANDON, SHOWHELP);
}
void Riddle::solveByInversions()
{
	Search(INVERSIONS, ABANDON, SHOWHELP);
}
void Riddle::solveByOnPlace()
{
	Search(ONPLACE, ABANDON, SHOWHELP);
}
void Riddle::solveByBFS() {

	Search(BFS, false, SHOWHELP);
}
void Riddle::solveByDFS() {

	Search(DFS, false, SHOWHELP);
}

void Riddle::getNextState(Board* copy, priority_queue<Board, vector<Board>>*q, queue <Board, list<Board>> *nq, stack<Board, vector<Board>>*s, algorithm alg)
{
	switch (alg)
	{
	case BFS: {
		while (!nq->empty() && checkIfIWasHere(nq->front().tab))
		{
			nq->pop();
		}
		if (!nq->empty()) //jesli jest co sprawdzac, to sprawdzam
		{
			*copy = nq->front();
			nq->pop();
		}
		break;
	}
	case DFS: {
		while (!s->empty() && checkIfIWasHere(s->top().tab))
		{
			s->pop();
		}
		if (!s->empty()) //jesli jest co sprawdzac, to sprawdzam
		{
			*copy = s->top();
			s->pop();
		}
		break;
	}
	default:
	{
		while (!q->empty() && checkIfIWasHere(q->top().tab))
		{
			q->pop();
		}
		if (!q->empty()) //jesli jest co sprawdzac, to sprawdzam
		{
			*copy = q->top();
			q->pop();
		}
		break;
	}
	}
}
void Riddle::addToQueue(Board* temp, algorithm alg, priority_queue<Board, vector<Board>>*q, queue <Board, list<Board>> *nq, stack<Board, vector<Board>>*s)
{
	switch (alg)
	{
	case BFS:
		nq->push(*temp);
		break;
	case DFS:
		s->push(*temp);
		break;
	default:
		q->push(*temp);
		break;
		//dodajemy do kolejki
	}
}
int Riddle::calculateDistance(int **temp)
{
	{
		int score = 0;
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				if (temp[i][j] != 0)
				{
					score += abs(((temp[i][j] - 1) / size - size * i / size));
					score += abs(((temp[i][j] - 1) % size - j));
				}
				else
				{
					score += abs(size - 1 - i);
					score += abs(size - 1 - j);
				}
			}
		}
		return score;
	}
}
void Riddle::cleanPriority(int tab[4][6])
{
	for (int k = 0; k < 4; k++)
		tab[k][0] = -1;
}
int Riddle::getPriorityFromQueue(algorithm alg, priority_queue<Board, vector<Board>>*q, queue <Board, list<Board>> *nq, stack<Board, vector<Board>>*s)
{
	switch (alg)
	{
	case BFS:
		return nq->front().priority;
		break;
	case DFS:
		return s->top().priority;
		break;
	default:
		return q->top().priority;
		break;
	}
}
bool Riddle::checkIfInLastMove(Board states[4], int** riddle, int priorities[4][6])
{
	int k = 0;
	for (k = 0; k < 4;k++)
	{
		if (priorities[k][0] == -1)
			continue;
		bool thatsIt = true;
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				if (states[k].tab[i][j] != riddle[i][j])
					thatsIt = false;
			}
			if (thatsIt == false)
				break;
		}
		if (thatsIt == true)
			return true;
	}
	return false;
}
int Riddle::calcPriority(algorithm alg, int**rows)
{
	switch (alg)
	{
	case BFS: {
		return 0;
	}
	case DFS: {
		return 0;
	}
	case DISTANCE: {
		return calculateDistance(rows);
	}
	case ONPLACE: {
		return countNotOnPlace(rows);
	}
	case INVERSIONS: {
		return countInversions(rows);
	}
	}
}
void Riddle::Search(algorithm alg, bool abandonBranch, bool displayInfo)
{
	cout << "Algorytm " << algorithm_name[alg] << " rozpoczyna swoj¹ pracê." << endl << endl;
	tree = new RedBlackTree(size);
	Board stateTab[4];
	clock_t tStart = clock();
	double timestamp = 0;
	double timeBefore = 0;
	int modI, modJ;
	Board copy;
	Board temp;
	bool done = false;
	bool success = new bool;
	bool found = false; // do stwierdzania, czy 0 znalezione w tablicy

	int priorities[4][6];
	cleanPriority(priorities);
	priority_queue<Board, vector<Board>>q;
	queue <Board, list<Board>> nq;
	stack<Board, vector<Board>>s;
	copy.tab = this->copyRiddle(rows);
	copy.priority = 0;
	temp.tab = this->copyRiddle(rows);
	switch (alg)
	{
	case BFS: {
		temp.priority = 0;
		nq.push(temp);
		//printf("BFS\n");
		break;
	}
	case DFS: {
		temp.priority = 0;
		s.push(temp);
		//printf("DFS\n");
		break;
	}
	case DISTANCE: {
		temp.priority = calculateDistance(temp.tab);
		q.push(temp);
		//printf("DISTANCE\n");
		break;
	}
	case INVERSIONS: {
		temp.priority = countInversions(temp.tab);
		q.push(temp);
		//	printf("INVERSIONS\n");
		break;
	}
	case ONPLACE: {
		temp.priority = countNotOnPlace(temp.tab);
		q.push(temp);
		//printf("ONPLACE\n");
		break;
	}
	}
	bool newBranch = false;
	while (done == false) //az sie nie uda
	{
		iloscwyw++;
		if (iloscwyw % 1000 == 0 && SHOWHELP == 0 && (alg == DFS || alg == BFS || BOARDSIZE > 3))
		{
			cout <<"Iloœæ rozpatrzonych stanów: "<< iloscwyw;

			timestamp = ((double)(clock() - tStart) / CLOCKS_PER_SEC) - timeBefore;
			timeBefore = ((double)(clock() - tStart) / CLOCKS_PER_SEC);
			printf("\t czas: %.2fs\t%.2fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC, timestamp);
		}
		if (abandonBranch == true)
		{
			getNextState(&copy, &q, &nq, &s, alg);
		}
		if (newBranch == true && abandonBranch == false)
		{
			getNextState(&copy, &q, &nq, &s, alg);
			newBranch = false;
		}

		if (abandonBranch == true && !checkIfInLastMove(stateTab, copy.tab, priorities) && displayInfo == true)
			cout << "Zmieniam ga³¹Ÿ" << endl;
		IWasHere(copy.tab);
		if (displayInfo == true)
		{
			getchar();
			cout << "Aktualnie:" << endl;
			display(copy.tab);
		}
		temp.tab = copyRiddle(copy.tab);
		found = false;
		success = true;
		for (int i = 0; i < size; i++) //sprawdzanie gdzie mozna sie ruszyc
		{
			if (found == true)
				break;
			for (int j = 0; j < size; j++)
			{
				if (found == true)
					break;
				if (temp.tab[i][j] == 0)
				{
					cleanPriority(priorities);
					int counter = 0;
					for (int k = 0; k < 4; k++)//sprawdzanie ruchow
					{
						switch (k)
						{
						case 0:
							if (i > 0)
								modI = i - 1;
							else
								continue;
							modJ = j;
							break;
						case 1:
							if (i + 1 < size)
								modI = i + 1;
							else
								continue;
							modJ = j;
							break;
						case 2:
							modI = i;
							if (j > 0)
								modJ = j - 1;
							else
								continue;
							break;
						case 3:
							modI = i;
							if (j + 1 < size)
								modJ = j + 1;
							else
								continue;
							break;
						}

						if (success == false)
						{
							temp.tab = this->copyRiddle(copy.tab);
						}
						success = true; //pomocnicza zmienna do decyzji o alokacji
						swap(temp.tab[i][j], temp.tab[modI][modJ]); // zamiana 2 elementów uk³adanki
						if (checkIfDone(temp.tab))
						{
							done = true;
							/*cout << iloscwyw;
							timestamp = ((double)(clock() - tStart) / CLOCKS_PER_SEC) - timeBefore;
							timeBefore = ((double)(clock() - tStart) / CLOCKS_PER_SEC);
							printf("\tTime taken: %.2fs\t%.2fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC, timestamp);*/
							if (SHOWHELP)
								display(temp.tab);
							cout << "Wygrana!" << endl;
							return;
						}

						if (!checkIfIWasHere(temp.tab)) //sprawdzanie czy stan ju¿ sprawdzany lub czy bêdzie sprawdzany
						{

							//priorities[counter][alg] = calcPriority(alg, temp.tab);

							priorities[counter][0] = 0;
							priorities[counter][1] = 0;
							if (alg == algorithm::DISTANCE || displayInfo == true)
								priorities[counter][2] = calculateDistance(temp.tab);
							if (alg == algorithm::INVERSIONS || displayInfo == true)
								priorities[counter][3] = countInversions(temp.tab);
							if (alg == algorithm::ONPLACE || displayInfo == true)
								priorities[counter][4] = countNotOnPlace(temp.tab);

							stateTab[counter].tab = temp.tab;
							stateTab[counter].priority = priorities[counter][alg];
							counter++;
							success = false;
						}
						if (success == true)
							swap(temp.tab[i][j], temp.tab[modI][modJ]); // jesli nie dodano elementu, cofamy zamiane, zeby zachowac oryginalny uklad
					}
					if (displayInfo == true)
						multiDisplay(stateTab, priorities);
					if (abandonBranch == false)
					{
						int k = 0;
						int max = 9999;
						int indexOfStateToConsider = -1;
						for (k = 0; k < 4;k++)
						{
							if (priorities[k][0] == -1)
								continue;
							if (priorities[k][alg] < max)
							{
								indexOfStateToConsider = k;
								max = priorities[k][alg];
							}
						}
						if (indexOfStateToConsider != -1)
						{
							copy = stateTab[indexOfStateToConsider];
							priorities[indexOfStateToConsider][0] = -1;
						}
						if (max == 9999)
						{
							newBranch = true;
							if (displayInfo == true)
								cout << "Zmieniam ga³¹Ÿ" << endl;
						}
						for (k = 0; k < 4; k++)
						{
							if (priorities[k][0] != -1)
								addToQueue(&stateTab[k], alg, &q, &nq, &s);
						}
					}
					else
					{
						int k = 0;
						for (k = 0; k < 4; k++)
						{
							if (priorities[k][0] == -1)
								continue;
							addToQueue(&stateTab[k], alg, &q, &nq, &s);
						}
					}
					found = true;// jak juz znalezlismy 0 w tablicy, to po co szukac dalej? xD
				}
			}
		}
	}

}
