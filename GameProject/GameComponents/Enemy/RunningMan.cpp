#include "RunningMan.h"

#define RUNNING_RANGE 150
#define SHOOTING_RANGE 100
#define SIT_RANGE 100

RunningMan::RunningMan(int level):Enemy()
{
	
}

RunningMan::RunningMan(float posX, float posY, int type, int color):Enemy(posX,posY,0,0)
{
	this->type = type;
	this->color = color;
	if (color == 0)
	{
		animations[EnemyStateName::EnemyStand] = new Animation("Resources/enemy/runningman/RunningMan_Stand.png", 1, 1, 1);
		animations[EnemyStateName::EnemyJump] = animations[EnemyStateName::EnemySit] = new Animation("Resources/enemy/runningman/RunningMan_Sit.png", 1, 1, 1);
		animations[EnemyStateName::EnemyDie] = new Animation("Resources/enemy/runningman/RunningMan_Die.png", 1, 1, 1, false);
		animations[EnemyStateName::EnemyRun] = new Animation("Resources/enemy/runningman/RunningMan_Run.png", 3, 1, 3, true, 0.5f);
	}
	else
	{
		animations[EnemyStateName::EnemyStand] = new Animation("Resources/enemy/runningman/GreenRunningMan_Stand.png", 1, 1, 1);
		animations[EnemyStateName::EnemyJump] = animations[EnemyStateName::EnemySit] = new Animation("Resources/enemy/runningman/GreenRunningMan_Sit.png", 1, 1, 1);
		animations[EnemyStateName::EnemyDie] = new Animation("Resources/enemy/runningman/GreenRunningMan_Die.png", 1, 1, 1);
		animations[EnemyStateName::EnemyRun] = new Animation("Resources/enemy/runningman/GreenRunningMan_Run.png", 3, 1, 3, true, 0.5f);
	}

	currHealth = maxHealth = 10;
	if (type == 0)
	{
		currentState = EnemyStateName::EnemyStand;
		SetState(EnemyStateName::EnemyStand);
	}
	else
	{
		currentState = EnemyStateName::EnemySit;
		SetState(EnemyStateName::EnemySit);
	}
	isReverse = false;
	isWaiting = true;
	enemySubTag = EnemySubTag::RunningManTag;
}

RunningMan::RunningMan(RECT r):RunningMan(r.left,r.top)
{
}

void RunningMan::InsertFromFile(int level)
{
	std::unordered_set<GameObject*> rs;
	std::ifstream file;
	if (level == 1)
	{
		file.open("Resources/enemy/runningman/runningmanlevel1.txt");
	}
	//insert to grid
	
	if (file.good())
	{
		while (!file.eof())
		{
			int x, y, t, c;
			file >> x;
			file >> y;
			file >> t;
			file >> c;
			GameObject* obj = new RunningMan(x, y, t, c);
			if (obj)
			{
				rs.insert(obj);
			}
		}
		file.close();
	}
	if (rs.size() > 0)
		GRID->InsertToGrid(rs);
	rs.clear();
}

void RunningMan::SetState(EnemyStateName state)
{
	prevState = currentState;
	currentState = state;
	currentAnim = animations[state];
	currentAnim->ResetAnim();
	this->width = animations[state]->_frameWidth;
	this->height = animations[state]->_frameHeight;
}


