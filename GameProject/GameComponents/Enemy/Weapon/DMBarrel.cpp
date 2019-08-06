#include "DMBarrel.h"

#define BARREL_SPEED 5.0f

DMBarrel::DMBarrel(float posX, float posY, int direction): Weapon(posX,posY,0,0)
{
	currAnim = new Animation("Resources/weapon/DMBarrel.png", 1, 1, 1);
	weaponDamage = 2;
	tag = Tag::WeaponTag;
	startingPoint = { posX, posY, 0 };
	float direct = (direction) ? 1 : -1;
	savedvX = BARREL_SPEED * direct;
	vY = 10.0f;
	isReverse = direction;
}


void DMBarrel::Update(float deltaTime)
{
	posX += vX * deltaTime;
	posY += vY * deltaTime;
	currAnim->Update(deltaTime);
	if (posX < CAMERA->GetBound().left || posX>CAMERA->GetBound().right || posY < CAMERA->GetBound().top || posY > CAMERA->GetBound().bottom)
	{
		isDead = true;
	}
}

void DMBarrel::OnCollision(GameObject * object, float deltaTime)
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
	std::vector<GameObject*> grounds = GRID->GetVisibleGround();
	CollisionResult res;
	for (auto g : grounds)
	{
		BoundingBox temp = GetBoundingBox();
		res = COLLISION->SweptAABB(temp, g->GetBoundingBox(), deltaTime);
		if (res.isCollide)
		{
			posY += vY * res.entryTime;
			vX = savedvX;
			vY = 0;
		}
	}
}

void DMBarrel::Draw(D3DXVECTOR3 position, D3DXVECTOR3 cameraPosition, RECT sourceRect, D3DXVECTOR3 center)
{
	if (!isDead)
	{
		currAnim->_isFlipHor = isReverse;
		currAnim->Draw(position, cameraPosition, sourceRect, center);
	}
}

void DMBarrel::Draw()
{
	if (!isDead)
	{
		Draw(D3DXVECTOR3(posX, posY, 0), CAMERA->camPosition, RECT(), D3DXVECTOR3(0, 0, 0));
	}
}

RECT DMBarrel::GetBound()
{
	RECT r;
	r.left = posX - width / 2;
	r.top = posY - height;
	r.right = r.left + width;
	r.bottom = r.top + height;
	return r;
}

BoundingBox DMBarrel::GetBoundingBox()
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

void DMBarrel::Release()
{
}
