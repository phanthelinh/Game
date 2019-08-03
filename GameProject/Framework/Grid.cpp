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
	objects.clear();
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
	for (auto o : objects)
	{
		AddObject(o);
	}
}

void Grid::AddObject(GameObject * object)
{
	if (object == NULL)
		return;
	this->objects.insert(object);
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
	if (this->objects.find(object) != this->objects.end())
	{
		this->objects.erase(object);
	}
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

void Grid::UpdateGrid(float deltaTime)
{
	UpdateVisibleCells();
	ObjectMoving(deltaTime);
}

std::unordered_set<GameObject*> Grid::GetColliableObjectsWith(GameObject * target, float deltaTime)
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
				if (COLLISION->SweptAABB(target->GetBoundingBox(),insideObject->GetBoundingBox(), deltaTime).isCollide)
				{
					//add it to result list
					res.insert(insideObject);
				}
			}
		}
	}
	return res;
}

std::vector<GameObject*> Grid::GetVisibleGround()
{
	std::vector<GameObject*> rs;
	for (auto c : visibleCells)
	{
		for (auto g : c->objects)
		{
			if (g->tag == Tag::GroundTag && g->IsCollide(CAMERA->GetBound()))
			{
				rs.push_back(g);
			}
		}
	}
	
	return rs;
}

std::unordered_set<GameObject*> Grid::GetVisibleObjects()
{
	std::unordered_set<GameObject*> rs;
	for (auto cell : visibleCells)
	{
		for (auto obj : cell->objects)
		{
			if (obj->IsCollide(CAMERA->GetBound()))
			{
				rs.insert(obj);
			}
		}
	}
	return rs;
}

void Grid::ObjectMoving(float deltaTime)
{
	auto lst = GetVisibleObjects();
	for (auto obj : lst)
	{
		RemoveObject(obj);
		if(obj->tag != Tag::ShieldTag)
			obj->Update(deltaTime);
		AddObject(obj);
	}
}

std::vector<GameObject*> Grid::GetVisibleWater()
{
	std::vector<GameObject*> rs;
	for (auto c : visibleCells)
	{
		for (auto g : c->objects)
		{
			if (g->tag == Tag::WaterTag && g->IsCollide(CAMERA->GetBound()))
			{
				rs.push_back(g);
			}
		}
	}

	return rs;
}

void Grid::Release()
{
	objects.clear();
	visibleCells.clear();
	if (cells != NULL)
	{
		for (int j = 0; j < numRows; j++)
		{
			for (int i = 0; i < numCols; i++)
			{
				cells[j][i]->Release();
				delete cells[j][i];
			}
			//break;
		}
		delete cells;
	}
}

void Grid::ResetGrid()
{
	Release();
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
}
