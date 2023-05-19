#include "simulationEntitie.h"

size_t Coordinates::HashFunction::operator()(const Coordinates coor) const
{
	return (coor.x + coor.y) * (coor.x + coor.y + 1) / 2 + coor.x;
}

int Coordinates::Distance(Coordinates p)const
{
	return abs(x - p.x) + abs(y - p.y);
}

int Coordinates::Length()const
{
	return abs(x) + abs(y);
}

Coordinates Coordinates::Direction(Coordinates c)
{
	return Coordinates(c.x - x, c.y - y);
}
