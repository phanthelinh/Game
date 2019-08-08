#include "Tank.h"

TankState Tank::GetStateNameFromNumber(int num)
{
	switch (num)
	{
	case 0:
		return TankStateBottom;
	case 1:
		return TankStateRightBottom;
	case 2:
		return TankStateRight;
	case 3:
		return TankStateRightTop;
	case 4:
		return TankStateTop;
	case 5:
		return TankStateLeftTop;
	case 6:
		return TankStateLeft;
	default:
		return TankStateLeftBottom;
	}
}

Tank::Tank(float x, float y, int type) :Enemy(x, y, 0, 0)
{
	initState = type;
	width = height = 8;
	enemySubTag = TankTag;
	for (int i = 0; i < 8; i++)
	{
		sprites[GetStateNameFromNumber(i)] = new Sprite("Resources/enemy/tank/tank_128_16.png", { i * 16,0,i * 16 + 16,16 });
	}
	currentAnim = new Animation("Resources/enemy/tank/tank_128_16.png", 8, 1, 8, false, 0.2);
	curNumSprite = type;
	curSprite = sprites[GetStateNameFromNumber(curNumSprite)];
	currHealth = maxHealth = 4;
	point = 50;
}

void Tank::InsertFromFile(int level)
{
	std::unordered_set<GameObject*> rs;
	std::string filename = "Resources/enemy/tank/lv" + std::to_string(level) + "_tank.txt";
	std::ifstream file(filename);
	if (file.good())
	{
		while (!file.eof())
		{
			int x, y,t;
			file >> x >> y >> t;
			GameObject* obj = new Tank(x - 4, y - 4, t);
			if (t != NULL)
				rs.insert(obj);
		}
		file.close();
	}
	if (rs.size() > 0)
	{
		GRID->InsertToGrid(rs);
		rs.clear();
	}
}

void Tank::ChangeTankState()
{
	curNumSprite = (curNumSprite + 1) % 8;
	curSprite = sprites[GetStateNameFromNumber(curNumSprite)];
}

void Tank::OnCollision(GameObject * object, float deltaTime)
{
	if (object->tag == ShieldTag)
	{
		auto res = COLLISION->SweptAABB(object->GetBoundingBox(), GetBoundingBox(), deltaTime);
		if (res.isCollide)
		{
			onChangingState = true;
		}
	}
}

void Tank::Update(float deltaTime)
{
	if (isDead)
		return;
	if (currHealth <= 0)
	{
		SOUND->play("enemydie");
		EXPLODE->ExplodeAt(D3DXVECTOR3(posX, posY, 0));
		PLAYER->scores += point;
		isDead = true;
	}
	if (onChangingState)
	{
		currentAnim->Update(deltaTime);
		if (currentAnim->_isFinished)
		{
			ChangeTankState();
			onChangingState = false;
			currentAnim->ResetAnim();
			timeCount = GetTickCount();
			currHealth -= PLAYER->shield->shieldPower;
		}
	}
	else
	{
		timeCount = timeCount == 0 ? GetTickCount() : timeCount;
		auto now = GetTickCount();
		if ((now - timeCount) / 1000.0f >= 2.0f)
		{
			Bullet* bu = NULL;
			switch (curNumSprite)
			{
			case 0://bottom
				bu = new Bullet(posX + 5, posY + 8, 0);
				bu->vX = 0;
				bu->vY = BULLET_SPEED;
				break;
			case 1://right bottom
				bu = new Bullet(posX + 8, posY + 8, 0);
				bu->vY = bu->vX = BULLET_SPEED;
				break;
			case 2://right
				bu = new Bullet(posX + 8, posY + 5, 1);
				break;
			case 3://right top
				bu = new Bullet(posX + 12, posY - 3, 0);
				bu->vX = BULLET_SPEED;
				bu->vY = -BULLET_SPEED;
				break;
			case 4://top
				bu = new Bullet(posX + 5, posY - 8, 0);
				bu->vX = 0;
				bu->vY = -BULLET_SPEED;
				break;
			case 5: //left top
				bu = new Bullet(posX - 1, posY - 1, 0);
				bu->vX = bu->vY = -BULLET_SPEED;
				break;
			case 6://left
				bu = new Bullet(posX - 3, posY + 5, -1);
				break;
			case 7://left bottom
				bu = new Bullet(posX - 1, posY + 12, 0);
				bu->vX = -BULLET_SPEED;
				bu->vY = BULLET_SPEED;
				break;
			default:
				break;
			}
			if (bu != NULL)
			{
				bullets.push_back(bu);
				GRID->AddObject(bu);
			}
			timeCount = now;
		}
	}
	//check for bullets is dead
	for (int i = 0;i <bullets.size();i++)
	{
		auto obj = bullets.begin() + i;
		if ((*obj)->isDead)
		{
			//GRID->RemoveObject(*obj);
			bullets.erase(obj);
		}
	}
}

void Tank::Draw(D3DXVECTOR3 position, D3DXVECTOR3 cameraPosition, RECT sourceRect, D3DXVECTOR3 center)
{
	if (!isDead)
	{
		if (onChangingState)
			currentAnim->Draw(position + D3DXVECTOR3(16,0,0), cameraPosition, sourceRect, D3DXVECTOR3(0, 0, 0));
		else
			curSprite->Draw(position, cameraPosition, sourceRect, D3DXVECTOR3(0, 0, 0));
	}
}

void Tank::Draw()
{
	if (!isDead)
		Draw(D3DXVECTOR3(posX, posY, 0), CAMERA->camPosition, RECT(), D3DXVECTOR3(0, 0, 0));
}

RECT Tank::GetBound()
{
	RECT r;
	r.left = posX;
	r.top = posY;
	r.right = r.left + width;
	r.bottom = r.top + height;
	return r;
}

BoundingBox Tank::GetBoundingBox()
{
	BoundingBox r;
	r.left = posX;
	r.top = posY;
	r.right = r.left + width;
	r.bottom = r.top + height;
	r.vX = r.vY = 0;
	return r;
}

void Tank::Release()
{
	for (int i = 0; i < bullets.size(); i++)
		bullets.erase(bullets.begin() + i);
	bullets.clear();
	sprites.clear();
}
