#include "DynamiteNapalm.h"
#include "../Ground.h"



DynamiteNapalm::DynamiteNapalm() :Enemy()
{
}

DynamiteNapalm::DynamiteNapalm(float posX, float posY) :Enemy(posX, posY, 0, 0)
{
	point = 1000;	//score when kill this boss
	currHealth = maxHealth = 14;

	animations[DMBarrelThrow] = new Animation("Resources/enemy/Dynamite Napalm/DMBarrelThrow.png", 2, 1, 2, false, 0.7f);
	animations[DMHurt] = new Animation("Resources/enemy/Dynamite Napalm/DMHurt.png", 2, 1, 2, true, 0.5f);
	animations[DMInjuredRun] = new Animation("Resources/enemy/Dynamite Napalm/DMInjuredRun.png", 3, 1, 3, true, 0.3f);
	animations[DMInjuredStand] = new Animation("Resources/enemy/Dynamite Napalm/DMInjuredStand.png", 1, 1, 1);
	animations[DMRun] = new Animation("Resources/enemy/Dynamite Napalm/DMRun.png", 3, 1, 3, true, 0.3f);
	animations[DMShot] = new Animation("Resources/enemy/Dynamite Napalm/DMShot.png", 2, 1, 2, false, 1.5f);
	animations[DMStand] = new Animation("Resources/enemy/Dynamite Napalm/DMStand.png", 1, 1, 1);
	animations[DMFall] = new Animation("Resources/enemy/Dynamite Napalm/DMStand.png", 1, 1, 1);
	animations[DMThrowWait] = new Animation("Resources/enemy/Dynamite Napalm/DMThrowWait.png", 2, 1, 2, false, 0.7f);

	currentState = DMFall;
	SetState(DMFall);
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
	std::vector<GameObject*> grounds = GRID->GetVisibleGround();
	CollisionResult res;
	for (auto g : grounds)
	{
		BoundingBox temp = GetBoundingBox();
		res = COLLISION->SweptAABB(temp, g->GetBoundingBox(), deltaTime);
		if (res.isCollide && res.sideCollided == Bottom)
		{
			isOnGround = true;
			posY += vY*res.entryTime;
			SetState(DMStand);
		}
	}
}

void DynamiteNapalm::Update(float deltaTime)
{
	auto now = GetTickCount();

	switch (currentState)
	{
	case DMStand:
	{
		dmbarrel = new DMBarrel(posX, posY, isReverse);
		GRID->AddObject(dmbarrel);
		if (vY != 0)
			vY = 0;
		break;
	}
	case DMFall:
	{
		if (vY == 0)
			vY = 10.0f;
		posY += vY * deltaTime;
		break;
	}
	case DMShot:
	{
		if (vY == 0)
			vY = 10.0f;
		posY += vY * deltaTime;
		break;
	}
	case DMRun:
	{
		if (vY == 0)
			vY = 10.0f;
		posY += vY * deltaTime;
		break;
	}
	case DMBarrelThrow:
	{
		if (vY == 0)
			vY = 10.0f;
		posY += vY * deltaTime;
		break;
	}
	case DMHurt:
	{
		if (vY == 0)
			vY = 10.0f;
		posY += vY * deltaTime;
		break;
	}
	case DMInjuredRun:
	{
		if (vY == 0)
			vY = 10.0f;
		posY += vY * deltaTime;
		break;
	}
	case DMInjuredStand:
	{
		if (vY == 0)
			vY = 10.0f;
		posY += vY * deltaTime;
		break;
	}
	case DMThrowWait:
	{
		if (vY == 0)
			vY = 10.0f;
		posY += vY * deltaTime;
		break;
	}

	default:

		break;
	}

	currentAnim->_isFlipHor = isReverse;
	currentAnim->Update(deltaTime);
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

//running man

RECT DynamiteNapalm::GetBound()
{
	RECT r;
	r.left = posX - width / 2;
	r.top = posY - height;
	r.right = r.left + width;
	r.bottom = r.top + height;
	return r;
}

BoundingBox DynamiteNapalm::GetBoundingBox()
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

