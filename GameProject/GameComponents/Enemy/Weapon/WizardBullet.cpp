#include "WizardBullet.h"
#include "../../Player/Player.h"

WizardBullet::WizardBullet(float posX, float posY, WizardBulletType type):Weapon(posX, posY, 0, 0)
{
	this->bulletType = type;
	startingPoint = { posX, posY, 0 };
	if (type == HorizontalBullet)
	{
		vX = 5.0f;
		vY = 0;
		currAnim = new Animation("Resources/weapon/Bullet_Small.png", 1, 1, 1, true, 0.8);
	}
	else
	{
		vX = 0;
		vY = 5.0f;
		currAnim = new Animation("Resources/weapon/Bullet_Doc.png", 1, 1, 1, true, 0.8);
	}
	weaponDamage = 5;
}

void WizardBullet::OnCollision(GameObject* object, float deltaTime)
{
	if (object->tag == Tag::Captain)
	{
		auto colRes = COLLISION->SweptAABB(GetBoundingBox(), object->GetBoundingBox(), deltaTime);
		if (colRes.isCollide)
		{
			PLAYER->ChangeState(Hurt);
		}
	}
}

RECT WizardBullet::GetBound()
{
	RECT r;
	r.left = posX;
	r.top = posY;
	r.right = r.left + width;
	r.bottom = r.top + height;
	return r;
}

BoundingBox WizardBullet::GetBoundingBox()
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

void WizardBullet::Update(float deltaTime)
{
	if (bulletType == HorizontalBullet)
	{
		posX += vX * deltaTime * (isReverse ? 1.0f : -1.0f);
	}
	else 
	{
		posY += vY * deltaTime;
	}
	currAnim->Update(deltaTime);
	//check for if missle is out of camera bound
	if (posX < CAMERA->GetBound().left || posX>CAMERA->GetBound().right || posY < CAMERA->GetBound().top || posY > CAMERA->GetBound().bottom)
	{
		isDead = true;
	}
}

void WizardBullet::Draw(D3DXVECTOR3 position, D3DXVECTOR3 cameraPosition, RECT sourceRect, D3DXVECTOR3 center)
{
	if (!isDead)
	{
		currAnim->_isFlipHor = isReverse;
		currAnim->Draw(position, cameraPosition, sourceRect, center);
	}
}

void WizardBullet::Draw()
{
	if (!isDead)
	{
		Draw(D3DXVECTOR3(posX, posY, 0), CAMERA->camPosition, RECT(), D3DXVECTOR3(0, 0, 0));
	}
}

void WizardBullet::Release()
{
}
