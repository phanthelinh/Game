#include "Five.h"

Five::Five(int left, int top, int width, int height)
{
	tag = Tag::FiveTag;
	posX = left;
	posY = top;
	this->width = width;
	this->height = height;
	five = new Sprite("Resources/items/life_health_five_24_16.png", { 16,0,24,16 });
	vY = 12.0f;
}

Five::Five(RECT rect):Five(rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top)
{
}

void Five::ExecuteCollision(GameObject * object)
{
}

void Five::Update(float deltaTime)
{
	if (!isDead)
	{
		posY += vY * deltaTime;
	}
}

void Five::Draw()
{
	if (!isDead)
	{
		Draw(D3DXVECTOR3(posX, posY, 0), CAMERA->camPosition, RECT(), D3DXVECTOR3(0, 0, 0));
	}
}

void Five::Draw(D3DXVECTOR3 position, D3DXVECTOR3 cameraPosition, RECT sourceRect, D3DXVECTOR3 center)
{
	if (!isDead)
	{
		five->Draw(position, cameraPosition, sourceRect, center);
	}
}

BoundingBox Five::GetBoundingBox()
{
	BoundingBox b;
	b.left = posX;
	b.top = posY;
	b.right = b.left + width;
	b.bottom = b.top + height;
	b.vX = 0;
	b.vY = vY;
	return b;
}

void Five::Release()
{
	if (five != NULL)
	{
		delete five;
	}
}
