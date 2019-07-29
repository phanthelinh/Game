#include "KeyCrystals.h"

KeyCrystals::KeyCrystals(int x, int y, int width, int height)
{
	posX = x;
	posY = y;
	this->width = width;
	this->height = height;
	vY = 12.0f;
	crystals = new Animation("Resources/items/exitgem_32_16.png", 2, 1, 2, true, 0.5);
	tag = Tag::KeyCrystalsTag;
}

KeyCrystals::KeyCrystals(RECT rect):KeyCrystals(rect.left,rect.top,rect.right-rect.left, rect.bottom-rect.top)
{
}

void KeyCrystals::OnCollision(GameObject * object, float deltaTime)
{
	if (isDead)
		return;
	if (object->tag != Tag::Captain || object->tag != Tag::Ground)
	{
		return;
	}
	auto collideRes = COLLISION->SweptAABB(object->GetBoundingBox(), GetBoundingBox(), deltaTime);
	if (collideRes.isCollide)
	{
		switch (object->tag)
		{
		case Tag::Ground:
			posY += vY * collideRes.entryTime;
			vY = 0;
			break;
		default:
			break;
		}
	}
	//if collide with captain america
	isDead = true;
	//increase score
	//..
}

void KeyCrystals::Update(float deltaTime)
{
	if (!isDead)
	{
		crystals->Update(deltaTime);
		posY += deltaTime * vY;
	}
}

void KeyCrystals::Draw()
{
	if (!isDead)
		Draw(D3DXVECTOR3(posX, posY, 0), CAMERA->camPosition, RECT(), D3DXVECTOR3(0, 0, 0));
}

void KeyCrystals::Draw(D3DXVECTOR3 position, D3DXVECTOR3 cameraPosition, RECT sourceRect, D3DXVECTOR3 center)
{
	if (!isDead)
		crystals->Draw(position, cameraPosition, sourceRect, center);
}

BoundingBox KeyCrystals::GetBoundingBox()
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

void KeyCrystals::Release()
{
	if (crystals != nullptr)
	{
		delete crystals;
	}
}
