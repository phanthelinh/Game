#include "Grid.h"

Grid* Grid::instance = NULL;

Grid * Grid::GetInstance()
{
	if (instance == NULL)
		instance = new Grid();
	return instance;
}

Grid::Grid()
{
	numCols = GLOBAL->g_WorldMapWidth / CELL_WIDTH;
	numRows = GLOBAL->g_WorldMapHeight / CELL_HEIGHT;
	std::vector<RECT> grounds;

	cells = new Cell**[numRows];
	for (int i = 0; i < numRows; i++)
	{
		cells[i] = new Cell*[numCols];
		for (int j = 0; j < numCols; j++)
		{
			cells[i][j] = new Cell(j*CELL_WIDTH, i*CELL_HEIGHT);
		}
	}
	//add ground from file to cell
	grounds = Util::GetAllObjectFromFile(GroundTag, 1);

	for (auto it = grounds.begin(); it != grounds.end(); ++it)
	{
		RECT* g = new RECT();
		g->top = it->top;
		g->left = it->left;
		g->bottom = it->bottom;
		g->top = it->top;
		//calculate which cell is valid
		int startX = floor((*it).left / CELL_WIDTH);
		int endX = floor((*it).right / CELL_WIDTH);
		int startY = floor((*it).top / CELL_HEIGHT);
		int endY = floor((*it).bottom / CELL_HEIGHT);

		if (endX >= numCols || endY >= numRows)
			continue;
		for (int i = startY; i <= endY; i++)
		{
			if (cells[i] == NULL)
				continue;
			for (int j = startX; j <= endX; j++)
			{
				cells[i][j]->grounds.push_back(g);
			}
		}
	}
}

Grid::Grid(int numCols, int numRows)
{
	this->numCols = numCols;
	this->numRows = numRows;

	cells = new Cell**[numRows];
	for (int i = 0; i < numRows; i++)
	{
		cells[i] = new Cell*[numCols];
		for (int j = 0; j < numCols; j++)
		{
			cells[i][j] = new Cell(i*CELL_WIDTH, j*CELL_HEIGHT);
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
		int startX = floor(objBound.left / CELL_WIDTH);
		int endX = floor(objBound.right / CELL_WIDTH);
		int startY = floor(objBound.top / CELL_HEIGHT);
		int endY = floor(objBound.bottom / CELL_HEIGHT);

		if (endX >= numCols || endY >= numRows)
			continue;
		for (int i = startY; i <= endY; i++)
		{
			if (cells[i] == NULL)
				continue;
			for (int j = startX; j <= endX; j++)
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
	int startX = floor(objBound.left / CELL_WIDTH);
	int endX = floor(objBound.right / CELL_WIDTH);
	int startY = floor(objBound.top / CELL_HEIGHT);
	int endY = floor(objBound.bottom / CELL_HEIGHT);

	for (int i = startY; i <= endY; i++)
	{
		if (i < 0 || i >= numRows || cells[i] == nullptr)
			continue;
		for (int j = startX; j <= endX; j++)
		{
			if (j < 0 || j >= numCols || cells[i][j] == nullptr)
				continue;
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
	int startX = floor(objBound.left / CELL_WIDTH);
	int endX = floor(objBound.right / CELL_WIDTH);
	int startY = floor(objBound.top / CELL_HEIGHT);
	int endY = floor(objBound.bottom / CELL_HEIGHT);

	for (int i = startY; i <= endY; i++)
	{
		if (i < 0 || i >= numRows || cells[i] == nullptr)
			continue;
		for (int j = startX; j <= endX; j++)
		{
			if (j < 0 || j >= numCols || cells[i][j] == nullptr)
				continue;
			cells[i][j]->Remove(object);
		}
	}
}

void Grid::UpdateVisibleCells()
{
	visibleCells.clear();
	int startX = floor(CAMERA->GetBound().left / CELL_WIDTH);
	int endX = floor(CAMERA->GetBound().right / CELL_WIDTH);
	int startY = floor(CAMERA->GetBound().top / CELL_HEIGHT);
	int endY = floor(CAMERA->GetBound().bottom / CELL_HEIGHT);
	for (int i = startY; i <= endY; i++)
	{
		if (i < 0 || i >= numRows || cells[i] == nullptr)
			continue;
		for (int j = startX; j <= endX; j++)
		{
			if (j < 0 || j >= numCols || cells[i][j] == nullptr)
				continue;
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
	
	int startX = floor(targetBound.left / CELL_WIDTH);
	int endX = ceil(targetBound.right / CELL_WIDTH);
	int startY = floor(targetBound.top / CELL_HEIGHT);
	int endY = ceil(targetBound.bottom / CELL_HEIGHT);
	//iterate for each cell in range
	
	for (int i = startY; i <= endY; i++)
	{
		if (i < 0 || i >= numRows || cells[i] == NULL)
			continue;
		for (int j = startX; j <= endX; j++)
		{
			if (j < 0 || j >= numCols || cells[i][j] == NULL)
				continue;
			//iterate for each object in a cell
			for (auto insideObject : cells[i][j]->objects)
			{
				//***Check if each object in each cell is colliable with target object
				if (COLLISION->SweptAABB(target->GetBoundingBox(),insideObject->GetBoundingBox()).isCollide)
				{
					//add it to result list
					res.insert(insideObject);
				}
			}
		}
	}
	return res;
}

std::unordered_set<RECT*> Grid::GetVisibleGrounds()
{
	std::unordered_set<RECT*> lstGrounds;

	for (auto cell : visibleCells)
	{
		for (auto g : cell->grounds)
		{
			if (COLLISION->IsCollide(BoundingBox(*g), BoundingBox(CAMERA->GetBound())))
			{
				lstGrounds.insert(g);
			}
		}
	}
	return lstGrounds;
}

std::unordered_set<RECT*> Grid::GetColliableGrounds(GameObject* target)
{
	std::unordered_set<RECT*> grounds;

	auto targetBound = target->GetBound();
	int LeftCell = targetBound.left / CELL_WIDTH;
	int RightCell = targetBound.right / CELL_WIDTH;
	int TopCell = targetBound.top / CELL_HEIGHT;
	int BottomCell = targetBound.bottom / CELL_HEIGHT;

	for (int y = BottomCell; y <= TopCell; ++y)
	{
		if (y < 0 || y >= numRows)
			continue;
		for (int x = LeftCell; x <= RightCell; ++x)
		{
			if (x < 0 || x >= numCols)
				continue;
			//insert all ground object from cells[y][x] into list grounds
			for (auto g : cells[y][x]->grounds)
			{
				grounds.insert(g);
			}
		}
	}
	return grounds;
}

