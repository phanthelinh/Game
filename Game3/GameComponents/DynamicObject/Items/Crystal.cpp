#include "Crystal.h"

Crystal::Crystal()
{

}

Crystal::Crystal(int x, int y)
{
	posX = x;
	posY = y;
	Tag = GameObjectTypes::CrystalObj;
	animObject = new Animation("Resources/items/crystal_16_16.png", 2, 1, 2);
	stopFalling = true;
	onGround = false;
	fallingTime = 0;
}

Crystal::~Crystal()
{
}

void Crystal::OnCollision(GameObject * entity, float deltaTime)
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

void Crystal::Update(float deltaTime)
{
	animObject->Update(deltaTime);
	if (stopFalling)
	{
		float now = GetTickCount();
		if (fallingTime == 0)
		{
			fallingTime = now;
		}
		if ((now - fallingTime) / 1000.0f >= 2.0f)
		{
			stopFalling = false;
			fallingTime = 0;
		}
	}
	else
	{
		if(!onGround)
			SetVy(50.0f);
		DynamicObject::Update(deltaTime);
	}
}

void Crystal::Draw(D3DXVECTOR3 position, D3DXVECTOR3 cameraPosition, RECT sourceRect, D3DXVECTOR3 center)
{
	if (isVisible)
		animObject->Draw(D3DXVECTOR3(posX, posY, 0), cameraPosition, RECT(), D3DXVECTOR3(0, 0, 0));
}

Box Crystal::getBox()
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
