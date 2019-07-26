#pragma once
#include <unordered_set>
#include "../GameComponents/GameObject.h"

#define CELL_WIDTH		(GLOBAL->g_ScreenWidth/2)
#define CELL_HEIGHT		(GLOBAL->g_ScreenHeight/2)
class Cell
{
private:
	int		x, y;
	
	bool IsContain(RECT r);
public:
	std::unordered_set<GameObject*> objects;

	Cell(int x, int y);
	//Add an object to a cell, if it is contained in this cell
	void Add(GameObject* obj);
	//Remove an object from a cell
	void Remove(GameObject* obj);
	//Get bound
	RECT GetCellBound();
	//Release memory
	void Release();
};