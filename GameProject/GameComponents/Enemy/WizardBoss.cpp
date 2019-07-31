#include "WizardBoss.h"

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
	animations[AttackingWizard] = new Animation("Resources/boss/Wizard_Attacking.png", 4, 1, 4);
	animations[FlyAttackWizard] = new Animation("Resources/boss/Wizard_FlyAttack.png", 3, 1, 3);
	animations[InjuringWizard] = new Animation("Resources/boss/Wizard_Injuring.png", 1, 1, 1);
	currentState = FlyingWizard;
	ChangeEnemyState(FlyingWizard);
	isReverse = true;
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
	if (object->tag == GroundTag)
	{
		CollisionResult res = COLLISION->SweptAABB(this->GetBoundingBox(), object->GetBoundingBox(), deltaTime);
		if (res.isCollide)
		{
			ChangeEnemyState(StandingWizard);
			posY = 390;
		}
	}
}

void WizardBoss::Update(float deltaTime)
{
	if (currHealth <= 0)
	{
		isDead = true;
		ChangeEnemyState(DieWizard);
	}
	switch (currentState)
	{
	case FlyingWizard:
	{
		vY = (posY >= 250) ? 10.0f : -10.0f;
		posY += vY * deltaTime;
		if (posY + height >= 450)	//collide with ground
		{
			ChangeEnemyState(StandingWizard);
			posY = 436;
		}
		break;
	}
	case StandingWizard:
	{
		vX = vY = 0;
		break;
	}
	case RunningWizard:
	{
		vX = (isReverse == false) ? -10.0f : 10.0f;
		posX += vX * deltaTime;
		posY += vY * deltaTime;

		break;
	}
	case AttackingWizard:
		vX = 0.0f;
		break;
	}
	currentAnim->_isFlipHor = false;
	currentAnim->Update(deltaTime);
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
