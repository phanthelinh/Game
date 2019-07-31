#pragma once
#include "Enemy.h"

enum WizardState {
	StandingWizard,
	RunningWizard,
	FlyingWizard,
	AttackingWizard,	//on ground attack
	FlyAttackWizard,	//on air attack
	InjuringWizard,
	DieWizard
};

class WizardBoss :public Enemy
{
public:
	WizardBoss();
	WizardBoss(float posX, float posY);
	WizardBoss(RECT r);

	void ChangeEnemyState(WizardState state);
	virtual void OnCollision(GameObject* object, float deltaTime = 0);
	virtual void Update(float deltaTime);
	RECT GetBound();
	BoundingBox GetBoundingBox();
	virtual void Draw(D3DXVECTOR3 position, D3DXVECTOR3 cameraPosition, RECT sourceRect = RECT(), D3DXVECTOR3 center = D3DXVECTOR3());
	//Draw at its position
	virtual void Draw();
	virtual void Release();
private:
	std::unordered_map<WizardState, Animation*> animations;
	WizardState	currentState, prevState;
	DWORD		startTime;

};
