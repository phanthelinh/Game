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



	SetState(DMStand);
	isReverse = false;
	isDead = false;
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
	
}

void DynamiteNapalm::Update(float deltaTime)
{
	auto now = GetTickCount();

	currentAnim->_isFlipHor = isReverse;
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
