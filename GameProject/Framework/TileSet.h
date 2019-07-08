#pragma once
#include "Tile.h"
#include "Sprite.h"
#include <d3dx9.h>

class TileSet 
{
private:
	Sprite* tileSet;
	Tile*	tile;
	int		numTilesWidth, numTilesHeight;
	int		tileWidth, tileHeight;
public:
	TileSet(const char* mapFilePath, int tileWidth, int tileHeight);

	void DrawTile(int tileId, D3DXVECTOR3 posToDraw, D3DXVECTOR3 cameraPos);
	//Release
	void Release();
};
