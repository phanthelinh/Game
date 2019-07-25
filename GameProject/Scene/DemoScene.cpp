#include "DemoScene.h"
#include "SceneManager.h"
#include "TitleScene.h"

DemoScene::DemoScene()
{
	PLAYER; //get instance
	PLAYER->posX = 16;
	PLAYER->posY = 390;
	PLAYER->isOnGround = false;
	map = new GameMap(16, 16, 128, 30, "Resources/map/Charleston_1_1.bmp", "Resources/map/Charleston_1_1.csv");
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
}

void DemoScene::Draw()
{
	//back->Draw(128,120);
	map->RenderMap();
	PLAYER->Draw();
}

void DemoScene::OnKeyDown(int keyCode)
{
	keys[keyCode] = true;
	PLAYER->OnKeyDown(keyCode);
	if (keyCode == VK_RETURN)
	{
		SCENES->ChangeScene(new TitleScene());
	}
}

void DemoScene::OnKeyUp(int keyCode)
{
	keys[keyCode] = false;
	PLAYER->OnKeyUp(keyCode);
}

void DemoScene::ReleaseAll()
{
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
