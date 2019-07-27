#include "Life.h"

Life::Life(int left, int top, int width, int height)
{
	posX = left;
	posY = top;
	this->width = width;
	this->height = height;
	life = new Sprite("Resources/items/life_health_five_24_16.png", { 0,0,8,16 });
	tag = Tag::LifeTag;
	vY = 12.0f;
}

Life::Life(RECT rect) :Life(rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top)
{
}

void Life::OnCollision(GameObject * object, float deltaTime)
{
}

void Life::Update(float deltaTime)
{
	if (!isDead)
	{
		posY += vY * deltaTime;
	}
}

void Life::Draw()
{
	if (!isDead)
	{
		Draw(D3DXVECTOR3(posX, posY, 0), CAMERA->camPosition, RECT(), D3DXVECTOR3(0, 0, 0));
	}
}

void Life::Draw(D3DXVECTOR3 position, D3DXVECTOR3 cameraPosition, RECT sourceRect, D3DXVECTOR3 center)
{
	if (!isDead)
	{
		life->Draw(position, cameraPosition, sourceRect, center);
	}
}

BoundingBox Life::GetBoundingBox()
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

void Life::Release()
{
	if (life != NULL)
	{
		delete life;
	}
}
