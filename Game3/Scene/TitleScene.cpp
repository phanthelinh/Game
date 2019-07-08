#include "TitleScene.h"

TitleScene::TitleScene()
{
	LoadContent();
}

TitleScene::~TitleScene()
{
	Memory::SafeDelete(castle);
	Memory::SafeDelete(textPushToStart);
	Memory::SafeDelete(screenSprite);
}

void TitleScene::Update(float deltaTime)
{
	castle->Update(deltaTime);
}

void TitleScene::LoadContent()
{
	castle = new Animation("Resources/scenes/title_castle_72_56.png", 15, 1, 15);
	textPushToStart = new Sprite("Resources/scenes/title_pushstart_111_7.png", RECT(), 111, 7);
	screenSprite = new Sprite("Resources/scenes/title_screen_255_240.png", RECT(), 255, 240);
}

void TitleScene::Draw()
{
	D3DXVECTOR3 defaultCamPos = D3DXVECTOR3(GlobalVar::GetScreenWidth() / 2, GlobalVar::GetScreenHeight() / 2, 0);
	//screenSprite->Draw(D3DXVECTOR3(0, 0, 0),RECT(),D3DXVECTOR2(),D3DXVECTOR2(),0.0f,D3DXVECTOR2(),D3DCOLOR_XRGB(255,255,255),D3DXVECTOR3(0,0,0));
	screenSprite->Draw(D3DXVECTOR3(0, 0, 0), defaultCamPos, RECT(), D3DXVECTOR3(0, 0, 0));
	//castle->Draw(D3DXVECTOR3(183, 106, 0), RECT(), D3DXVECTOR2(), D3DXVECTOR2(), 0.0f, D3DXVECTOR2(), D3DCOLOR_XRGB(255, 255, 255), D3DXVECTOR3(0, 0, 0));
	castle->Draw(D3DXVECTOR3(183, 106, 0), defaultCamPos, RECT(), D3DXVECTOR3(0, 0, 0));
	//textPushToStart->Draw(D3DXVECTOR3(73, 136, 0), RECT(), D3DXVECTOR2(), D3DXVECTOR2(), 0.0f, D3DXVECTOR2(), D3DCOLOR_XRGB(255, 255, 255), D3DXVECTOR3(0, 0, 0));
	textPushToStart->Draw(D3DXVECTOR3(73, 136, 0), defaultCamPos, RECT(), D3DXVECTOR3(0, 0, 0));
}

void TitleScene::OnKeyDown(int keyCode)
{
	if (keyCode == VK_RETURN) //Enter key
	{
		SceneManager::GetInstance()->ReplaceScene(new IntroScene());
	}
}

void TitleScene::OnKeyUp(int keyCode)
{
}

void TitleScene::OnMouseDown(float x, float y)
{
}
