#include "Tile.h"

Tile::Tile(float x, float y, float width, float height)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}

Tile::~Tile()
{
}

RECT Tile::GetSourceRect()
{
	RECT r;
	r.left = x;
	r.top = y;
	r.right = r.left + width;
	r.bottom = r.top + height;
	return r;
}

float Tile::GetTileWidth()
{
	return width;
}

float Tile::GetTileHeight()
{
	return height;
}
