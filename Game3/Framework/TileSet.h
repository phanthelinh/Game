#pragma once
#include "Tile.h"
#include "Sprite.h"
#include <map>
class TileSet
{
public:
	/*
	Initialize the TileSet
	@file:		the path of tile set
	@tileWidth:	width of each tile in tile set file
	@tileHeight:height of each tile in tile set file
	*/
	TileSet(const char* file, float tileWidth, float tileHeight);
	~TileSet();

	void Draw(int tileID, D3DXVECTOR3 position, D3DXVECTOR3 camPosition);
	//Free memory
	void Release();
private:
	//Initialize tile set into std::map
	void InitTileSet(const char* file, float tileWidth, float tileHeight);
	
	int tilesetWidth, tilesetHeight;
	int tileWidth, tileHeight;
	Sprite* tileset;
};
