#pragma once
#include <Windows.h>

class Tile
{
public:
	int posX, posY;
	int tileWidth, tileHeight;
	/**
	Initilaize the Tile
	x:		the left of this tile, compare to world map
	y:		the top of this tile, compare to wolrd map
	width:	the width of this tile
	hieght:the height of this tile
	**/
	Tile(int x, int y, int width, int height);
	//Get the rectangle of a tile
	RECT GetSourceRect();

};