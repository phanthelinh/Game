#include "WizardBoss.h"

WizardBoss::WizardBoss():Enemy()
{
	tag = Wizard;
	maxHealth = 14;
	animations[StandingWizard] = new Animation("Resources/boss/Wizard_Standing.png", 2, 1, 2);
	currentAnim = animations[StandingWizard];
}

WizardBoss::WizardBoss(float posX, float posY, float width, float height):Enemy(posX, posY, width, height)
{
	tag = Wizard;
	maxHealth = 14;
}

WizardBoss::WizardBoss(RECT r):Enemy(r)
{
	maxHealth = 14;
	tag = Wizard;
}

void WizardBoss::OnCollision(GameObject* object, float deltaTime)
{
}

RECT WizardBoss::GetBound()
{
	return RECT();
}

BoundingBox WizardBoss::GetBoundingBox()
{
	return BoundingBox();
}

void WizardBoss::Update(float deltaTime)
{
}

void WizardBoss::Draw()
{
	currentAnim->_isFlipHor = false;
	currentAnim->Draw(posX, posY);
}

void WizardBoss::Release()
{
}
