#include "TileSet.h"

TileSet::TileSet(const char * file, float tileWidth, float tileHeight)
{
	InitTileSet(file, tileWidth, tileHeight);
}

TileSet::~TileSet()
{
	Release();
}

void TileSet::Draw(int tileID, D3DXVECTOR3 position, D3DXVECTOR3 camPosition)
{
	Tile* tile = new Tile((tileID%tilesetWidth)*tileWidth, (tileID / tilesetWidth)*tileWidth, tileWidth, tileHeight);
	if (tile == NULL)
	{
		return;
	}
	tileset->Draw(position, camPosition, tile->GetSourceRect(), D3DXVECTOR3(0, 0, 0));
	Memory::SafeDelete(tile);
}

void TileSet::InitTileSet(const char * file, float tileWidth, float tileHeight)
{
	tileset = new Sprite(file);
	this->tileWidth = tileWidth;
	this->tileHeight = tileHeight;
	tilesetWidth = tileset->GetWidth() / tileWidth;
	tilesetHeight = tileset->GetHeight() / tileHeight;
	//reset size of each tile
	tileset->SetWidth(tileWidth);
	tileset->SetHeight(tileHeight);
}

void TileSet::Release()
{
	Memory::SafeDelete(tileset);
}
