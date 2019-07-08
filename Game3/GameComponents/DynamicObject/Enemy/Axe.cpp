#include "Axe.h"

Axe::Axe()
{
}

Axe::Axe(float x, float y)
{
	Tag = GameObjectTypes::AxeObj;
	posX = x;
	posY = y;
	animObject = new Animation("Resources/enemies/axe_15_15.png", 4, 1, 4, 0.15);
	startPos.x = x;
	startPos.y = y;
}

Axe::~Axe()
{
}

void Axe::Update(float deltaTime)
{
	animObject->Update(deltaTime);
	if (isToLeft)
	{
		SetVx(-ACCELERATE_X);
	}
	else
	{
		SetVx(ACCELERATE_X);
	}
	DynamicObject::Update(deltaTime);
	if (GetPosition().x < startPos.x - RANGE_X)
	{
		isToLeft = false;
	}
	if (GetPosition().x > startPos.x + RANGE_X)
	{
		isToLeft = true;
	}
}

void Axe::Draw(D3DXVECTOR3 position, D3DXVECTOR3 cameraPosition, RECT sourceRect, D3DXVECTOR3 center)
{
	animObject->Draw(position, cameraPosition, sourceRect, center);
}

void Axe::IsRenderLeft(bool flag)
{
	isToLeft = flag;
}

Box Axe::getBox()
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
