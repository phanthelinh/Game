#pragma once
#include <unordered_set>
#include "../GameComponents/GameObject.h"

class Cell
{
private:
	int		x, y;
	int		cellSize;
	

	bool IsContain(RECT r);
public:
	std::unordered_set<GameObject*> objects;

	Cell(int x, int y, int cellSize);
	//Add an object to a cell, if it is contained in this cell
	void Add(GameObject* obj);
	//Remove an object from a cell
	void Remove(GameObject* obj);
	//Get bound
	RECT GetCellBound();
	//Release memory
	void Release();
};