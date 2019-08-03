#include "Five.h"
#include "../../Framework/Collision.h"

Five::Five(int x, int y, int width, int height)
{
	tag = Tag::FiveTag;
	posX = x;
	posY = y;
	this->width = width;
	this->height = height;
	five = new Sprite("Resources/items/life_health_five_24_16.png", { 16,0,24,16 });
	vY = 12.0f;
}

Five::Five(RECT rect):Five(rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top)
{
}

void Five::OnCollision(GameObject * object, float deltaTime)
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
				posY += vY * collideRes.entryTime;
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
