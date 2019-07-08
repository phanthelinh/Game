#pragma once
#include "../GlobalVar.h"
#include "Camera.h"
#include "Sprite.h"
#include <string>
#include "TileSet.h"


class GameMap
{
public:
	enum RenderMapDirection
	{
		LeftToRight,
		RightToLeft,
		BottomToTop,
		TopToBottom
	};
	//Data of section in Game Map
	typedef struct tagMapSectionData
	{
		int startX;
		int startY;
		int numTilesWidth;
		int numTilesHeight;
		RenderMapDirection direction;
		D3DXVECTOR3 newPlayerPos;
	}MapSectionData;
	/*
	Initilaized the map
	@tWidth:	tile width
	@tHeight:	tile height
	@mWidth:	the number of tiles at the first row
	@mHeight:	the number of tiles at the first column
	@fPath:		the path to the image/tileset
	@data[]:	the data of the map
	*/
	GameMap(int tWidth, int tHeight, int mWidth, int mHeight, std::string fPath,int data[]);

	GameMap(std::map<int, MapSectionData> sectionData, int tWidth, int tHeight,int mWidth, int mHeight, std::string fPath, int data[], D3DXVECTOR3 &newPlayerPos);

	~GameMap();
	//Change map to next section
	void NextSection(D3DXVECTOR3 &newPlayerPos);
	//Check for reach to the end of section
	bool IsEndSection();
	//Get camera position depending on section
	D3DXVECTOR3 GetCameraPosition(MapSectionData sec);
	//Set the user's view
	void SetCamera(Camera *cam);
	//Get current camera
	Camera* GetCamera();
	//Begin render the map
	void RenderMap();
	//Update the map, camera
	void UpdateMap(D3DXVECTOR3 playerPosition);
	//Check camera and world map
	void CheckCameraAndWorldMap(D3DXVECTOR3 playerPosition);
	//Free memory
	void Release();

	int *mapData;								//map data to draw, contains position of block in picture
private:
	//Set data to draw
	void SetMapData(int data[]);
	
	int tileWidth, tileHeight;					//Size of tile
	int mapWidth, mapHeight;					//number of tiles in width and height
	int gameWorldWidth, gameWorldHeight;		//real size of map in pixels
	
	Camera * camera;							//view of user
	TileSet* tileset;							//Tileset contains a lot of tiles to be drawn respectively
	int currentSection;							//Current section in this map
	std::map<int,MapSectionData> mapSectionData;//Section data in this map
};

