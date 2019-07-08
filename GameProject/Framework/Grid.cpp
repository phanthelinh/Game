#include "Grid.h"

Grid::Grid(int numCols, int numRows, int cellSize)
{
	this->numCols = numCols;
	this->numRows = numRows;
	this->cellSize = cellSize;

	for (int i = 0; i < numCols; i++)
	{
		for (int j = 0; j < numRows; j++)
		{
			cells[i][j] = new Cell(i*cellSize, j*cellSize, cellSize);
		}
	}
}

Cell * Grid::GetCell(int x, int y)
{
	return cells[x][y];
}

void Grid::InsertToGrid(std::unordered_set<GameObject*> objects)
{
	if (objects.empty())
		return;
	this->objects = objects;

	for (auto it = objects.begin(); it != objects.end(); ++it)
	{
		RECT objBound = (*it)->GetBound();
		//calculate which cell is valid
		int startX = floor(objBound.left / cellSize);
		int endX = floor(objBound.right / cellSize);
		int startY = floor(objBound.top / cellSize);
		int endY = floor(objBound.bottom / cellSize);

		if (endX >= numCols || endY >= numRows)
			continue;
		for (int i = startX; i <= endX; i++)
		{
			for (int j = startY; j <= endY; j++)
			{
				cells[i][j]->Add(*it);
			}
		}
	}
}

void Grid::AddObject(GameObject * object)
{
	if (object == NULL)
		return;
	auto objBound = object->GetBound();
	//calculate which cell is valid
	int startX = floor(objBound.left / cellSize);
	int endX = floor(objBound.right / cellSize);
	int startY = floor(objBound.top / cellSize);
	int endY = floor(objBound.bottom / cellSize);

	for (int i = startX; i <= endX; i++)
	{
		for (int j = startY; j <= endY; j++)
		{
			cells[i][j]->Add(object);
		}
	}
}

void Grid::RemoveObject(GameObject * object)
{
	if (object == NULL)
		return;
	auto objBound = object->GetBound();
	//calculate which cell is valid
	int startX = floor(objBound.left / cellSize);
	int endX = floor(objBound.right / cellSize);
	int startY = floor(objBound.top / cellSize);
	int endY = floor(objBound.bottom / cellSize);

	for (int i = startX; i <= endX; i++)
	{
		for (int j = startY; j <= endY; j++)
		{
			cells[i][j]->Remove(object);
		}
	}
}

void Grid::UpdateVisibleCells()
{
	visibleCells.clear();
	int startX = floor(CAMERA->GetBound().left / cellSize);
	int endX = ceil(CAMERA->GetBound().right / cellSize);

	for (int i = startX; i <= endX; i++)
	{
		for (int j = 0; j < numRows; j++)
		{
			visibleCells.push_back(cells[i][j]);
		}
	}
}

void Grid::UpdateGrid()
{
	UpdateVisibleCells();
}

std::unordered_set<GameObject*> Grid::GetColliableObjectsWith(GameObject * target)
{
	std::unordered_set<GameObject*> res; //result objects

	auto targetBound = target->GetBound();
	
	int startX = floor(targetBound.left / cellSize);
	int endX = floor(targetBound.right / cellSize);
	int startY = floor(targetBound.top / cellSize);
	int endY = floor(targetBound.bottom / cellSize);
	//iterate for each cell in range
	for (int j = startY; j < endY; j++)
	{
		if (j < 0 || j >= numRows)
			continue;
		for (int i = startX; i < endX; i++)
		{
			if (i < 0 || i >= numCols)
				continue;
			//iterate for each object in a cell
			for (auto insideObject : cells[j][i]->objects)
			{
				//***Check if each object in each cell is colliable with target object
				if (insideObject->IsCollide(target->GetBound()))
				{
					//add it to result list
					res.insert(insideObject);
				}
			}
		}
	}
	return res;
}
