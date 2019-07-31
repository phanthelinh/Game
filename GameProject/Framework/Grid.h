#pragma once
#include "Cell.h"
#include "Camera.h"
#include "Collision.h"
#include "../GameComponents/GameObject.h"
#include "Util.h"
#include "../GameComponents/Ground.h"

#define GRID	Grid::GetInstance()

class Grid
{
private:
	Cell*** cells;
	std::unordered_set<GameObject*> objects;
	int numCols, numRows;
	static Grid*	instance;

public:
	std::vector<Cell*> visibleCells;
	std::vector<GameObject*> listGround;

	static Grid* GetInstance();
	Grid();
	Grid(int numCols, int numRows);
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
	void UpdateGrid(float deltaTime);
	//Get objects that have ability to collide with a target Game object
	std::unordered_set<GameObject*> GetColliableObjectsWith(GameObject* target, float deltaTime);
	//Get object Ground in visual viewport
	std::vector<GameObject*> GetVisibleGround();
	std::unordered_set<GameObject*> GetVisibleObjects();
	void ObjectMoving(float deltaTime);
};
