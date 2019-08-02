#include "WizardBoss.h"
#include "../Ground.h"
#define NUM_OF_HORIZONTAL_BULLET 3
#define NUM_OF_VERTICAL_BULLET 1

WizardBoss::WizardBoss() :Enemy()
{
	tag = Wizard;
	maxHealth = 14;
}

WizardBoss::WizardBoss(float posX, float posY) :Enemy(posX, posY, 0, 0)
{
	tag = Wizard;
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
}

WizardBoss::WizardBoss(RECT r) :Enemy(r)
{
	maxHealth = 14;
	tag = Wizard;
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
			//low health, then not check small ground collision
			if (currentState == FlyAttackWizard && (currHealth <= 5 || isReverse))	
				continue;
			ChangeEnemyState(StandingWizard);
			posY = g->posY;
			isOnGround = true;
		}
	}
	if (object->tag == Captain)
	{
		res = COLLISION->SweptAABB(this->GetBoundingBox(), object->GetBoundingBox(), deltaTime);
		if (res.isCollide)
		{
			ChangeEnemyState(InjuringWizard);
			posX += vX > 0 ? -5 : 5;
		}
	}
}

void WizardBoss::Update(float deltaTime)
{
	auto now = GetTickCount();
	currentAnim->_isFlipHor = isReverse;
	
	if (currHealth <= 0)
	{
		isDead = true;
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
		
		if (isOnGround && posY + height <= 150)	//is flying up and touch camera.top, then fly horizontally and attack
		{
			vY = 0;
			ChangeEnemyState(FlyAttackWizard);
			isOnGround = false;
		}
		break;
	}
	case InjuringWizard:
	{
		if ((now - startTime)/1000.0f >= 0.5f)
		{
			startTime = now;
			ChangeEnemyState(StandingWizard);
		}
	}
	break;
	case StandingWizard:
	{
		vX = vY = 0;

		//run toward player and shoot
		if ((now - startTime) / 1000.0f >= 2.0f)
		{
			startTime = now;
			if (prevState == FlyAttackWizard)	//is standing on small ground
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
		posY += vY * deltaTime;
		if (abs(PLAYER->posX - posX) <= 200)	//run toward and closer to captain, then shoot
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
			if ((now - startTime) / 1000.0f >= 0.7f)	//shoot, then fly up
			{
				startTime = now;
				bul = new WizardBullet(posX-2, posY - 33, HorizontalBullet);
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
		if (abs(PLAYER->posX - posX) <= 20 && nVerticalBullet) //shoot bullet to player while flying
		{
			bul = new WizardBullet(posX, posY, VerticalBullet);
			bul->isReverse = isReverse;
			bullets.push_back(bul);
			nVerticalBullet--;
		}

		if ((isReverse && abs(posX - CAMERA->GetBound().right) <= 10) || (!isReverse && abs(posX - CAMERA->GetBound().left) <= 10))	//then flying down
		{
			ChangeEnemyState(FlyingWizard);
			isReverse = !isReverse;
			nVerticalBullet = NUM_OF_VERTICAL_BULLET;
		}
		break;
	}
	default:
		break;
	}
	if (bul != NULL)
	{
		GRID->AddObject(bul);
	}
}

RECT WizardBoss::GetBound()
{
	RECT r;
	r.left = posX;
	r.top = posY;
	r.right = posX + width;
	r.bottom = posY + height;
	return r;
}

BoundingBox WizardBoss::GetBoundingBox()
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
