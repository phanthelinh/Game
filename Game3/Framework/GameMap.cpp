#include "GameMap.h"

GameMap::GameMap(int tWidth, int tHeight, int mWidth, int mHeight, std::string fPath, int data[])
{
	tileWidth = tWidth;
	tileHeight = tHeight;
	mapWidth = mWidth;
	mapHeight = mHeight;
	currentSection = 1;

	SetMapData(data);
	//calculate world map size
	gameWorldWidth = tileWidth * mapWidth;
	GlobalVar::SetWorldMapWidth(gameWorldWidth);
	gameWorldHeight = tileHeight * mapHeight;
	GlobalVar::SetWorldMapHeight(gameWorldHeight);
	
	camera = new Camera();
	tileset = new TileSet(fPath.c_str(), tileWidth, tileHeight);
}

GameMap::GameMap(std::map<int, MapSectionData> sectionData, int tWidth, int tHeight, int mWidth, int mHeight, std::string fPath, int data[], D3DXVECTOR3 &newPlayerPos)
{
	mapSectionData = sectionData;
	currentSection = 1;
	MapSectionData currentData = mapSectionData[currentSection];
	//free memory and re-init
	Release();

	tileWidth = tWidth;
	tileHeight = tHeight;
	mapWidth = mWidth;
	mapHeight = mHeight;
	
	SetMapData(data);
	//must reset after next section, this is section size
	gameWorldWidth = tileWidth * currentData.numTilesWidth;
	GlobalVar::SetWorldMapWidth(gameWorldWidth); 
	gameWorldHeight = tileHeight * currentData.numTilesHeight;
	GlobalVar::SetWorldMapHeight(gameWorldHeight);

	camera = new Camera();
	tileset = new TileSet(fPath.c_str(), tileWidth, tileHeight);
	//Update camera position, suit to section
	camera->SetCameraPosition(GetCameraPosition(currentData));

	newPlayerPos = mapSectionData[currentSection].newPlayerPos;
}

GameMap::~GameMap()
{
	Release();
}

void GameMap::NextSection(D3DXVECTOR3 &newPlayerPos)
{
	if (mapSectionData.size() > 0 && currentSection < mapSectionData.size())
	{
		currentSection++;
		//Reset Camera Position
		MapSectionData currentData = mapSectionData[currentSection];
		camera->SetCameraPosition(GetCameraPosition(currentData));
		//reset section size
		gameWorldWidth = tileWidth * currentData.numTilesWidth;
		GlobalVar::SetWorldMapWidth(gameWorldWidth);
		gameWorldHeight = tileHeight * currentData.numTilesHeight;
		GlobalVar::SetWorldMapHeight(gameWorldHeight);
		newPlayerPos = mapSectionData[currentSection].newPlayerPos;
	}
}

bool GameMap::IsEndSection()
{
	if (currentSection >= mapSectionData.size())
		return true;
	return false;
}

D3DXVECTOR3 GameMap::GetCameraPosition(MapSectionData sec)
{
	D3DXVECTOR3 vect;
	switch (sec.direction)
	{
	case RenderMapDirection::LeftToRight:
		vect.x = sec.startX + GlobalVar::GetScreenWidth() / 2;
		vect.y = sec.startY + (GlobalVar::GetScreenHeight() /*- GlobalVar::GetGameUIArea()*/) / 2;
		break;
	case RenderMapDirection::RightToLeft:
		vect.x = sec.startX - GlobalVar::GetScreenWidth() / 2;
		vect.y = sec.startY - (GlobalVar::GetScreenHeight()/* - GlobalVar::GetGameUIArea()*/) / 2;
		break;
	}
	vect.z = 0;
	return vect;
}

void GameMap::SetCamera(Camera * cam)
{
	camera = cam;
}

Camera * GameMap::GetCamera()
{
	return this->camera;
}

void GameMap::RenderMap()
{
	//calculating offset

	int offX = camera->GetBound().left / tileWidth;
	int offY = camera->GetBound().top / tileHeight;
	//calculating number of columns and rows that will be drawn
	int columnsDraw = camera->GetCameraWidth() / tileWidth;
	int rowsDraw = camera->GetCameraHeight() / tileHeight;

	for (int y = 0; y < rowsDraw; y++)
	{
		for (int x = 0; x <= columnsDraw; x++)
		{
			int pos = (offY + y)*mapWidth + (offX + x);
			if (pos < 0)
			{
				return;
			}
			int tileID = mapData[pos];
			if (tileID < 0)
			{
				return;
			}
			//tileset->Draw(tileID, D3DXVECTOR3(x*tileWidth, y*tileHeight + GlobalVar::GetGameUIArea(), 0));
			tileset->Draw(tileID, D3DXVECTOR3((x + offX)*tileWidth, (y + offY)*tileHeight, 0), camera->GetCameraPosition());
		}
	}
	
}

void GameMap::UpdateMap(D3DXVECTOR3 playerPosition)
{
	CheckCameraAndWorldMap(playerPosition);
}

void GameMap::CheckCameraAndWorldMap(D3DXVECTOR3 playerPosition)
{
	MapSectionData secData = mapSectionData[currentSection];
	int mapTopBorder = secData.startY;
	int mapBottomBorder = secData.startY;
	int offsetX = secData.startX;
	if (mapSectionData[currentSection].direction == RenderMapDirection::LeftToRight)
	{
		mapBottomBorder = mapTopBorder + camera->GetCameraHeight();
	}
	if (mapSectionData[currentSection].direction == RenderMapDirection::RightToLeft)
	{
		mapTopBorder = mapBottomBorder - camera->GetCameraHeight();
	}
	
	camera->SetCameraPosition(playerPosition);
	if (secData.direction == RenderMapDirection::LeftToRight)
	{
		if (camera->GetBound().left < offsetX)
		{
			camera->SetCameraPosition(camera->GetCameraWidth() / 2 + offsetX, camera->GetCameraPosition().y);
		}
		if (camera->GetBound().right > GlobalVar::GetWorldMapWidth() + offsetX)
		{
			camera->SetCameraPosition(GlobalVar::GetWorldMapWidth() + offsetX - camera->GetCameraWidth() / 2,
				camera->GetCameraPosition().y);
		}
	}
	if (secData.direction == RenderMapDirection::RightToLeft)
	{
		if (camera->GetBound().left < offsetX - GlobalVar::GetWorldMapWidth())
		{
			camera->SetCameraPosition(camera->GetCameraWidth() / 2 + offsetX - GlobalVar::GetWorldMapWidth(), 
				camera->GetCameraPosition().y);
		}
		if (camera->GetBound().right > offsetX)
		{
			camera->SetCameraPosition(offsetX - camera->GetCameraWidth() / 2,
				camera->GetCameraPosition().y);
		}
	}
	//top and bottom border
	if (camera->GetBound().top < mapTopBorder)
	{
		camera->SetCameraPosition(camera->GetCameraPosition().x, mapTopBorder + camera->GetCameraHeight() / 2);
	}
	if (camera->GetBound().bottom > mapBottomBorder)
	{
		camera->SetCameraPosition(camera->GetCameraPosition().x, mapBottomBorder - camera->GetCameraHeight() / 2);
	}
	
}

void GameMap::Release()
{
	Memory::SafeRelease(tileset);
	Memory::SafeDeleteArr(mapData);
	Memory::SafeDelete(camera);
}

void GameMap::SetMapData(int data[])
{
	int size = mapWidth * mapHeight;
	if (size == 0)
		return;
	mapData = new int[size];
	for (int i = 0; i < size; i++)
	{
		mapData[i] = data[i];
	}
}