#include "Domesto.h"

Domesto::Domesto():Enemy()
{

}

Domesto::Domesto(float posX, float posY):Enemy(posX,posY,0,0)
{
	point = 500;//500 scores for player if he killed this object
	currHealth = maxHealth = 5; //attack five times
	anims[EnemyStateName::EnemyStand] = new Animation("Resources/enemy/domesto/domesto_stand_23_46.png", 1, 1, 1);
	currentAnim = anims[EnemyStateName::EnemyRun] = new Animation("Resources/enemy/domesto/domesto_run_46_46.png", 2, 1, 2,true,0.9);
	anims[EnemyStateName::EnemyJump] = anims[EnemyStateName::EnemySit] = new Animation("Resources/enemy/domesto/domesto_sit_24_31.png", 1, 1, 1);
	anims[EnemyStateName::EnemyDie] = new Animation("Resources/enemy/domesto/domesto_die_24_46.png", 1, 1, 1);
	currentState = EnemyStateName::EnemyRun;
	ChangeEnemyState(EnemyStateName::EnemyRun);
	startTime = 0;
	isReverse = true;
}

Domesto::Domesto(RECT r):Domesto(r.left,r.top)
{
}

void Domesto::ChangeEnemyState(EnemyStateName state)
{
	prevState = currentState;
	currentState = state;
	currentAnim = anims[state];
	currentAnim->ResetAnim();
	this->width = anims[state]->_frameWidth;
	this->height = anims[state]->_frameHeight;
}

void Domesto::OnCollision(GameObject * object, float deltaTime)
{
}

void Domesto::Update(float deltaTime)
{
	isReverse = posX <= PLAYER->posX;
	currentAnim->_isFlipHor = isReverse;
	//running for 2 seconds
	auto now = GetTickCount();
	if (startTime == 0)
	{
		startTime = now;
	}
	switch (currentState)
	{
	case EnemyStand:
		vX = 0;
		if ((now - startTime) / 1000.0f >= 1.0f)
		{
			//attack
			startTime = now;
			EXPLODE->ExplodeAt(20, 300);
			ChangeEnemyState(EnemySit);
		}
		break;
	case EnemyRun:
		vX = 4.0f * (isReverse ? 1.0f : -1.0f);
		posX += vX * deltaTime;
		posY += vY * deltaTime;
		now = GetTickCount();
		if ((now - startTime) / 1000.0f >= 2.0f)
		{
			startTime = now;
			ChangeEnemyState(EnemyStand);
		}
		break;
	case EnemySit:
		vX = 0;
		now = GetTickCount();
		if ((now - startTime) / 1000.0f >= 1.0f)
		{
			//attack
			startTime = now;
			EXPLODE->ExplodeAt(20, 300);
			ChangeEnemyState(EnemyStand);
		}
		break;
	case EnemyAttack:
		//attack and change to preState
		ChangeEnemyState(prevState);
		break;
	case EnemyDie:
		break;
	case EnemyJump:
		break;
	default:
		break;
	}
	currentAnim->Update(deltaTime);
	EXPLODE->Update(deltaTime);
}

void Domesto::Draw(D3DXVECTOR3 position, D3DXVECTOR3 cameraPosition, RECT sourceRect, D3DXVECTOR3 center)
{
	if (!isDead)
	{
		currentAnim->Draw(position, cameraPosition, sourceRect, center);
		EXPLODE->Draw();
	}
}

void Domesto::Draw()
{
	if(!isDead)
		Draw(D3DXVECTOR3(posX, posY, 0), CAMERA->camPosition, RECT(), D3DXVECTOR3(width/2, height, 0));
}

RECT Domesto::GetBound()
{
	RECT r;
	r.left = posX - width / 2;
	r.top = posY - height;
	r.right = r.left + width;
	r.bottom = r.top + height;
	return r;
}

BoundingBox Domesto::GetBoundingBox()
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

void Domesto::Release()
{
}
