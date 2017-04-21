#pragma once
#include "Board.h"
#include <queue>
#include <vector> 
#include "RedBlackTree.h"// std::vector
#include <list>
#include <stack>
#include <queue>
using namespace std;
class Riddle
{
public:
	int iloscwyw = 0;
	typedef enum {
		BFS = 0,
		DFS = 1,
		DISTANCE = 2,
		INVERSIONS = 3,
		ONPLACE = 4
	}algorithm;
	char * algorithm_name[20] = {
		"BFS",
		"DFS",
		"DISTANCE",
		"INVERSIONS",
		"ONPLACE"
	};
	int size;
	int** rows;

	struct None
	{
		bool operator()(const Board& left, const Board& right) const
		{
			return -1;
		}
	};
	RedBlackTree* tree;
	void solveByDistance();
	void solveByInversions();
	void solveByOnPlace();
	void solveByBFS();
	void solveByDFS();
	int countInversions(int** rows);
	Riddle(int size);
	bool checkSolvability(int** rows, int size);
	void display(int** riddle);
	void multiDisplay(Board states[4], int priorities[4][6]);
	bool checkIfDone(int ** actualState);
	bool checkIfIWasHere(int** riddle);
	void IWasHere(int** riddle);
	int countNotOnPlace(int** rows);
	Board* copy(Board* state);
	int** copyRiddle(int** riddle);
	void losujuklad();
	void getNextState(Board* copy, priority_queue<Board, vector<Board>>*q, queue <Board, list<Board>> *nq, stack<Board, vector<Board>>*s, algorithm alg);
	void addToQueue(Board* temp, algorithm alg, priority_queue<Board, vector<Board>>*q, queue <Board, list<Board>> *nq, stack<Board, vector<Board>>*s);
	int calculateDistance(int **temp);
	void cleanPriority(int tab[4][6]);
	int calcPriority(algorithm alg, int** rows);
	int getPriorityFromQueue(algorithm alg, priority_queue<Board, vector<Board>>*q, queue <Board, list<Board>> *nq, stack<Board, vector<Board>>*s);
	bool checkIfInLastMove(Board states[4], int** riddle, int priorities[4][6]);
	void Search(algorithm alg, bool abandonBranch, bool displayInfo);
};