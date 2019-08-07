#pragma once
#include "Enemy.h"
#include "../../Framework/Grid.h"
#include "Weapon/DMBullet.h"
#include "Weapon/DMBarrel.h"

enum DMState {
	DMBarrelThrow,
	DMHurt,
	DMInjuredRun,
	DMInjuredStand,
	DMRun,
	DMShot,
	DMStand,
	DMFall,
	DMThrowWait,
	DMDie
};

class DynamiteNapalm :public Enemy
{
public:
	float StateTime = 0.0f;
	float LastShotTime = 0.0f;
	DynamiteNapalm();
	DynamiteNapalm(float posX, float posY);
	DynamiteNapalm(RECT r);

	void ChangeState(DMState state);
	bool CheckStateTime(float offset, float compared);
	void SetState(DMState state);
	virtual void OnCollision(GameObject* object, float deltaTime = 0);
	virtual void Update(float deltaTime);
	RECT GetBound();
	BoundingBox GetBoundingBox();
	virtual void Draw(D3DXVECTOR3 position, D3DXVECTOR3 cameraPosition, RECT sourceRect = RECT(), D3DXVECTOR3 center = D3DXVECTOR3());
	//Draw at its position
	virtual void Draw();
	virtual void Release();
	DMState GetState();
private:
	bool waitfornextshot = false; //handle the shooting state
	int shotcount = 0; //count the shots
	std::unordered_map<DMState, Animation*> animations;
	DMState	currentState, prevState;
	std::vector<DMBullet*>	dmbullet;
	DMBarrel*	dmbarrel;
	bool isOnGround;
};
