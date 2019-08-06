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
	point = 1000;	//score when kill this boss
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
	isDead = false;
	isOnGround = false; //falling down
	nHorizontalBullet = NUM_OF_HORIZONTAL_BULLET;
	nVerticalBullet = NUM_OF_VERTICAL_BULLET;
	enemySubTag = EnemySubTag::WizardBossTag;
}

WizardBoss::WizardBoss(RECT r) :Enemy(r)
{
	enemySubTag = EnemySubTag::WizardBossTag;
	maxHealth = 50;
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
		if (res.isCollide)
		{
			//OutputDebugStringA("colission: ");
			//low health, then not check small ground collision
			/*if ((currentState == FlyAttackWizard && (currHealth <= 5 || isReverse)) || (currentState == StandingWizard && !isReverse))
			{
				OutputDebugStringA("skip \r\n");
				continue;
			}*/
			switch (currentState)
			{
			case FlyAttackWizard:
				//OutputDebugStringA("a\r\n");
				//ChangeEnemyState(FlyingWizard);
				break;
			case FlyingWizard:
				//OutputDebugStringA("b\r\n");
				isOnGround = true;
				startTime = GetTickCount();
				ChangeEnemyState(StandingWizard);
				
				break;
				//OutputDebugStringA("nothing \r\n");
			}
			
			//posY += vY * deltaTime;
			//isOnGround = true;
		}
	}
	auto colRes = COLLISION->SweptAABB(object->GetBoundingBox(), GetBoundingBox(), deltaTime);
	if (colRes.isCollide && object->tag == ShieldTag)
	{
		currHealth -= 5;
		ChangeEnemyState(InjuringWizard);
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
				//OutputDebugStringA("staanding\r\n");
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
		//OutputDebugStringA("running\r\n");
		vX = (isReverse == false) ? -15.0f : 15.0f;
		posX += vX * deltaTime;
		//posY += vY * deltaTime;
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
		posX += vX > 0 ? -2 : 2;
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
		}
		break;
	}
	default:
		break;
	}

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
