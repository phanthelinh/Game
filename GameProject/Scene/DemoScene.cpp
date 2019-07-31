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

	//implement grid
	GRID;
	GRID->InsertToGrid(itemsContainer);
	GRID->AddObject(PLAYER->shield);
	//GRID->listGround = listObject;
	domesto = new Domesto(120, 460);
	GRID->AddObject(domesto);

	//enemy test
	boss = new WizardBoss();
	boss->posX = 70;
	boss->posY = 436;
	runningman = new RunningMan(240, 436, 0, 1);
}

DemoScene::~DemoScene()
{
}

void DemoScene::Update(float deltaTime)
{
	//object will be move to another cell, that is included in Update Grid
	GRID->UpdateGrid(deltaTime);
	runningman->Update(deltaTime);
	//update object
	visibleObject.clear();
	visibleObject = GRID->GetVisibleObjects();
	PLAYER->Update(deltaTime);
	PLAYER->HandleKeyboard(keys, deltaTime);
	
	//
	//COLLISION
	//
	//check collision Ground <> Player
	for (auto g : GRID->GetVisibleGround())
	{
		PLAYER->OnCollision(g, deltaTime);
	}
	//get list colliable objects with player
	auto lstCollideable = GRID->GetColliableObjectsWith(PLAYER, deltaTime);
	//player check collision
	PLAYER->CheckCollision(lstCollideable, deltaTime);
	// visible objects check collision with player
	for (auto obj : visibleObject)
	{
		obj->OnCollision(PLAYER, deltaTime);
	}
}

void DemoScene::Draw()
{
	//render map
	map->RenderMap();
	//draw visible objects
	for (auto obj : visibleObject)
	{
		obj->Draw();
	}
	//render player
	PLAYER->Draw();
	boss->Draw();
	runningman->Draw();
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

void DemoScene::CheckCollision(BoundingBox player, std::unordered_set<GameObject*> listObj, float deltaTime)
{
	
	/*for (auto i = 0; i < listObj.size(); i++) 
	{
		CollisionResult res = COLLISION->SweptAABB(player, listObj[i]->GetBoundingBox(), deltaTime);
		if (res.entryTime > 0.0f && res.entryTime < 1.0f)
		{
			PLAYER->isOnGround = true;
			PLAYER->vY = 0;
		}
	}*/
	//
	//if (!PLAYER->isOnGround)
	//	PLAYER->vY += 10;
}
