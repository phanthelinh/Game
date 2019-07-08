#include "Grid.h"

Grid::Grid(int numCols, int numRows, int cellWidth, int cellHeight)
{

}

Cell * Grid::GetCell(int x, int y)
{
	return cells[x][y];
}
