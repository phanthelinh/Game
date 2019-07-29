#pragma once
#include "Enemy.h"
#include "../Effect/Explode.h"
#include "../Player/Player.h"
#include <unordered_map>

class RunningMan : public Enemy
{
private:
	std::unordered_map<EnemyStateName, Animation*> animations;
	EnemyStateName	currentState, prevState;
	
	//variables that helps control runningman's behaviour
	bool isWaiting = true;
	bool isAttacking = false;
public:
	RunningMan();
	RunningMan(float posX, float posY);
	RunningMan(RECT r);

	bool CheckPosition(); //0 is shooting range, 1 is running range

	//necessary functions
	void SetState(EnemyStateName state);
	void OnCollision(GameObject* object, float deltaTime = 0);
	void Update(float deltaTime);
	void Draw(D3DXVECTOR3 position, D3DXVECTOR3 cameraPosition, RECT sourceRect = RECT(), D3DXVECTOR3 center = D3DXVECTOR3());
	void Draw();
	RECT GetBound();
	BoundingBox GetBoundingBox();
	void Release();
};
