#include "BigHeart.h"

BigHeart::BigHeart(int x, int y, int width, int height)
{
	posX = x;
	posY = y;
	this->width = width;
	this->height = height;
	vY = 12.0f; 
	bigHeart = new Sprite("Resources/items/bigheart_12_12.png", { 0,0,12,12 });
	tag = Tag::BigHeartTag;
}

BigHeart::BigHeart(RECT rect):BigHeart(rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top)
{
}

void BigHeart::OnCollision(GameObject* object, float deltaTime)
{
	if (!isDead)
	{
		if (object->tag != Tag::Captain && object->tag != Tag::GroundTag)
		{
			return;
		}
		CollisionResult collideRes;
		collideRes = COLLISION->SweptAABB(object->GetBoundingBox(), GetBoundingBox());

		if (collideRes.isCollide)
		{
			switch (object->tag)
			{
			case Tag::GroundTag:
				posY += vY * collideRes.entryTime + 5;
				vY = 0;
				break;
			case Tag::Captain:
				isDead = true;
				break;
			default:
				break;
			}
		}
		//if collide with captain america
		//isDead = true;
		//display EXIT item
		//..
	}
}

void BigHeart::Update(float deltaTime)
{
	if (!isDead)
	{
		posY += vY * deltaTime;
	}
}

void BigHeart::Draw()
{
	if (!isDead)
		Draw(D3DXVECTOR3(posX, posY, 0), CAMERA->camPosition, RECT(), D3DXVECTOR3(0, 0, 0));
}

void BigHeart::Draw(D3DXVECTOR3 position, D3DXVECTOR3 cameraPosition, RECT sourceRect, D3DXVECTOR3 center)
{
	if (!isDead)
		bigHeart->Draw(position, cameraPosition, sourceRect, center);
}

BoundingBox BigHeart::GetBoundingBox()
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

void BigHeart::Release()
{
	if (bigHeart != nullptr)
	{
		delete bigHeart;
	}
}
