#include "Health.h"

Health::Health(int left, int top, int width, int height)
{
	posX = left;
	posY = top;
	this->width = width;
	this->height = height;
	health = new Sprite("Resources/items/life_health_five_24_16.png", { 8,0,16,16 });
	tag = Tag::HealthTag;
	vY = 12.0f;
}

Health::Health(RECT rect) :Health(rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top)
{
}

void Health::ExecuteCollision(GameObject * object)
{
}

void Health::Update(float deltaTime)
{
	if (!isDead)
	{
		posY += vY * deltaTime;
	}
}

void Health::Draw()
{
	if (!isDead)
	{
		Draw(D3DXVECTOR3(posX, posY, 0), CAMERA->camPosition, RECT(), D3DXVECTOR3(0, 0, 0));
	}
}

void Health::Draw(D3DXVECTOR3 position, D3DXVECTOR3 cameraPosition, RECT sourceRect, D3DXVECTOR3 center)
{
	if (!isDead)
	{
		health->Draw(position, cameraPosition, sourceRect, center);
	}
}

BoundingBox Health::GetBoundingBox()
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

void Health::Release()
{
	if (health != NULL)
	{
		delete health;
	}
}
