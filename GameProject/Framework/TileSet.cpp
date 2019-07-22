#include "TileSet.h"

TileSet::TileSet(const char * mapFilePath, int tileWidth, int tileHeight)
{
	tileSet = new Sprite(mapFilePath);
	numTilesWidth = tileSet->_textureWidth / tileWidth;
	numTilesHeight = tileSet->_textureHeight / tileHeight;
	this->tileWidth = tileWidth;
	this->tileHeight = tileHeight;
	//reset tileset to size of each tile
	tileSet->_textureWidth = tileWidth;
	tileSet->_textureHeight = tileHeight;
}

void TileSet::DrawTile(int tileId, D3DXVECTOR3 posToDraw, D3DXVECTOR3 cameraPos)
{
	tile = new Tile((tileId%numTilesWidth)*tileWidth, (tileId / numTilesWidth)*tileWidth, tileWidth, tileHeight);
	if (tile == NULL)
	{
		return;
	}
	tileSet->Draw(posToDraw, cameraPos, tile->GetSourceRect(), D3DXVECTOR3(0, 0, 0));
	delete tile;
}

void TileSet::Release()
{
	if (tileSet != nullptr)
	{
		delete tileSet;
	}
}
