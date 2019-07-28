#include "Rescue.h"

Rescue::Rescue(int left, int top, int width, int height)
{
	posX = left;
	posY = top;
	this->width = width;
	this->height = height;
	rescue = new Sprite("Resources/items/life_health_five_24_16.png", { 8,0,16,16 });
	tag = Tag::HealthTag;
	vY = 12.0f;
}

Rescue::Rescue(RECT rect) :Rescue(rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top)
{
}

void Rescue::OnCollision(GameObject * object, float deltaTime)
{
}

void Rescue::Update(float deltaTime)
{
	if (!isDead)
	{
		posY += vY * deltaTime;
	}
}

void Rescue::Draw()
{
	if (!isDead)
	{
		Draw(D3DXVECTOR3(posX, posY, 0), CAMERA->camPosition, RECT(), D3DXVECTOR3(0, 0, 0));
	}
}

void Rescue::Draw(D3DXVECTOR3 position, D3DXVECTOR3 cameraPosition, RECT sourceRect, D3DXVECTOR3 center)
{
	if (!isDead)
	{
		rescue->Draw(position, cameraPosition, sourceRect, center);
	}
}

BoundingBox Rescue::GetBoundingBox()
{
	BoundingBox b;
	b.left = posX;
	b.top = posY;
	b.right = b.left + width;
	b.bottom = b.top + height;
	b.vX = 0;
	b.vY = 0;
	return b;
}

void Rescue::Release()
{
	if (rescue != NULL)
	{
		delete rescue;
	}
}
