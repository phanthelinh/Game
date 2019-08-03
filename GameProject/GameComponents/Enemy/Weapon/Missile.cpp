#include "Missile.h"
#include "../../Player/Player.h"

#define MISSILE_VX	6.5f
#define MISSILE_MAX_DISTANCE_BEFORE_DIRECTION_CHANGE 30.0f


Missile::Missile(float posX, float posY, MissileType type):Weapon(posX,posY,0,0)
{
	this->missileType = type;
	startingPoint = { posX, posY, 0 };
	vX = MISSILE_VX;
	if (type == MissileType::StraightMissile)
	{
		currAnim = new Animation("Resources/weapon/missle_straight_32_8.png", 2, 1, 2, true, 0.8);
	}
	else
	{
		currAnim = new Animation("Resources/weapon/missle_straight_32_8.png", 2, 1, 2, true, 0.8);
		subAnim = new Animation("Resources/weapon/missle_up_32_16.png", 2, 1, 2, true, 0.8);
	}
	weaponDamage = 2;
}

void Missile::OnCollision(GameObject * object, float deltaTime)
{
	if (object->tag == Tag::Captain)
	{
		auto colRes = COLLISION->SweptAABB(GetBoundingBox(), object->GetBoundingBox(), deltaTime);
		if (colRes.isCollide && PLAYER->isImmu == false)
		{
			PLAYER->health -= weaponDamage;
			if (PLAYER->health <= 0)
				PLAYER->ChangeState(Die);
			else
				PLAYER->ChangeState(Hurt);
		}
	}
}

RECT Missile::GetBound()
{
	RECT r;
	r.left = posX;
	r.top = posY;
	r.right = r.left + width;
	r.bottom = r.top + height;
	return r;
}

BoundingBox Missile::GetBoundingBox()
{
	BoundingBox r;
	r.left = posX;
	r.top = posY;
	r.right = r.left + width;
	r.bottom = r.top + height;
	r.vX = vX;
	r.vY = vY;
	return r;
}

void Missile::Update(float deltaTime)
{
	posX += vX * deltaTime*(-1.0f); //always fly to the left side
	posY += vY * deltaTime;
	if (missileType == MissileType::StraightUpwardMissile)
	{
		if (abs(posX - startingPoint.x) >= MISSILE_MAX_DISTANCE_BEFORE_DIRECTION_CHANGE)
		{
			vY = -vX;
			currAnim = subAnim;
		}
	}
	currAnim->Update(deltaTime);
	//check for if missle is out of camera bound
	if(!IsCollide(CAMERA->GetBound()))
	{
		isDead = true;
	}
}

void Missile::Draw(D3DXVECTOR3 position, D3DXVECTOR3 cameraPosition, RECT sourceRect, D3DXVECTOR3 center)
{
	if (!isDead)
	{
		currAnim->_isFlipHor = false;
		currAnim->Draw(position, cameraPosition, sourceRect, center);
	}
}

void Missile::Draw()
{
	if (!isDead)
	{
		Draw(D3DXVECTOR3(posX, posY, 0), CAMERA->camPosition, RECT(), D3DXVECTOR3(0, 0, 0));
	}
}

void Missile::Release()
{
	if (subAnim != NULL)
		delete subAnim;
}
