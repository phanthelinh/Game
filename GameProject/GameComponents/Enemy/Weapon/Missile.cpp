#include "Missile.h"

#define MISSILE_VX	5.0f

Missile::Missile():Weapon()
{
}

Missile::Missile(float posX, float posY, MissileType type):Weapon(posX,posY,0,0)
{
	if (type == MissileType::StraightMissile)
	{
		currAnim = new Animation("Resources/weapon/missle_straight_32_8.png", 2, 1, 2, true, 0.8);
	}
	else
	{
		currAnim = new Animation("Resources/waepon/missle_up_32_16.png", 2, 1, 2, true, 0.8);
	}
	weaponDamage = 2;
}

void Missile::OnCollision(GameObject * object, float deltaTime)
{
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
}

void Missile::Draw(D3DXVECTOR3 position, D3DXVECTOR3 cameraPosition, RECT sourceRect, D3DXVECTOR3 center)
{
	if (!isDead)
	{
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
}
