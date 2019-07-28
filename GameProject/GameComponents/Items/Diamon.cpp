#include "Diamon.h"

Diamon::Diamon(int left, int top, int width, int height, bool isSmallType)
{
	posX = left - width/2;
	posY = top - height/2;
	this->width = width;
	this->height = height;
	vY = -12.0f;
	this->isSmallType = isSmallType;
	if (isSmallType)
	{
		curDiamon = new Animation("Resources/items/diamonsmall_32_16.png", 2, 1, 2, true, 0.5);
	}
	else
	{
		curDiamon = new Animation("Resources/items/diamonlarge_32_16.png", 2, 1, 2, true, 0.5);
	}
	tag = Tag::DiamonTag;
}

Diamon::Diamon(RECT rect, bool isSmallType) :Diamon(rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, isSmallType)
{
}

void Diamon::OnCollision(GameObject * object, float deltaTime)
{
	if (!isDead)
	{
		if (object->tag != Tag::Captain && object->tag != Tag::GroundTag)
		{
			return;
		}
		CollisionResult collideRes;
		if (object->tag == GroundTag)
		{
			collideRes = COLLISION->SweptAABB(GetBoundingBox(), object->GetBoundingBox());
		}
		else
		{
			collideRes = COLLISION->SweptAABB(object->GetBoundingBox(), GetBoundingBox());
		}
		if (collideRes.isCollide)
		{
			switch (object->tag)
			{
			case Tag::GroundTag:
				posY += vY * collideRes.entryTime;
				vY = 0;
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

void Diamon::Update(float deltaTime)
{
	if (!isDead)
	{
		curDiamon->Update(deltaTime);
		posY += deltaTime * vY;
		vY += 2;
	}
}

void Diamon::Draw()
{
	if (!isDead)
		Draw(D3DXVECTOR3(posX, posY, 0), CAMERA->camPosition, RECT());//center is like player
}

void Diamon::Draw(D3DXVECTOR3 position, D3DXVECTOR3 cameraPosition, RECT sourceRect, D3DXVECTOR3 center)
{
	if (!isDead)
		curDiamon->Draw(position, cameraPosition, sourceRect, center);
}

BoundingBox Diamon::GetBoundingBox()
{
	BoundingBox b;
	b.left = posX + width/2;
	b.top = posY + height/2;
	b.right = b.left + width;
	b.bottom = b.top + height;
	b.vX = 0;
	b.vY = vY;
	return b;
}

void Diamon::Release()
{
	if (curDiamon != nullptr)
		delete curDiamon;
}
