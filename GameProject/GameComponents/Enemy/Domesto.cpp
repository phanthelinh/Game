#include "Domesto.h"
#define MAX_DISTANCE_START_TO_JUMP_PLAYER	50.0f
#define MAX_DISTANCE_RUNNING				50.0f

Domesto::Domesto(int level)
{
	
}

Domesto::Domesto(float x, float y) : Enemy(x, y, 0, 0)
{
	point = 400;//400 scores for player if he killed this object
	currHealth = maxHealth = 30; //attack five times
	anims[EnemyStateName::EnemyStand] = new Animation("Resources/enemy/domesto/domesto_stand_23_46.png", 1, 1, 1);
	currentAnim = anims[EnemyStateName::EnemyRun] = new Animation("Resources/enemy/domesto/domesto_run_46_46.png", 2, 1, 2, true, 0.8f);
	anims[EnemyStateName::EnemyJump] = anims[EnemyStateName::EnemySit] = new Animation("Resources/enemy/domesto/domesto_sit_24_31.png", 1, 1, 1);
	anims[EnemyStateName::EnemyDie] = new Animation("Resources/enemy/domesto/domesto_die_24_46.png", 1, 1, 1);
	currentState = EnemyStateName::EnemyRun;
	ChangeEnemyState(EnemyStateName::EnemyRun);
	startTime = 0;
	isReverse = true;
	isPauseMissile = false;
	enemySubTag = EnemySubTag::DomestoTag;
}

Domesto::Domesto(float posX, float posY, EnemyDomestoType type) :Domesto(posX, posY)
{
	this->domestoType = type;
}

void Domesto::InsertFromFile(int level)
{
	std::unordered_set<GameObject*> rs;
	std::string filename = "Resources/enemy/domesto/lv" + std::to_string(level) + "_domesto.txt";
	std::ifstream file(filename);
	//insert to grid
	
	if (file.good())
	{
		while (!file.eof())
		{
			int x, y, t;
			file >> x;
			file >> y;
			file >> t;
			GameObject* obj = NULL;
			if (t == 0)
			{
				obj = new Domesto(x, y + 50, EnemyDomestoType::DomestoRunning);
			}
			else
			{
				obj = new Domesto(x, y, EnemyDomestoType::DomestoJumping);
			}
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
	//check collision with ground
	auto grounds = GRID->GetVisibleGround();
	for (auto g : grounds)
	{
		auto colRes = COLLISION->SweptAABB(GetBoundingBox(), g->GetBoundingBox(), deltaTime);
		if (colRes.isCollide)
		{
			posX += vX * colRes.entryTime;
			posY += vY * colRes.entryTime;
			vY = 0;
			ChangeEnemyState(EnemyStateName::EnemyStand);
		}
	}
	auto colRes = COLLISION->SweptAABB(object->GetBoundingBox(), GetBoundingBox(), deltaTime);
	if (colRes.isCollide)
	{
		switch (object->tag)
		{
		case Captain:
		{
			if (PLAYER->currentState->GetState() == Dashing)
			{
				currHealth -= 30;
			}
			break;
		}
		case Tag::ShieldTag:
			if (PLAYER->shieldFlying)
			{
				currHealth -= PLAYER->shield->shieldPower;
			}
			else
			{
				vX = vY = 0;
				currHealth = 0;
				PLAYER->scores += point;
				ChangeEnemyState(EnemyStateName::EnemyDie);
			}
			break;
		default:
			break;
		}
	}
}

void Domesto::Update(float deltaTime)
{
	auto now = GetTickCount();
	isReverse = posX <= PLAYER->posX;
	currentAnim->_isFlipHor = false;
	if (isStopUpdate)
	{
		if ((now - startTime)/1000.0f >= 0.5f)
		{
			isDead = true;
			startTime = 0;
		}
		return;
	}
	//currHealth--;
	if (currHealth <= 0)
		ChangeEnemyState(EnemyDie);
	currentAnim->Update(deltaTime);
	//
	//Update missiles
	//
	if (!isPauseMissile)
	{
		for (int i = 0; i < missles.size(); ++i)
		{
			if (missles[i]->isDead)
			{
				GRID->RemoveObject(missles[i]);
				missles.erase(missles.begin() + i);
				
			}
		}
	}
	//
	//Domesto update
	//
	
	Missile* mis = NULL;
	if (startTime == 0)
	{
		startTime = now;
	}
	switch (currentState)
	{
	case EnemyStand:
		isPauseMissile = false;
		vX = 0;
		if ((now - startTime) / 1000.0f >= 2.0f)
		{
			//attack
			startTime = now;
			if (domestoType == EnemyDomestoType::DomestoRunning)
			{
				mis = new Missile(posX, posY - 30, MissileType::StraightMissile);
			}
			else
			{
				mis = new Missile(posX, posY - 30, MissileType::StraightUpwardMissile);
			}
			mis->isReverse = isReverse;
			missles.push_back(mis);
			ChangeEnemyState(EnemySit);
		}
		break;
	case EnemyRun:
		isPauseMissile = true;
		vX = 3.0f * (isReverse ? 1.0f : -1.0f);
		posX += vX * deltaTime;
		posY += vY * deltaTime;
		if (abs(posX-PLAYER->posX)>= MAX_DISTANCE_RUNNING)
		{
			if (this->domestoType == EnemyDomestoType::DomestoRunning)
			{
				mis = new Missile(posX, posY - height + 5, MissileType::StraightMissile);
				mis->isReverse = isReverse;
				missles.push_back(mis);
				ChangeEnemyState(EnemyStand);
			}
			else
			{
				vY = -28.0f;
				ChangeEnemyState(EnemyJump);
			}
		}
		break;
	case EnemySit:
		isPauseMissile = false;
		vX = 0;
		if ((now - startTime) / 1000.0f >= 2.0f)
		{
			//attack
			startTime = now;
			mis = new Missile(posX, posY - 40, MissileType::StraightMissile);
			mis->isReverse = isReverse;
			missles.push_back(mis);
			ChangeEnemyState(EnemyStand);
		}
		break;
	case EnemyDie:
		isPauseMissile = true;
		if (currHealth <= 0)
		{
			//bounce behind
			if (isReverse) //face to right
			{
				//bounce to left
				vX = -10.0f;
				vY = -10.0f;
			}
			else
			{
				//bounce to right
				vX = 10.0f;
				vY = -10.0f;
			}
			posX += vX * deltaTime;
			posY += vY * deltaTime;
			//explode
			SOUND->play("enemydie");
			EXPLODE->ExplodeAt(posX-8, posY-24);
			startTime = now;
			isStopUpdate = true;
		}
		break;
	case EnemyJump:
		isPauseMissile = true;
		vY = vY + 2 > 28.0f ? 8.0f : vY + 2;
		vX = 5.0f*(isReverse ? 1.0f : -1.0f);
		posX += vX * deltaTime;
		posY += vY * deltaTime;
		break;
	default:
		break;
	}
	//add to grid
	if (mis != NULL)
	{
		GRID->AddObject(mis);
	}
}

void Domesto::Draw(D3DXVECTOR3 position, D3DXVECTOR3 cameraPosition, RECT sourceRect, D3DXVECTOR3 center)
{
	if (!isDead)
	{
		currentAnim->Draw(position, cameraPosition, sourceRect, center);
		if (!isPauseMissile)
		{
			for (auto m : missles)
			{
				m->Draw();
			}
		}
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
