#pragma once
#include "../GlobalVar.h"

class Tile
{
public: 
	/*
	Initilaize the Tile
	@x:		the left of this tile, compare to world map
	@y:		the top of this tile, compare to wolrd map
	@width:	the width of this tile
	@hieght:the height of this tile
	*/
	Tile(float x, float y, float width, float height);
	~Tile();
	//Return the bounding box of this tile in world map
	RECT GetSourceRect();
	//Return width of this tile
	float GetTileWidth();
	//Return height of this tile
	float GetTileHeight();
private:
	float x, y;				//left,top position
	float width, height;	//size of tile
};
