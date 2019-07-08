#include "Candle.h"

Candle::Candle()
{
}

Candle::Candle(int x, int y)
{
	posX = x;
	posY = y;
	Tag = GameObjectTypes::CandleObj;
	animObject = new Animation("Resources/items/candle_16_16.png", 2, 1, 2);
	heart = NULL;
}

Candle::~Candle()
{
	Memory::SafeDelete(heart);
}

void Candle::Update(float deltaTime)
{
	animObject->Update(deltaTime);
	DynamicObject::Update(deltaTime);
	if (heart != NULL && !heart->isVisible)
	{
		Memory::SafeDelete(heart);
	}
	/*Update small heart in demoscene*/
}

void Candle::Draw(D3DXVECTOR3 position, D3DXVECTOR3 cameraPosition, RECT sourceRect, D3DXVECTOR3 center)
{
	if(isVisible)
		animObject->Draw(D3DXVECTOR3(posX, posY, 0), cameraPosition, RECT(), D3DXVECTOR3(0, 0, 0));
	DynamicObject::Draw(hittedPosition, cameraPosition, RECT(), D3DXVECTOR3(0, 0, 0));
	if (heart != NULL)
	{
		heart->Draw(D3DXVECTOR3(), cameraPosition);
	}
}

void Candle::OnCollision(GameObject * entity, float deltaTime)
{
	if (entity->Tag == GameObjectTypes::WhipObj)
	{
		GameCollision * collision = new GameCollision();
		if (collision->isCollide(entity->getBox(), getBox()))
		{
			if (isVisible)
			{
				isHurted = true;
				isDead = true;
				isVisible = false;
				hittedPosition = D3DXVECTOR3(posX, this->getBox().bottom - animHit->GetHeight() - 10, 0);
				heart = new SmallHeart(posX, posY);
			}
		}
	}
}

GameObject * Candle::GetItems()
{
	return heart;
}
