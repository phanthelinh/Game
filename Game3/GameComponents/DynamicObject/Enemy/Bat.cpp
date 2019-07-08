#include "Bat.h"
#include <math.h>

Bat::Bat()
{
}

Bat::Bat(int x, int y, bool isLeft)
{
	posX = x; 
	posY = y;
	this->isLeft = isLeft;
	Tag = GameObjectTypes::BatObj;
	animObject = new Animation("Resources/enemies/bats_16_16.png", 3, 1, 3, 0.15);
	animObject->FlipHorizontal(!isLeft);
	heart = NULL;
}

Bat::~Bat()
{
	Memory::SafeDelete(heart);
}

void Bat::Update(float deltaTime)
{
	/*Update large heart in demoscene*/
	
	animObject->Update(deltaTime);
	if (isLeft)
	{
		SetVx(-50.0f);
	}
	else
	{
		SetVx(50.0f);
	}
	posY += 4 * sin(posX);
	if (heart != NULL && !heart->isVisible)
	{
		Memory::SafeDelete(heart);
	}
	DynamicObject::Update(deltaTime);
}

void Bat::Draw(D3DXVECTOR3 position, D3DXVECTOR3 cameraPosition, RECT sourceRect, D3DXVECTOR3 center)
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

void Bat::OnCollision(GameObject * entity, float deltaTime)
{
	GameCollision * collision = new GameCollision();
	Box broadPhase = collision->getBroadPhaseRect(getBox(), deltaTime);

	if (entity->Tag != GameObject::Ground && entity->Tag != GameObject::WhipObj)
		return;

	if (collision->isCollide(broadPhase, entity->getBox()))
	{
		if (entity->Tag == GameObject::WhipObj)
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
	Memory::SafeDelete(collision);
}

Box Bat::getBox()
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

GameObject * Bat::GetItems()
{
	return nullptr;
}
