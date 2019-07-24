#pragma once
#include "Util.h"
#include "TileSet.h"
#include "Camera.h"
#include <Windows.h>
class GameMap
{
private:
	std::vector<int> data;
	TileSet* tileSet;
public:
	int		tileWidth, tileHeight;
	int		numTilesWidth, numTilesHeight;
	


	GameMap(int tileWidth, int tileHeight, int numTilesWidth, int numTileHeight, const char* tileSetPath, const char* dataFilePath);
	//Start redering map
	void RenderMap();
	//Update map along with player
	void UpdateMap(D3DXVECTOR3 playerPos);
	void Release();
};
