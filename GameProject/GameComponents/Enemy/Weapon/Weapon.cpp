#include "Weapon.h"


Enemy* Weapon::currEnemy = NULL;

Weapon::Weapon():GameObject()
{
	tag = Tag::WeaponTag;
}

Weapon::Weapon(float posX, float posY, float width, float height):GameObject(posX,posY,width,height,Tag::WeaponTag)
{
}

Weapon::Weapon(RECT r):GameObject(r)
{
	tag = Tag::WeaponTag;
}

void Weapon::OnCollision(GameObject * object, float deltaTime)
{
}

RECT Weapon::GetBound()
{
	RECT r;
	r.left = posX;
	r.top = posY;
	r.right = r.left + width;
	r.bottom = r.top + height;
	return r;
}

BoundingBox Weapon::GetBoundingBox()
{
	BoundingBox b;
	b.left = posX;
	b.top = posY;
	b.right = b.left + width;
	b.bottom = b.top + height;
	b.vX = vX;
	b.vY = vY;
	return b;
}

void Weapon::Update(float deltaTime)
{
}

void Weapon::Draw()
{
}

void Weapon::Release()
{
}
