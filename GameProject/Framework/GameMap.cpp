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
	int offX = 0;//camera->GetBound().left / tileWidth;
	int offY = 0;// camera->GetBound().top / tileHeight;
	//calculating number of columns and rows that will be drawn
	int columnsDraw = GLOBAL->g_ScreenWidth / tileWidth;//camera->GetCameraWidth() / tileWidth;
	int rowsDraw = GLOBAL->g_ScreenHeight / tileHeight;//camera->GetCameraHeight() / tileHeight;

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
			//tileset->Draw(tileID, D3DXVECTOR3(x*tileWidth, y*tileHeight + GlobalVar::GetGameUIArea(), 0));
			//tileSet->DrawTile(tileID, D3DXVECTOR3((x + offX)*tileWidth, (y + offY)*tileHeight, 0), camera->GetCameraPosition());
			tileSet->DrawTile(tileID, D3DXVECTOR3((x + offX)*tileWidth, (y + offY)*tileHeight, 0), D3DXVECTOR3(GLOBAL->g_ScreenWidth/2,GLOBAL->g_ScreenHeight/2,0));
		}
	}
}
