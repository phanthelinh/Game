#include "DemoScene.h"
#include "SceneManager.h"
#include "TitleScene.h"

DemoScene::DemoScene()
{
	back = new Sprite("Resources/scenes/intro_255_240.png");
	simon = new Animation("Resources/simon/run_18_32.png", 2, 1, 2);
}

DemoScene::~DemoScene()
{
}

void DemoScene::Update(float deltaTime)
{
	simon->Update(deltaTime);
}

void DemoScene::Draw()
{
	back->Draw(128,120);
	simon->Draw(128, 120);
}

void DemoScene::OnKeyDown(int keyCode)
{
	if (keyCode == VK_RETURN)
	{
		SCENES->ChangeScene(new TitleScene());
	}
}

void DemoScene::OnKeyUp(int keyCode)
{
}

void DemoScene::ReleaseAll()
{
}
