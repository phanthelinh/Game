#include "Cell.h"

bool Cell::IsContain(RECT r)
{

	return !((x + CELL_WIDTH < r.left) || (x > r.right) || (y > r.bottom) || (y + CELL_HEIGHT < r.top));
}

Cell::Cell(int x, int y)
{
	this->x = x;
	this->y = y;
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
	r.right = r.left + CELL_WIDTH;
	r.bottom = r.top + CELL_HEIGHT;
	return r;
}

void Cell::Release()
{
	objects.erase(objects.begin(), objects.end());
}
