#pragma once
#include "Cell.h"
#include <vector>
class Grid
{
private:
	std::vector<std::vector<Cell*>> cells;
public:
	Grid(int numCols, int numRows, int cellWidth, int cellHeight);
	//Get the cell at grid[x][y]
	Cell* GetCell(int x, int y);

};
