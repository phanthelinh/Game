#include "TitleScene.h"

TitleScene::TitleScene()
{
	back = new Sprite("Resources/scenes/title_screen_255_240.png");
}

void TitleScene::Update(float deltaTime)
{
}

void TitleScene::Draw()
{
	back->Draw(128, 120);
}

void TitleScene::OnKeyDown(int keyCode)
{
}

void TitleScene::OnKeyUp(int keyCode)
{
}

void TitleScene::ReleaseAll()
{
}
