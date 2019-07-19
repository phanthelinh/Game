#include "Cell.h"

bool Cell::IsContain(RECT r)
{
	return !((x + cellSize < r.left) || (x > r.right) || (y > r.bottom) || (y + cellSize < r.top));
}

Cell::Cell(int x, int y, int cellSize)
{
	this->x = x;
	this->y = y;
	this->cellSize = cellSize;
}

void Cell::Add(GameObject * obj)
{
	if (obj != NULL && IsContain(obj->GetBound()))
	{
		objects.insert(obj);
	}
}

void Cell::Remove(GameObject * obj)
{
	if (objects.find(obj) != objects.end())
	{
		objects.erase(obj);
	}
}

RECT Cell::GetCellBound()
{
	RECT r;
	r.left = x;
	r.top = y;
	r.right = r.left + cellSize;
	r.bottom = r.top + cellSize;
	return r;
}

void Cell::Release()
{
	for (auto i = objects.begin(); i != objects.end(); ++i)
	{
		objects.erase(i);
	}
}
