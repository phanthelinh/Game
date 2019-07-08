#include "IntroScene.h"

IntroScene::IntroScene()
{
	LoadContent();
}

IntroScene::~IntroScene()
{
	Memory::SafeDelete(playerRun);
	Memory::SafeDelete(playerComingIn);
	Memory::SafeDelete(screenSprite);
}

void IntroScene::LoadContent()
{
	screenSprite = new Sprite("Resources/scenes/intro_255_240.png", RECT(), 255, 245);
	playerRun = new Animation("Resources/simon/run_18_32.png", 3, 1, 3);
	playerComingIn = new Sprite("Resources/simon/player_coming_in_16_32.png", RECT(), 16, 32);
	playerRun->SetPosition(D3DXVECTOR3(256, 205, 0));
	playerRun->FlipHorizontal(true);
	changingScene = false;
	previousTime = 0;
}

void IntroScene::Update(float deltaTime)
{
	
	if (!changingScene)
	{
		playerRun->Update(deltaTime);
		playerRun->SetPosition(playerRun->GetPosition() - D3DXVECTOR3(1.0f, 0, 0));//decrease velocity
	}
	else
	{
		float now = GetTickCount(); //current time since the player coming sprite start
		float result = (now - previousTime) / 1000.0f;
		if (result >= 1.0f) //Changign scene only after 1 second
		{
			SceneManager::GetInstance()->ReplaceScene(new DemoScene());
		}
	}

}

void IntroScene::Draw()
{
	D3DXVECTOR3 defaultCamPos = D3DXVECTOR3(GlobalVar::GetScreenWidth() / 2, GlobalVar::GetScreenHeight() / 2, 0);
	//screenSprite->Draw(D3DXVECTOR3(0, 0, 0), RECT(), D3DXVECTOR2(), D3DXVECTOR2(), 0.0f, D3DXVECTOR2(), D3DCOLOR_XRGB(255, 255, 255), D3DXVECTOR3(0, 0, 0));
	screenSprite->Draw(D3DXVECTOR3(0, 0, 0), 
		defaultCamPos, 
		RECT(), D3DXVECTOR3(0, 0, 0));
	if (playerRun->GetPosition().x >= GlobalVar::GetScreenWidth() / 2) //player is still going to the center of the screen
	{
		playerRun->Draw(playerRun->GetPosition(), defaultCamPos);
		//playerRun->Draw();
	}
	else
	{
		//playerComingIn->Draw(playerRun->GetPosition());
		playerComingIn->Draw(playerRun->GetPosition(),
			D3DXVECTOR3(GlobalVar::GetScreenWidth() / 2, (GlobalVar::GetScreenHeight() - GlobalVar::GetGameUIArea()) / 2, 0)); //default cam
		if (!changingScene)
			previousTime = GetTickCount(); //record the time when player coming sprite start
		changingScene = true;
	}
}

void IntroScene::OnKeyDown(int keyCode)
{
}

void IntroScene::OnKeyUp(int keyCode)
{
}

void IntroScene::OnMouseDown(float x, float y)
{
}
