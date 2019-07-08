#include "SmallHeart.h"
#include <math.h>

SmallHeart::SmallHeart()
{
}

SmallHeart::SmallHeart(int x, int y)
{
	posX = x; 
	posY = y;
	Tag = GameObjectTypes::SmallHeartObj;
	animObject = new Animation("Resources/items/smallheart_8_8.png", 1, 1, 1);
	stopFalling = false; 
	existTime = 0;
}

SmallHeart::~SmallHeart()
{
}

void SmallHeart::OnCollision(GameObject * entity, float deltaTime)
{
	GameCollision * collision = new GameCollision();
	Box heartPhase = collision->getBroadPhaseRect(this->getBox(), deltaTime);
	if (collision->isCollide(heartPhase, entity->getBox()))
	{
		if (entity->Tag == GameObject::Ground)
		{
			float normalX = 0, normalY = 0, collisionTime;
			collisionTime = collision->sweptAABB(this->getBox(), entity->getBox(), normalX, normalY);
			if (collisionTime > 0 && collisionTime < 1)
			{
				this->AddPosition(0, GetVy()*collisionTime);
				SetVy(0);
				stopFalling = true;
			}
		}
		else if (entity->Tag == GameObject::Simon)
		{
			this->isVisible = false;
		}
		
	}
}

void SmallHeart::Update(float deltaTime)
{
	if (!stopFalling)
	{
		posX += 3 * sin(posY);
		SetVy(20.0f);
		DynamicObject::Update(deltaTime);
	}
	else //invisible if player do no collect 3 sec
	{
		float now = GetTickCount();
		if (existTime == 0)
		{
			existTime = now;
		}
		if ((now - existTime) / 1000.0f >= 3.0f)
		{
			existTime = 0;
			isVisible = false;
		}
	}
}

void SmallHeart::Draw(D3DXVECTOR3 position, D3DXVECTOR3 cameraPosition, RECT sourceRect, D3DXVECTOR3 center)
{
	if (isVisible)
		animObject->Draw(D3DXVECTOR3(posX, posY, 0), cameraPosition, RECT(), D3DXVECTOR3(0, 0, 0));
}

Box SmallHeart::getBox()
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
