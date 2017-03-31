#include "stdafx.h"
#include "Pos.h"
const char* pos::toString()
{
	char * out;
	if (this->x == -1)
	{
		out = "left";
	}
	else if (this->x == 1)
	{
		out = "right";
	}
	else if (this->y == -1)
	{
		out = "up";
	}
	else if (this->y == 1)
	{
		out = "down";
	}
	else
	{
		out = "wtf";
	}

	return out;
}	
pos pos::operator -(const pos & other)
{
	pos wynik;
	wynik.y = this->y - other.y;
	wynik.x = this->x - other.x;
	return  wynik;
}
bool pos::operator ==(const pos & other)
{
	if (this->x == other.x  && this->y == other.y)
		return 1;
	return 0;
}
pos pos::operator +(const pos & other)
{
	pos wynik;
	wynik.y = this->y + other.y;
	wynik.x = this->x + other.x;
	return  wynik;
}
pos pos::operator *(const int & val)
{
	pos wynik;
	wynik.y = this->y * val;
	wynik.x = this->x * val;
	return  wynik;
}
 pos pos::keyToDelta(int numPadNumber)
{
	pos out;
	switch (numPadNumber)
	{
	case 8:
		out.y = -1;
		out.x = 0;
		break;
	case 2:
		out.y = +1;
		out.x = 0;
		break;
	case 4:
		out.y = 0;
		out.x = -1;
		break;
	case 6:
		out.y = 0;
		out.x = +1;
		break;
	default:
		out.y = 0;
		out.x = 0;
		break;
	}
	return out;
}
 pos pos::DeltaToDir(pos delta)
{
	pos out;
	if (delta.x < 0)
	{
		out.y = 0;
		out.x = -1;
	}
	else if (delta.x>0)
	{
		out.y = 0;
		out.x = +1;
	}
	else  if (delta.y < 0)
	{
		out.y = -1;
		out.x = 0;
	}
	else if (delta.y > 0)
	{
		out.y = +1;
		out.x = 0;
	}
	else
	{
		out.y = +1337;
		out.x = +1337;
	}

	return out;
}

std::ostream & operator <<(std::ostream & s, const pos & p)
{
	return s << '<' << p.y << ',' << p.x << '>';
}