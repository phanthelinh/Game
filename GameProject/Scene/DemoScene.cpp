#include "DemoScene.h"
#include "SceneManager.h"
#include "TitleScene.h"

DemoScene::DemoScene()
{
	map = new GameMap(16, 16, 128, 30, "Resources/map/Charleston_cut.png", "Resources/map/Charleston_1_1.csv");
	//map = new GameMap(16, 16, 80, 60, "Resources/map/Pittsburgh_1_1.bmp", "Resources/map/Pittsburgh_1_1.csv");

	//Get items container
	lstItemContainerRect = Util::GetObjectDataFromFile("Resources/items/itemcontainer.txt");
	if (lstItemContainerRect.size() > 0)
	{
		for (auto r : lstItemContainerRect)
		{
			itemsContainer.insert(new ItemsContainer(r));
		}
	}
	//init for Player
	PLAYER; //get instance
	PLAYER->posX = 16;
	PLAYER->posY = 390;
	PLAYER->isOnGround = false;
	PLAYER->currentState = new PlayerFallingState();

	//ground objects
	GameObject* ground = new GameObject(0, 436, 96, 12, Tag::Ground);
	listObject.push_back(ground);
	//implement grid
	grid = new Grid();
	grid->InsertToGrid(itemsContainer);
	grid->AddObject(PLAYER->shield);
}

DemoScene::~DemoScene()
{
}

void DemoScene::Update(float deltaTime)
{
	PLAYER->Update(deltaTime);
	PLAYER->HandleKeyboard(keys, deltaTime);
	grid->UpdateGrid();
	//update object
	for (auto cell : grid->visibleCells)
	{
		for (auto obj : cell->objects)
		{
			obj->Update(deltaTime);
		}
	}
	//get list colliable objects
	auto lstCollideable = grid->GetColliableObjectsWith(PLAYER);
	//player check collision
	PLAYER->CheckCollision(lstCollideable, deltaTime);
	//objects check collision
	for (auto obj : lstCollideable)
	{
		obj->OnCollision(PLAYER, deltaTime);
	}
}

void DemoScene::Draw()
{
	//render map
	map->RenderMap();
	//draw visible objects
	for (auto cell : grid->visibleCells)
	{
		for (auto obj : cell->objects)
		{
			obj->Draw();
		}
	}
	//render player
	PLAYER->Draw();
}

void DemoScene::OnKeyDown(int keyCode)
{
	keys[keyCode] = true;
	PLAYER->OnKeyDown(keyCode);
}

void DemoScene::OnKeyUp(int keyCode)
{
	keys[keyCode] = false;
	PLAYER->OnKeyUp(keyCode);
}

void DemoScene::ReleaseAll()
{
	PLAYER->Release();
	if (PLAYER)
	{
		delete PLAYER;
	}
	if (CAMERA)
	{
		delete CAMERA;
	}
	if (COLLISION)
	{
		delete COLLISION;
	}
	if (map != nullptr)
	{
		map->Release();
		delete map;
	}
}

void DemoScene::CheckCollision(BoundingBox player, std::vector<GameObject*> listObj, float deltaTime)
{
	float collisionTime;
	float normalX, normalY;
	
	Collision* collision = new Collision();
	for (auto i = 0; i < listObj.size(); i++) 
	{
		CollisionResult res = collision->SweptAABB(player, listObj[i]->GetBoundingBox(), deltaTime);
		if (res.entryTime > 0.0f && res.entryTime < 1.0f)
		{
			PLAYER->isOnGround = true;
			PLAYER->vY = 0;
		}
	}
	//
	//if (!PLAYER->isOnGround)
	//	PLAYER->vY += 10;
}
