#include "GameMap.h"

GameMap::GameMap(int tileWidth, int tileHeight, int numTilesWidth, int numTileHeight, const char * tileSetPath, const char * dataFilePath)
{
	data = Util::GetMapDataFromFile(dataFilePath);
	if (data.empty())
	{
		MessageBox(NULL, "Error on retriving map data", "Error", MB_OK);
		return;
	}
	this->tileWidth = tileWidth;
	this->tileHeight = tileHeight;
	this->numTilesHeight = numTileHeight;
	this->numTilesWidth = numTilesWidth;

	tileSet = new TileSet(tileSetPath, tileWidth, tileHeight);
	//init camera

}

void GameMap::RenderMap()
{
	//calculating offset
	int offX = CAMERA->GetBound().left / tileWidth;
	int offY = CAMERA->GetBound().top / tileHeight;
	//calculating number of columns and rows that will be drawn
	int columnsDraw = CAMERA->camWidth / tileWidth;
	int rowsDraw = CAMERA->camHeight / tileHeight;

	for (int y = 0; y < rowsDraw; y++)
	{
		for (int x = 0; x <= columnsDraw; x++)
		{
			int pos = (offY + y)*numTilesWidth + (offX + x);
			if (pos < 0 || pos >= data.size())
			{
				return;
			}
			int tileID = data.at(pos);
			if (tileID < 0)
			{
				return;
			}
			
			tileSet->DrawTile(tileID, D3DXVECTOR3((x + offX)*tileWidth, (y + offY)*tileHeight, 0), CAMERA->camPosition);
		}
	}
}
