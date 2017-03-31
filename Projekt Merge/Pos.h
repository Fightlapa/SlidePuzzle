#pragma once
#include <iostream>
struct pos
{
	int y, x;
	pos operator -(const pos & other);
	bool operator ==(const pos & other);
	pos operator +(const pos & other);
	pos operator *(const int & val);
	static pos keyToDelta(int numPadNumber);
	static pos DeltaToDir(pos delta);
	const char* toString();
};
std::ostream & operator <<(std::ostream & s, const pos & p);