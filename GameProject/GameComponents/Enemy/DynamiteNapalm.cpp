#include "DynamiteNapalm.h"
#include "../Ground.h"
#include "../Effect/Explode.h"

#define RUN_SPEED 8.0f
#define STATE_DELAY_TIME 1500.0f
#define RUN_TIME 1800.0f
#define SHOT_DELAY_TIME 600.0f
#define DIE_STAY_TIME 3000.0f

DynamiteNapalm::DynamiteNapalm() :Enemy()
{
}

DynamiteNapalm::DynamiteNapalm(float posX, float posY) :Enemy(posX, posY, 0, 0)
{
	point = 1000;	//score when kill this boss
	currHealth = maxHealth = 18;

	animations[DMBarrelThrow] = new Animation("Resources/enemy/Dynamite Napalm/DMBarrelThrow.png", 2, 1, 2, false, 0.7f);
	animations[DMHurt] = new Animation("Resources/enemy/Dynamite Napalm/DMHurt.png", 2, 1, 2, true, 1.5f);
	animations[DMInjuredRun] = new Animation("Resources/enemy/Dynamite Napalm/DMInjuredRun.png", 3, 1, 3, true, 1.0f);
	animations[DMInjuredStand] = new Animation("Resources/enemy/Dynamite Napalm/DMInjuredStand.png", 1, 1, 1);
	animations[DMRun] = new Animation("Resources/enemy/Dynamite Napalm/DMRun.png", 3, 1, 3, true, 1.5f);
	animations[DMShot] = new Animation("Resources/enemy/Dynamite Napalm/DMShot.png", 2, 1, 2, false, 1.5f);
	animations[DMStand] = new Animation("Resources/enemy/Dynamite Napalm/DMStand.png", 1, 1, 1);
	animations[DMFall] = new Animation("Resources/enemy/Dynamite Napalm/DMStand.png", 1, 1, 1);
	animations[DMThrowWait] = new Animation("Resources/enemy/Dynamite Napalm/DMThrowWait.png", 1, 1, 1, false, 0.5f);
	animations[DMDie] = new Animation("Resources/enemy/Dynamite Napalm/DMInjuredStand.png", 1, 1, 1);

	currentState = DMFall;
	SetState(DMFall);
	isReverse = false;
	isDead = false;
	isOnGround = false;
	tag = EnemyTag;
	enemySubTag = EnemySubTag::DMBossTag;

	dmbarrel = new DMBarrel(posX, posY, isReverse);
	dmbarrel->isVisible = false;
	GRID->AddObject(dmbarrel);
}

DynamiteNapalm::DynamiteNapalm(RECT r) :Enemy(r)
{
	enemySubTag = EnemySubTag::DMBossTag;
	maxHealth = 50;
}

void DynamiteNapalm::ChangeState(DMState state)
{
	SetState(state);
	StateTime = GetTickCount();
}

