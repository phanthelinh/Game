#include "DemoScene.h"
#include "SceneManager.h"
#include "TitleScene.h"

DemoScene::DemoScene()
{
	PLAYER; //get instance
	//map = new GameMap(16, 16, 128, 15, "Resources/map/temp_cut.png", "Resources/map/temp.csv");//
	map = new GameMap(16, 16, 128, 30, "Resources/map/Charleston_cut.png", "Resources/map/Charleston_1_1.csv");
	//map = new GameMap(16, 16, 80, 60, "Resources/map/Pittsburgh_1_1.bmp", "Resources/map/Pittsburgh_1_1.csv");
	life = new Life(128, 300, 8, 16);
	lstItemContainerRect = Util::GetObjectDataFromFile("Resources/items/itemcontainer.txt");
	if (lstItemContainerRect.size() > 0)
	{
		for (auto r : lstItemContainerRect)
		{
			itemsContainer.insert(new ItemsContainer(r));
		}
	}
	PLAYER->posX = 16;
	PLAYER->posY = 390;
	PLAYER->isOnGround = false;
	PLAYER->currentState = new PlayerFallingState();
	//map = new GameMap(16, 16, 128, 30, "Resources/map/Charleston_1_1.bmp", "Resources/map/Charleston_1_1.csv");
	GameObject* ground = new GameObject(0, 436, 96, 12, Tag::Ground);
	listObject.push_back(ground);
}

DemoScene::~DemoScene()
{
}

void DemoScene::Update(float deltaTime)
{
	PLAYER->Update(deltaTime);
	PLAYER->HandleKeyboard(keys, deltaTime);
	//CheckCollision(PLAYER->GetBoundingBox(), listObject, deltaTime);
	life->Update(deltaTime);
	////check collision
	//if (!PLAYER->shield->isDead)
	//{
	//	itemsContainer->ExecuteCollision(PLAYER->shield);
	//}
}

void DemoScene::Draw()
{
	map->RenderMap();
	for (auto i : itemsContainer)
	{
		i->Draw();
	}
	life->Draw();
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
