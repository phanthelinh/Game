#include "Bullet.h"



Bullet::Bullet(float posX, float posY, int direction): Weapon(posX,posY,0,0)
{
	startingPoint = { posX, posY, 0};
	vX = BULLET_SPEED * direction;
	currAnim = new Animation("Resources/weapon/RunningManBullet.png", 1, 1, 1);
	weaponDamage = 2;
	tag = Tag::WeaponTag;
}


void Bullet::Update(float deltaTime)
{
	posX += vX * deltaTime;
	posY += vY * deltaTime;
	currAnim->Update(deltaTime);
	if (posX < CAMERA->GetBound().left || posX>CAMERA->GetBound().right || posY < CAMERA->GetBound().top || posY > CAMERA->GetBound().bottom)
	{
		isDead = true;
	}
}

void Bullet::OnCollision(GameObject * object, float deltaTime)
{
	if (object->tag == Tag::ShieldTag)
	{
		auto colRes = COLLISION->SweptAABB(GetBoundingBox(), object->GetBoundingBox(), deltaTime);
		if (colRes.isCollide && PLAYER->shieldFlying == false)
		{
			posX += vX * colRes.entryTime;
			posY += vY * colRes.entryTime;
			this->vY = abs(vX) * -1;
			this->vX = 0.0;
		}
	}
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

void Bullet::Draw(D3DXVECTOR3 position, D3DXVECTOR3 cameraPosition, RECT sourceRect, D3DXVECTOR3 center)
{
	if (!isDead)
	{
		currAnim->_isFlipHor = isReverse;
		currAnim->Draw(position, cameraPosition, sourceRect, center);
	}
}

void Bullet::Draw()
{
	if (!isDead)
	{
		Draw(D3DXVECTOR3(posX, posY, 0), CAMERA->camPosition, RECT(), D3DXVECTOR3(0, 0, 0));
	}
}

RECT Bullet::GetBound()
{
	RECT r;
	r.left = posX - width / 2;
	r.top = posY - height;
	r.right = r.left + width;
	r.bottom = r.top + height;
	return r;
}

BoundingBox Bullet::GetBoundingBox()
{
	BoundingBox r;
	r.left = posX - width / 2;
	r.top = posY - height;
	r.right = r.left + width;
	r.bottom = r.top + height;
	r.vX = vX;
	r.vY = vY;
	return r;
}

void Bullet::Release()
{
}
