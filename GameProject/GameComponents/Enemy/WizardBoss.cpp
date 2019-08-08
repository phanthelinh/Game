#include "WizardBoss.h"
#include "../Ground.h"
#define NUM_OF_HORIZONTAL_BULLET 3
#define NUM_OF_VERTICAL_BULLET 1

WizardBoss::WizardBoss() :Enemy()
{
	enemySubTag = EnemySubTag::WizardBossTag;
	maxHealth = 14;
}

WizardBoss::WizardBoss(float posX, float posY) :Enemy(posX, posY, 0, 0)
{
	point = 500;	//score when kill this boss
	currHealth = maxHealth = 14;
	animations[StandingWizard] = new Animation("Resources/boss/Wizard_Standing.png", 2, 1, 2, false);
	currentAnim = animations[FlyingWizard] = new Animation("Resources/boss/Wizard_Flying.png", 1, 1, 1);
	animations[RunningWizard] = new Animation("Resources/boss/Wizard_Running.png", 3, 1, 3, true, 0.09);
	animations[DieWizard] = new Animation("Resources/boss/Wizard_Die.png", 2, 1, 2);
	animations[AttackingWizard] = new Animation("Resources/boss/Wizard_Attacking.png", 4, 1, 4, true, 0.9);
	animations[FlyAttackWizard] = new Animation("Resources/boss/Wizard_FlyAttack.png", 3, 1, 3, false, 0.07);
	animations[InjuringWizard] = new Animation("Resources/boss/Wizard_Injuring.png", 1, 1, 1,false);
	currentState = FlyingWizard;
	ChangeEnemyState(FlyingWizard);
	isReverse = false;
	isDead = PLAYER->isBossKilled = false;
	isOnGround = false; //falling down
	nHorizontalBullet = NUM_OF_HORIZONTAL_BULLET;
	nVerticalBullet = NUM_OF_VERTICAL_BULLET;
	enemySubTag = EnemySubTag::WizardBossTag;
}

WizardBoss::WizardBoss(RECT r) :Enemy(r)
{
	enemySubTag = EnemySubTag::WizardBossTag;
	maxHealth = 14;
}

void WizardBoss::ChangeEnemyState(WizardState state)
{
	
	prevState = currentState;
	currentState = state;
	currentAnim = animations[state];
	currentAnim->ResetAnim();
	this->width = animations[state]->_frameWidth;
	this->height = animations[state]->_frameHeight;
}

void WizardBoss::OnCollision(GameObject* object, float deltaTime)
{
	std::vector<GameObject*> grounds = GRID->GetVisibleGround();
	CollisionResult res;
	for (auto g: grounds)
	{
		res = COLLISION->SweptAABB(this->GetBoundingBox(), g->GetBoundingBox(), deltaTime);
		if (res.isCollide && res.sideCollided == Bottom)
		{
			switch (currentState)
			{
			case FlyAttackWizard:
				break;
			case FlyingWizard:
				isOnGround = true;
				startTime = GetTickCount();
				ChangeEnemyState(StandingWizard);
				
				break;
			}
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
				currHealth -= 10;
			}
			break;
		}
		case Tag::ShieldTag:
			if (PLAYER->shieldFlying)
			{
				currHealth -= PLAYER->shield->shieldPower;
				ChangeEnemyState(InjuringWizard);
			}
			break;
		default:
			break;
		}
	}
}

