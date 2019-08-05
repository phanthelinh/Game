#pragma once
#include "Enemy.h"
#include "../../Framework/Grid.h"
#include "Weapon/DMBullet.h"
#include "Weapon/DMBarrel.h"

enum DMState {
	DMStand,
	DMRun,
	DMThrowWait,
	DMBarrelExplode,
	DMHurt,
	DMInjuredStand,
	DMInjuredRun,
	DMDie
};

class DynamiteNapalm :public Enemy
{
public:
	DynamiteNapalm();
	DynamiteNapalm(float posX, float posY);
	DynamiteNapalm(RECT r);

	void SetState(DMState state);
	virtual void OnCollision(GameObject* object, float deltaTime = 0);
	virtual void Update(float deltaTime);
	RECT GetBound();
	BoundingBox GetBoundingBox();
	virtual void Draw(D3DXVECTOR3 position, D3DXVECTOR3 cameraPosition, RECT sourceRect = RECT(), D3DXVECTOR3 center = D3DXVECTOR3());
	//Draw at its position
	virtual void Draw();
	virtual void Release();
private:
	std::unordered_map<DynamiteNapalm, Animation*> animations;
	DMState	currentState, prevState;
	DMBullet* dmbullet;
	DMBarrel* dmbarrel;
};
