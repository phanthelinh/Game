#include "DynamiteNapalm.h"
#include "../Ground.h"



DynamiteNapalm::DynamiteNapalm() :Enemy()
{
	enemySubTag = EnemySubTag::DMBossTag;
	maxHealth = 14;
}

DynamiteNapalm::DynamiteNapalm(float posX, float posY) :Enemy(posX, posY, 0, 0)
{
	point = 1000;	//score when kill this boss
	currHealth = maxHealth = 14;

	animations[DMBarrelThrow] = new Animation("Resources/enemy/Dynamite Napalm/DMBarrelThrow.png", 2, 1, 2, false, 0.7f);
	animations[DMHurt] = new Animation("Resources/enemy/Dynamite Napalm/DMHurt.png", 4, 1, 2, false, 0.5f);
	animations[DMInjuredRun] = new Animation("Resources/enemy/Dynamite Napalm/DMInjuredRun.png", 3, 1, 3, true, 0.3f);
	animations[DMInjuredStand] = new Animation("Resources/enemy/Dynamite Napalm/DMInjuredStand.png", 1, 1, 1);
	animations[DMRun] = new Animation("Resources/enemy/Dynamite Napalm/DMRun.png", 3, 1, 3, true, 0.3f);
	animations[DMShot] = new Animation("Resources/enemy/Dynamite Napalm/DMShot.png", 2, 1, 2, false, 1.5f);
	animations[DMStand] = new Animation("Resources/enemy/Dynamite Napalm/DMStand.png", 1, 1, 1);
	animations[DMFall] = new Animation("Resources/enemy/Dynamite Napalm/DMStand.png", 1, 1, 1);
	animations[DMThrowWait] = new Animation("Resources/enemy/Dynamite Napalm/DMThrowWait.png", 2, 1, 2, false, 0.7f);

	SetState(DMStand);
	isReverse = false;
	isDead = false;
	isOnGround = false;
	enemySubTag = EnemySubTag::DMBossTag;
}

DynamiteNapalm::DynamiteNapalm(RECT r) :Enemy(r)
{
	enemySubTag = EnemySubTag::DMBossTag;
	maxHealth = 50;
}

void DynamiteNapalm::SetState(DMState state)
{
	prevState = currentState;
	currentState = state;
	currentAnim = animations[state];
	currentAnim->ResetAnim();
	this->width = animations[state]->_frameWidth;
	this->height = animations[state]->_frameHeight;
}

void DynamiteNapalm::OnCollision(GameObject* object, float deltaTime)
{
	CollisionResult res = COLLISION->SweptAABB(GetBoundingBox(), object->GetBoundingBoxFromCorner());
	if (res.isCollide && object->tag == GroundTag && res.sideCollided == Bottom)
	{
		isOnGround = true;
		posY += vY*res.entryTime;
		SetState(DMStand);
	}
}

void DynamiteNapalm::Update(float deltaTime)
{
	auto now = GetTickCount();

	currentAnim->_isFlipHor = isReverse;

	switch (currentState)
	{
	case DMStand:
	{
		if (vY != 0)
			vY = 0;
		break;
	}
	case DMFall:
	{
		if (vY == 0)
			vY = 10.0f;
		posY = posY + vY * deltaTime;
		break;
	}

	default:

		break;
	}
}

RECT DynamiteNapalm::GetBound()
{
	RECT r;
	r.left = posX;
	r.top = posY;
	r.right = posX + width;
	r.bottom = posY + height;
	return r;
}

BoundingBox DynamiteNapalm::GetBoundingBox()
{
	BoundingBox b;
	b.top = posY;
	b.left = posX;
	b.right = posX + width;
	b.bottom = posY + height;
	b.vX = vX;
	b.vY = vY;
	return b;
}

void DynamiteNapalm::Draw(D3DXVECTOR3 position, D3DXVECTOR3 cameraPosition, RECT sourceRect, D3DXVECTOR3 center)
{
	if (!isDead)
	{
		currentAnim->Draw(position, cameraPosition, sourceRect, center);
	}
}

void DynamiteNapalm::Draw()
{
	if (!isDead)
	{
		Draw(D3DXVECTOR3(posX, posY, 0), CAMERA->camPosition, RECT(), D3DXVECTOR3(width / 2, height, 0));
	}

}

void DynamiteNapalm::Release()
{
}
