#include "Gigi.h"

#define DETECT_RANGE 150
#define SHOOTING_RANGE 150
#define FLYING_SPEED 5.0f

Gigi::Gigi(int level):Enemy()
{
	
}

Gigi::Gigi(float posX, float posY):Enemy(posX,posY,0,0)
{
	currHealth = maxHealth = 10;

	animations[GigiStand] = new Animation("Resources/enemy/Gigi/Gigi_Shooting.png", 1, 1, 1);
	animations[GigiShot] = new Animation("Resources/enemy/Gigi/Gigi_Shooting.png", 1, 1, 1);
	animations[GigiFly] = new Animation("Resources/enemy/Gigi/Gigi_Flying.png", 3, 1, 3, true, 1.0f);
	animations[GigiFlyStill] = new Animation("Resources/enemy/Gigi/Gigi_FlyStill.png", 3, 1, 3, true, 1.0f);
	animations[GigiSuprised] = new Animation("Resources/enemy/Gigi/Gigi_Suprised.png", 2, 1, 2, false, 1.5f);
	animations[GigiDie] = new Animation("Resources/enemy/Gigi/Gigi_Die.png", 2, 1, 2, true, 0.3f);

	currentState = GigiState::GigiStand;
	SetState(GigiState::GigiStand);
	
	savedvX = FLYING_SPEED * -1;
	isReverse = false;
	isWaiting = true;
	enemySubTag = EnemySubTag::GigiTag;
}
void Gigi::Update(float deltaTime)
{
	float currTime = GetTickCount();

	if (currHealth <= 0 && isDying == false)
	{
		isDying = true;
		SetState(GigiDie);
		StateTime = currTime;
	}

	switch (currentState)
	{
		case GigiStand:
		{
			if (CheckPosition() != 0 && isWaiting == true) //state dau, doi player di vao tam thi bat dau di chuyen
			{
				isWaiting = false;
				SetState(GigiSuprised);
				StateTime = currTime;
			}
			if (isWaiting == false && currTime - StateTime > 1000 && CheckPosition() == 2 && isAttacking == false)
			{
				SetState(GigiShot);
				StateTime = currTime;
			}
			else if (isWaiting == false && currTime - StateTime > 1000 && prevState == GigiShot)
			{
				SetState(GigiFly);
				savedvX *= -1;
				isReverse = !isReverse;
				StateTime = currTime;
				isAttacking = false;
			}
			break;
		}
		case GigiSuprised:
		{
			if (currTime - StateTime > 1000)
			{
				SetState(GigiFlyStill);
				StateTime = currTime;
			}
			break;
		}
		case GigiFlyStill:
		{
			if (currTime - StateTime > 1000)
			{
				SetState(GigiFly);
				savedvX *= -1;
				CheckReverse();
				StateTime = currTime;
			}
			break;
		}
		case GigiFly:
		{
			vX = savedvX;
			posX += vX * deltaTime;
			if (currTime - StateTime > 2500)
			{
				SetState(GigiStand);
				StateTime = currTime;
			}
			break;
		}
		case GigiShot:
		{
			if (currentAnim->_isFinished)
			{
				HomingMissile* temp = new HomingMissile(posX, posY, isReverse);
				GRID->AddObject(temp);
				missiles.push_back(temp);
				isAttacking = true;
			}
			vX = vY = 0.0f;
			if (currTime - StateTime > 1000 && isAttacking == true)
			{
				SetState(GigiStand);
				StateTime = currTime;
			}
			break;
		}
	}

	for (int i = 0; i < missiles.size(); i++)
	{
		missiles[i]->Update(deltaTime);
		if (missiles[i]->isDead)
		{
			GRID->RemoveObject(missiles[i]);
			missiles.erase(missiles.begin() + i);

		}
	}
	/*if (PLAYER->posX < posX)
	{
		isReverse = false;
	}
	else
	{
		isReverse = true;
	}*/
	currentAnim->_isFlipHor = isReverse;
	currentAnim->Update(deltaTime);
}

int Gigi::CheckPosition()
{
	if (abs(PLAYER->posX - posX) <= SHOOTING_RANGE && abs(PLAYER->posY - posY) <= SHOOTING_RANGE)
	{
		return 2;
	}
	if (abs(PLAYER->posX - posX) <= DETECT_RANGE && abs(PLAYER->posY - posY) <= DETECT_RANGE)
	{
		return 1;
	}
	return 0;
}

void Gigi::CheckReverse()
{
	if (PLAYER->posX < posX)
	{
		isReverse = false;
	}
	else
	{
		isReverse = true;
	}
}

void Gigi::OnCollision(GameObject * object, float deltaTime)
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
			vX = 0;
			isDead = true;
		}
	}
	auto colRes = COLLISION->SweptAABB(object->GetBoundingBox(), GetBoundingBox(), deltaTime);
	if (colRes.isCollide)
	{
		switch (object->tag)
		{
		case Captain:
		{
			if (PLAYER->currentState->GetState() == Kicking)
			{
				currHealth -= 10;
			}
			break;
		}
		default:
			break;
		}
	}
}

void Gigi::InsertFromFile(int level)
{
	std::unordered_set<GameObject*> rs;
	std::string filename = "Resources/enemy/gigi/lv" + std::to_string(level) + "_gigi.txt";
	std::ifstream file(filename);

	if (file.good())
	{
		while (!file.eof())
		{
			int x, y, t, c;
			file >> x;
			file >> y;
			GameObject* obj = new Gigi(x, y);
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

void Gigi::SetState(GigiState state)
{
	prevState = currentState;
	currentState = state;
	currentAnim = animations[state];
	currentAnim->ResetAnim();
	this->width = animations[state]->_frameWidth;
	this->height = animations[state]->_frameHeight;
}

void Gigi::Draw(D3DXVECTOR3 position, D3DXVECTOR3 cameraPosition, RECT sourceRect, D3DXVECTOR3 center)
{
	if (!isDead)
	{
		currentAnim->Draw(position, cameraPosition, sourceRect, center);
	}
}

void Gigi::Draw()
{
	if(!isDead)
		Draw(D3DXVECTOR3(posX, posY, 0), CAMERA->camPosition, RECT(), D3DXVECTOR3(width/2, height, 0));
}

Gigi::Gigi(RECT r) :Gigi(r.left, r.top)
{
}



RECT Gigi::GetBound()
{
	RECT r;
	r.left = posX - width / 2;
	r.top = posY - height;
	r.right = r.left + width;
	r.bottom = r.top + height;
	return r;
}

BoundingBox Gigi::GetBoundingBox()
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

void Gigi::Release()
{
}
