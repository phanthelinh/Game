#include "PowerStone.h"

PowerStone::PowerStone(int x, int y, int width, int height, bool isSmallType)
{
	posX = x;
	posY = y;
	this->width = width;
	this->height = height;
	vY = -13.0f;
	this->isSmallType = isSmallType;
	if (isSmallType)
	{
		curDiamon = new Animation("Resources/items/diamonsmall_32_16.png", 2, 1, 2, true, 0.5);
	}
	else
	{
		curDiamon = new Animation("Resources/items/diamonlarge_32_16.png", 2, 1, 2, true, 0.5);
	}
	tag = Tag::PowerStoneTag;
}

PowerStone::PowerStone(RECT rect, bool isSmallType) :PowerStone(rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, isSmallType)
{
}

void PowerStone::OnCollision(GameObject * object, float deltaTime)
{
	if (!isDead)
	{
		if (object->tag != Tag::Captain && object->tag != Tag::GroundTag)
		{
			return;
		}
		CollisionResult collideRes;
		collideRes = COLLISION->SweptAABB(GetBoundingBox(), object->GetBoundingBox());
		
		if (collideRes.isCollide)
		{
			switch (object->tag)
			{
			case Tag::GroundTag:
				posY += vY * collideRes.entryTime + 20;
				vY = 0;
				//firstTimeCollideGround = GetTickCount();
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

void PowerStone::Update(float deltaTime)
{
	if (!isDead)
	{
		curDiamon->Update(deltaTime);
		posY += deltaTime * vY;
		vY = vY == 0 ? 0 : vY + 2;
		auto now = GetTickCount();
		if ((now - firstTimeCollideGround) / 1000.0f >= 10.0f)
		{
		}
	}
}

void PowerStone::Draw()
{
	if (!isDead)
		Draw(D3DXVECTOR3(posX, posY, 0), CAMERA->camPosition, RECT());//center is like player
}

void PowerStone::Draw(D3DXVECTOR3 position, D3DXVECTOR3 cameraPosition, RECT sourceRect, D3DXVECTOR3 center)
{
	if (!isDead)
		curDiamon->Draw(position, cameraPosition, sourceRect, center);
}

BoundingBox PowerStone::GetBoundingBox()
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

void PowerStone::Release()
{
	if (curDiamon != nullptr)
		delete curDiamon;
}
