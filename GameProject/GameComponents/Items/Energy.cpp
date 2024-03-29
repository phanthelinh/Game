#include "Energy.h"
#include "../Player/Player.h"

Energy::Energy(int x, int y, int width, int height)
{
	posX = x;
	posY = y;
	this->width = width;
	this->height = height;
	vY = 12.0f;
	energy = new Sprite("Resources/items/smallheart_12_12.png", { 0,0,12,12 });
	tag = Tag::EnergyTag;
}

Energy::Energy(RECT rect):Energy(rect.left,rect.top, rect.right-rect.left,rect.bottom-rect.top)
{
}

void Energy::OnCollision(GameObject * object, float deltaTime)
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
				SOUND->stop("item");
				SOUND->play("item");
				PLAYER->health += 10;
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

void Energy::Update(float deltaTime)
{
	if (!isDead)
	{
		posY += vY * deltaTime;
	}
}

void Energy::Draw()
{
	if(!isDead)
		Draw(D3DXVECTOR3(posX, posY, 0), CAMERA->camPosition, RECT(), D3DXVECTOR3(0, 0, 0));
}

void Energy::Draw(D3DXVECTOR3 position, D3DXVECTOR3 cameraPosition, RECT sourceRect, D3DXVECTOR3 center)
{
	if(!isDead)
		energy->Draw(position, cameraPosition, sourceRect, center);
}

BoundingBox Energy::GetBoundingBox()
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

void Energy::Release()
{
	if (energy != nullptr)
	{
		delete energy;
	}
}
