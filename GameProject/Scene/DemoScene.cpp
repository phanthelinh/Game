#include "DemoScene.h"
#include "SceneManager.h"
#include "TitleScene.h"

DemoScene::DemoScene()
{
	PLAYER; //get instance
	map = new GameMap(16, 16, 128, 30, "Resources/map/Charleston_1_1.bmp", "Resources/map/Charleston_1_1.csv");
}

DemoScene::~DemoScene()
{
}

void DemoScene::Update(float deltaTime)
{
	PLAYER->Update(deltaTime);
	PLAYER->HandleKeyboard(keys, deltaTime);
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
