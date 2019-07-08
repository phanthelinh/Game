#include "BoneTower.h"

BoneTower::BoneTower()
{
}

BoneTower::BoneTower(int x, int y, bool isLeft)
{
	posX = x;
	posY = y;
	prevTime = 0;
	Tag = GameObjectTypes::BoneTowerObj;
	animObject = new Animation("Resources/enemies/bonetower_16_32.png", 1, 1, 1);
	this->isLeft = isLeft;
	bullet = NULL;
	//Set fliphorizontal
	if (isLeft)
	{
		animObject->FlipHorizontal(false);

	}
	else
	{
		animObject->FlipHorizontal(true);
		//Set vx
	}
}

BoneTower::~BoneTower()
{
	Memory::SafeDelete(bullet);
}

void BoneTower::Update(float deltaTime)
{
	//update bullet at DemoScene

	//re-init Bullet when it was cleared after 1 second
	float now = GetTickCount();
	if (prevTime == 0)
	{
		prevTime = now;
	}
	if ((now - prevTime) / 1000 >= 1.0f)
	{
		bullet = new Bullet(posX, posY + 5, isLeft);
		prevTime = 0;
	}
	else
	{
		Sleep(1.0f - (now - prevTime) / 1000.0f);
	}
}

void BoneTower::Draw(D3DXVECTOR3 position, D3DXVECTOR3 cameraPosition, RECT sourceRect, D3DXVECTOR3 center)
{
	if (isVisible)
	{
		animObject->Draw(D3DXVECTOR3(posX, posY, 0), cameraPosition, sourceRect, center);
	}
	if (bullet != NULL)
	{
		bullet->Draw(D3DXVECTOR3(), cameraPosition, sourceRect, center); //same with center
																		 //check for bullet out of screen or be killed by player, announce for reinit
		if (bullet->GetPosition().x > cameraPosition.x + GlobalVar::GetScreenWidth() / 2 ||
			bullet->GetPosition().x < cameraPosition.x - GlobalVar::GetScreenWidth() / 2)
		{
			Memory::SafeDelete(bullet);
		}
	}
}

void BoneTower::SetPlayerPosition(D3DXVECTOR3 player)
{
}

Box BoneTower::getBox()
{
	Box b;
	b.left = GetPosition().x;
	b.top = GetPosition().y;
	b.right = b.left + animObject->GetWidth();
	b.bottom = b.top + animObject->GetHeight();
	b.vx = GetVx();
	b.vy = GetVy();
	return b;
}