bool DynamiteNapalm::CheckStateTime(float offset, float compared)
{
	float currTime = GetTickCount();
	if (currTime - StateTime + offset > compared)
		return true;
	return false;
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


void DynamiteNapalm::Update(float deltaTime)
{
	float currTime = GetTickCount();
	switch (currentState)
	{
		case DMFall:
		{
			if (vY == 0)
				vY = 10.0f;
			posY += vY * deltaTime;
			break;
		}
		case DMStand:
		{
			if (prevState == DMFall || (CheckStateTime(0, 800) && StateTime != 0))
			{
				ChangeState(DMThrowWait);
			}
			break;
		}
		case DMThrowWait:
		{
			if (waitfornextshot == false)
			{
				float x = (isReverse) ? 10 : -10;
				dmbarrel->StartWait(posX + x, posY - 60, isReverse);
				waitfornextshot = true;
			}
			if (CheckStateTime(0, STATE_DELAY_TIME))
			{
				ChangeState(DMBarrelThrow);
				waitfornextshot = false;
			}
			break;
		}
		case DMBarrelThrow:
		{
			if (currentAnim->_isFinished && waitfornextshot == false)
			{
				dmbarrel->StartFall();
				waitfornextshot = true;
			}
			if (CheckStateTime(0, 800))
			{
				ChangeState(DMShot);
				waitfornextshot = false;
			}
			break;
		}
		case DMShot:
		{
			if (shotcount == 2 && CheckStateTime(-200.0f, STATE_DELAY_TIME))
			{
				ChangeState(DMRun);
				shotcount = 0;
				waitfornextshot = false;
			}
			if (currentAnim->_isFinished && waitfornextshot == false)
			{
				float x = (isReverse) ? 30 : -30;
				DMBullet* dmbllet = new DMBullet(posX + x, posY - 38, isReverse);
				GRID->AddObject(dmbllet);
				dmbullet.push_back(dmbllet);
				waitfornextshot = true;
				shotcount++;
			}
			if (CheckStateTime(-200.0f, STATE_DELAY_TIME)) //kiem tra de ban lan tiep theo
			{
				ChangeState(DMShot);
				waitfornextshot = false;
			}
			break;
		}
		case DMRun:
		{
			vX = (!isReverse) ? RUN_SPEED * -1 : RUN_SPEED;
			posX += vX * deltaTime;
			if (CheckStateTime(0, RUN_TIME))
			{
				ChangeState(DMStand);
				isReverse = !isReverse;
			}
			break;
		}
		case DMHurt:
		{
			dmbarrel->isVisible = false;
			waitfornextshot = false;
			if (CheckStateTime(0, STATE_DELAY_TIME))
			{
				ChangeState(DMRun);
			}
			break;
		}
		case DMInjuredStand:
		{
			dmbarrel->isVisible = false;
			if (CheckStateTime(0, STATE_DELAY_TIME))
			{
				ChangeState(DMInjuredRun);
				shotcount = 0;
			}
			break;
		}
		case DMInjuredRun:
		{
			vX = (!isReverse) ? RUN_SPEED * -1 : RUN_SPEED;
			posX += vX * deltaTime;
			if (LastShotTime == 0 || currTime - LastShotTime > SHOT_DELAY_TIME)
			{
				float x = (isReverse) ? 30 : -30;
				DMBullet* dmbllet = new DMBullet(posX + x, posY - 38, isReverse, 2);
				GRID->AddObject(dmbllet);
				dmbullet.push_back(dmbllet);
				shotcount++;
				LastShotTime = currTime;
			}
			if (CheckStateTime(0, RUN_TIME))
			{
				ChangeState(DMInjuredStand);
				isReverse = !isReverse;
				shotcount = 0;
				LastShotTime = 0.0f;
			}
			break;
		}
		case DMDie:
		{
			isReverse = !isReverse;
			if (CheckStateTime(0, DIE_STAY_TIME) && isDead != true)
			{
				isDead = true;
				SOUND->play("bossdie");
				EXPLODE->ExplodeAt(posX, posY - 30);
			}
		}
	}

	for (int i = 0; i < dmbullet.size(); i++)
	{
		dmbullet[i]->Update(deltaTime);
		if (dmbullet[i]->isDead)
		{
			GRID->RemoveObject(dmbullet[i]);
			dmbullet.erase(dmbullet.begin() + i);

		}
	}

	if (dmbarrel != nullptr)
	{
		dmbarrel->Update(deltaTime);
		if (dmbarrel->isDead)
		{
			GRID->RemoveObject(dmbarrel);

		}
	}

	currentAnim->_isFlipHor = isReverse;
	currentAnim->Update(deltaTime);
}

void DynamiteNapalm::OnCollision(GameObject* object, float deltaTime)
{
	if (object->tag == Tag::Captain)
	{
		auto colRes = COLLISION->SweptAABB(GetBoundingBox(), object->GetBoundingBox(), deltaTime);
		if (colRes.isCollide && PLAYER->isImmu == false)
		{
			PLAYER->health -= 2;
			if (PLAYER->health <= 0)
				PLAYER->ChangeState(Die);
			else
				PLAYER->ChangeState(Hurt);
		}
	}

	auto colRes = COLLISION->SweptAABB(object->GetBoundingBox(), GetBoundingBox(), deltaTime);
	if (colRes.isCollide && object->tag == ShieldTag)
	{
		currHealth -= 3;
		if (currHealth <= 0)
		{
			ChangeState(DMDie);
		}
	}

	std::vector<GameObject*> grounds = GRID->GetVisibleGround();
	CollisionResult res;
	for (auto g : grounds)
	{
		BoundingBox temp = GetBoundingBox();
		res = COLLISION->SweptAABB(temp, g->GetBoundingBox(), deltaTime);
		if (res.isCollide && res.sideCollided == Bottom && isOnGround == false)
		{
			isOnGround = true;
			posY += vY * res.entryTime;
			vY = 0;
			ChangeState(DMStand);
		}
	}
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
	if (currentAnim != NULL)
		delete currentAnim;
}

DMState DynamiteNapalm::GetState()
{
	if (currentState == NULL)
		currentState = DMStand;
	return currentState;
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

