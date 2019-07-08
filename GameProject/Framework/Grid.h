#pragma once
#include "Cell.h"
#include "Camera.h"

class Grid
{
private:
	std::vector<std::vector<Cell*>> cells;
	std::unordered_set<GameObject*> objects;
	int numCols, numRows;
	int	cellSize;
public:
	std::vector<Cell*> visibleCells;

	Grid(int numCols, int numRows, int cellSize);
	//Get the cell at grid[x][y]
	Cell* GetCell(int x, int y);
	//Insert all objects to grid
	void InsertToGrid(std::unordered_set<GameObject*> objects);
	//Add an object to Grid
	void AddObject(GameObject* object);
	//Remove an object
	void RemoveObject(GameObject* object);
	//Only update cells contained in camera
	void UpdateVisibleCells();
	//Update entire grid
	void UpdateGrid();
	//Get objects that have ability to collide with a target Game object
	std::unordered_set<GameObject*> GetColliableObjectsWith(GameObject* target);
};
