#include "Tile.h"

Tile::Tile(int x, int y, int width, int height)
{
	this->posX = x;
	this->posY = y;
	this->tileWidth = width;
	this->tileHeight = height;
}

RECT Tile::GetSourceRect()
{
	RECT r;
	r.left = posX;
	r.top = posY;
	r.right = r.left + tileWidth;
	r.bottom = r.top + tileHeight;

	return r;
}
