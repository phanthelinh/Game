#include "Ghouls.h"

Ghouls::Ghouls()
{
}

Ghouls::Ghouls(int x, int y)
{
	posX = x; 
	posY = y;
	Tag = GameObjectTypes::GhoulsObj;
	animObject = new Animation("Resources/enemies/ghouls_16_32.png", 2, 1, 2,0.1);
	isLeft = true;
}

Ghouls::~Ghouls()
{
	Memory::SafeDelete(heart);
}

void Ghouls::Update(float deltaTime)
{
	animObject->Update(deltaTime);
	if (isLeft)
	{
		SetVx(-45.0f);
	}
	if (heart != NULL && !heart->isVisible)
	{
		Memory::SafeDelete(heart);
	}
	/*Update large heart in demoscene*/
	DynamicObject::Update(deltaTime);
}

void Ghouls::Draw(D3DXVECTOR3 position, D3DXVECTOR3 cameraPosition, RECT sourceRect, D3DXVECTOR3 center)
{
	if (isVisible)
		animObject->Draw(D3DXVECTOR3(posX, posY, 0), cameraPosition, RECT(), D3DXVECTOR3(0, 0, 0));
	//effect and items
	DynamicObject::Draw(hittedPosition, cameraPosition, RECT(), D3DXVECTOR3(0, 0, 0));
	if (heart != NULL)
	{
		heart->Draw(D3DXVECTOR3(), cameraPosition);
	}
}

void Ghouls::OnCollision(GameObject * entity, float deltaTime)
{
	GameCollision * collision = new GameCollision();
	Box broadPhase = collision->getBroadPhaseRect(getBox(), deltaTime);
	
	if (entity->Tag != GameObject::Ground && entity->Tag != GameObject::WhipObj)
		return;

	if (collision->isCollide(broadPhase, entity->getBox()))
	{
		float normalX = 0, normalY = 0;
		float collisionTime = collision->sweptAABB(getBox(), entity->getBox(), normalX, normalY);
		if (entity->Tag == GameObject::Ground)
		{
			if (collisionTime > 0 && collisionTime < 1)
			{
				if (normalY < 0)
				{
					AddPosition(0, GetVy()*collisionTime);
					SetVy(0);
					
				}
			}
		}
		else //collide with WHIP
		{
			if (isVisible)
			{
				isHurted = true;
				isDead = true;
				isVisible = false;
				hittedPosition = D3DXVECTOR3(posX, this->getBox().bottom - animHit->GetHeight() - 10, 0);
				heart = new LargeHeart(posX, posY);
			}
		}
	}
}

Box Ghouls::getBox()
{
	Box b;
	b.left = posX;
	b.top = posY;
	b.right = b.left + animObject->GetWidth();
	b.bottom = b.top + animObject->GetHeight();
	b.vx = GetVx();
	b.vy = GetVy();
	return b;
}

GameObject * Ghouls::GetItems()
{
	return heart;
}