void RunningMan::Update(float deltaTime)
{
	float currTime = GetTickCount();

	if (currHealth <= 0 && isDying == false)
	{
		SetState(EnemyStateName::EnemyDie);
	}
	switch (currentState)
	{
		case EnemyStand:
		{
			if (isWaiting == true && CheckPosition() == 1) //player vao tam thi chay toi
			{
				isWaiting = false;
				SetState(EnemyStateName::EnemyRun);
			}
			if (isAttacking == true && CheckPosition() == 1) //player ra khoi tam thi duoi theo
			{
				isAttacking = false;
				SetState(EnemyStateName::EnemyRun);
			}
			if (isAttacking == true && CheckPosition() == 0) //trong tam thi ban
			{
				if (currTime - LastShotTime >= 1200.0f)
				{
					LastShotTime = currTime;
					Bullet* bull = new Bullet(posX, posY - 35, (PLAYER->posX - posX > 0) ? 1 : -1);
					GRID->AddObject(bull);
					bullets.push_back(bull);
				}
			}
			break;
		}
		case EnemyRun:
		{
			vX = (isReverse == false) ? -8.0f : 8.0f;
			posX += vX * deltaTime;
			posY += vY * deltaTime;
			if (CheckPosition() == 0)
			{
				isAttacking = true;
				SetState(EnemyStateName::EnemyStand);
			}
			break;
		}
		case EnemyDie:
		{
			if (isDying == false) //vong lap dau tien khi running man moi chet
			{
				if (isReverse == true)
				{
					vX = -5.0f;
					vY = -5.0f;
				}
				else
				{
					vX = 5.0f;
					vY = 5.0f;
				}
				posX += vX * deltaTime;
				posY += vY * deltaTime;
				EXPLODE->ExplodeAt(posX - 8, posY - 24);
				DeadStartTime = GetTickCount();
				isDying = true;
			}
			else
			{
				if (currTime - DeadStartTime >= 200.0f && DeadStartTime != 0.0f)
				{
					isDead = true;
				}
			}
			break;
		}
		case EnemySit:
		{
			if (isAttacking == true)
			{
				if (currTime - LastShotTime >= 1200.0f)
				{
					LastShotTime = currTime;
					Bullet* bull = new Bullet(posX, posY - 20, (PLAYER->posX - posX > 0) ? 1 : -1);
					GRID->AddObject(bull);
					bullets.push_back(bull);
				}
			}
			if (CheckPosition() == 2)
			{
				isWaiting = false;
				isAttacking = true;
			}
			break;
		}
	}

	for (int i = 0; i < bullets.size(); i++)
	{
		bullets[i]->Update(deltaTime);
		if (bullets[i]->isDead)
		{
			GRID->RemoveObject(bullets[i]);
			bullets.erase(bullets.begin() + i);

		}
	}
	if (PLAYER->posX < posX)
	{
		isReverse = false;
	}
	else
	{
		isReverse = true;
	}
	currentAnim->_isFlipHor = isReverse;
	currentAnim->Update(deltaTime);
}

int RunningMan::CheckPosition()
{
	float distance = abs(PLAYER->posX - posX);
	if (distance <= RUNNING_RANGE && distance > SHOOTING_RANGE)
	{
		return 1;
	}
	if (distance <= SHOOTING_RANGE && currentState != EnemyStateName::EnemySit)
	{
		return 0;
	}
	if (distance <= SIT_RANGE && currentState == EnemyStateName::EnemySit)
	{
		return 2;
	}
	return -1;
}

void RunningMan::Draw(D3DXVECTOR3 position, D3DXVECTOR3 cameraPosition, RECT sourceRect, D3DXVECTOR3 center)
{
	if (!isDead)
	{
		currentAnim->Draw(position, cameraPosition, sourceRect, center);
	}
}

void RunningMan::OnCollision(GameObject * object, float deltaTime)
{
	auto grounds = GRID->GetVisibleGround();
	for (auto g : grounds)
	{
		auto colRes = COLLISION->SweptAABB(GetBoundingBox(), g->GetBoundingBox(), deltaTime);
		if (colRes.isCollide)
		{
			posX += vX * colRes.entryTime;
			posY += vY * colRes.entryTime;
			vY = 0;
			SetState(EnemyStateName::EnemyStand);
		}
	}
	auto colRes = COLLISION->SweptAABB(object->GetBoundingBox(), GetBoundingBox(), deltaTime);
	if (colRes.isCollide)
	{
		switch (object->tag)
		{
		case Tag::ShieldTag:
			if (PLAYER->shieldFlying)
			{
				currHealth -= 10;
			}
			else
			{
				vX = vY = 0;
				currHealth = 0;
				SetState(EnemyStateName::EnemyDie);
			}
			break;
		default:
			break;
		}
	}
}

void RunningMan::Draw()
{
	if(!isDead)
		Draw(D3DXVECTOR3(posX, posY, 0), CAMERA->camPosition, RECT(), D3DXVECTOR3(width/2, height, 0));
}

RECT RunningMan::GetBound()
{
	RECT r;
	r.left = posX - width / 2;
	r.top = posY - height;
	r.right = r.left + width;
	r.bottom = r.top + height;
	return r;
}

BoundingBox RunningMan::GetBoundingBox()
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

void RunningMan::Release()
{
}