void WizardBoss::Update(float deltaTime)
{
	auto now = GetTickCount();
	currentAnim->_isFlipHor = isReverse;
	
	if (currHealth <= 0)
	{
		ChangeEnemyState(DieWizard);
	}
	currentAnim->Update(deltaTime);
	WizardBullet* bul = NULL;
	if (startTime == 0)
	{
		startTime = now;
	}

	switch (currentState)
	{
	case FlyingWizard:
	{
		vX = 0;
		vY = isOnGround ? -15.0f : 15.0f;
		posY += vY * deltaTime;
		
		if (isOnGround && posY + height <= 140)	//is flying up and touch camera.top, then fly horizontally and attack
		{
			vY = 0;
			ChangeEnemyState(FlyAttackWizard);
			isOnGround = false;
		}
		break;
	}
	case StandingWizard:
	{
		vX = vY = 0;

		//run toward player and shoot
		if ((now - startTime) / 1000.0f >= 1.0f)
		{
			startTime = now;
			nVerticalBullet = NUM_OF_VERTICAL_BULLET;
			if (posY < 98)	//is standing on small ground
			{
				isReverse = !isReverse;
				ChangeEnemyState(FlyingWizard);
				break;
			}

			ChangeEnemyState(RunningWizard);
		}
		break;
	}
	case RunningWizard:
	{
		vX = (isReverse == false) ? -15.0f : 15.0f;
		posX += vX * deltaTime;
		if (abs(PLAYER->posX - posX) <= 100)	//run toward and closer to captain, then shoot
		{
			ChangeEnemyState(AttackingWizard);
		}
		break;
	}
	case AttackingWizard:
	{
		vX = vY = 0;
		if (nHorizontalBullet > 0) 
		{
			if ((now - startTime) / 1000.0f >= 0.6f)	//shoot, then fly up
			{
				startTime = now;
				bul = new WizardBullet(posX - (width >> 1), posY - 33, HorizontalBullet);
				bul->isReverse = isReverse;
				bullets.push_back(bul);
				nHorizontalBullet--;
			}
		}
		else
		{
			ChangeEnemyState(FlyingWizard);
			nHorizontalBullet = NUM_OF_HORIZONTAL_BULLET;
		}
		break;
	}
	case FlyAttackWizard:
	{
		vY = 0;
		vX = isReverse ? 15.0f : -15.0f;
		posX += vX * deltaTime;
		if (abs(PLAYER->posX - posX) <= 4 && nVerticalBullet) //shoot bullet to player while flying
		{
			bul = new WizardBullet(posX + 5, posY, VerticalBullet);
			bul->isReverse = isReverse;
			bullets.push_back(bul);
			nVerticalBullet--;
		}

		if ((isReverse && abs(posX - CAMERA->GetBound().right) <= 15) || (!isReverse && abs(posX - CAMERA->GetBound().left) <= 15))	//then flying down
		{
			ChangeEnemyState(FlyingWizard);
			isReverse = !isReverse;
			
		}
		break;
	}
	case InjuringWizard:
	{
		if ((now - startTime) / 1000.0f >= 0.7f)	
		{
			startTime = now;
			ChangeEnemyState(StandingWizard);
		}
		break;
	}
	case DieWizard:
	{
		if ((now - startTime) / 1000.0f >= 3.0f)
		{
			startTime = now;
			isDead = true;
			PLAYER->isBossKilled = true;
			PLAYER->scores += this->point;
		}
		break;
	}
	default:
		break;
	}
	//boss is on small ground or is low health, then fly up to the right
	if ((posX < 60) && (currentState == FlyAttackWizard) && currHealth > 5 && !isReverse)
	{
		ChangeEnemyState(FlyingWizard);
	}

	if (bul != NULL)
	{
		GRID->AddObject(bul);
	}
}

RECT WizardBoss::GetBound()
{
	RECT r;
	r.left = posX - width / 2;
	r.top = posY - height;
	r.right = r.left + width;
	r.bottom = r.top + height;
	return r;
}

BoundingBox WizardBoss::GetBoundingBox()
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

void WizardBoss::Draw(D3DXVECTOR3 position, D3DXVECTOR3 cameraPosition, RECT sourceRect, D3DXVECTOR3 center)
{
	if (!isDead)
	{
		currentAnim->Draw(position, cameraPosition, sourceRect, center);
		for (auto m : bullets)
		{
			m->Draw();
		}
	}
}

void WizardBoss::Draw()
{
	if (!isDead)
	{
		Draw(D3DXVECTOR3(posX, posY, 0), CAMERA->camPosition, RECT(), D3DXVECTOR3(width / 2, height, 0));
	}

}

void WizardBoss::Release()
{
}

void WizardBoss::InsertFromFile(int level)
{
	std::unordered_set<GameObject*> rs;
	std::ifstream file;
	if (level == 2)
	{
		file.open("Resources/boss/wizardBoss.txt");
	}
	//insert to grid

	if (file.good())
	{
		while (!file.eof())
		{
			int x, y;
			file >> x;
			file >> y;
			
			GameObject* obj = new WizardBoss(x, y);
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
