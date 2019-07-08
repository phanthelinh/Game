#include "AxeKnight.h"

AxeKnight::AxeKnight()
{
}

AxeKnight::AxeKnight(float x, float y)
{
	Tag = GameObjectTypes::AxeKnightObj;
	animObject = new Animation("Resources/enemies/axeknight_24_32.png", 2, 1, 2, 0.15);
	throwing = false; //can throw now
	SetPosition(x, y);
	isVisible = true;
	isMoveLeft = true;
	oldX = x;
	oldY = y;
	SetVx(-ACCELARATE_X);
	prev1 = prevTime = 0;
	isEnable = false;
}

AxeKnight::~AxeKnight()
{
}

void AxeKnight::Update(float deltaTime)
{
	animObject->Update(deltaTime);
	if (isVisible)
		reviveTime = 0;
	else
		reviveTime += deltaTime;
	if (playerPos.x > posX)
	{
		isMoveLeft = false; //turn to right
		animObject->FlipHorizontal(true);
		if (playerPos.x - posX <= 30.0f) //keep the distance
		{
			isEnable = true;
			//backward
			SetVx(-ACCELARATE_X);
		}
		else isEnable = false;
	}
	else //player on the left side
	{
		isMoveLeft = true;
		animObject->FlipHorizontal(false);
		if (posX - playerPos.x <= 30.0f) //keep the distance
		{
			isEnable = true;
			//backward
			SetVx(ACCELARATE_X);
		}
		else isEnable = false;
	}

	DynamicObject::Update(deltaTime);
	if (GetPosition().x > oldX + DISTANCE_MAX && !isEnable)
	{
		isMoveLeft = true;
		animObject->FlipHorizontal(false);
		SetVx(-ACCELARATE_X);
	}
	if (GetPosition().x < oldX - DISTANCE_MAX && !isEnable)
	{
		isMoveLeft = false;
		animObject->FlipHorizontal(true);
		SetVx(ACCELARATE_X);
	}

	if (axe == NULL)
	{
		float now = GetTickCount();
		if (prevTime == 0)
			prevTime = now;
		if ((now - prevTime) / 1000 >= 3.0f)
		{
			axe = new Axe(this->posX, this->posY);
			axe->IsRenderLeft(isMoveLeft);
			prevTime = now;
		}
	}
	if (axe != NULL)
	{
		axe->Update(deltaTime);
		CheckCollisionWithAxe(deltaTime);
	}
}

void AxeKnight::Draw(D3DXVECTOR3 position, D3DXVECTOR3 cameraPosition, RECT sourceRect, D3DXVECTOR3 center)
{
	if (isVisible)
	{
		animObject->Draw(D3DXVECTOR3(posX, posY, 0), cameraPosition, sourceRect, center);
		if (axe != NULL)
		{
			axe->Draw(axe->GetPosition(), cameraPosition, RECT(), center); //sanme center with AxeKnight
		}
	}
}

void AxeKnight::SetPlayerPosition(D3DXVECTOR3 player)
{
	playerPos = player;
}

Box AxeKnight::getBox()
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

void AxeKnight::CheckCollisionWithAxe(float deltaTime)
{
	GameCollision* collision = new GameCollision();
	Box axeBox = axe->getBox();
	Box broadPhase = collision->getBroadPhaseRect(axeBox, deltaTime);
	Box knightBox = this->getBox();
	knightBox.vx = knightBox.vy = 0;
	
	if (collision->isCollide(broadPhase, this->getBox()))
	{
		float norX, norY;
		float collisionTime = collision->sweptAABB(axeBox, this->getBox(), norX, norY);
		if (collisionTime > 0.0f && collisionTime < 1.0f)
		{
			//delete Axe
			Memory::SafeDelete(axe);
			throwing = false;
			prevTime = 0;
		}
	}
	Memory::SafeDelete(collision);
}

