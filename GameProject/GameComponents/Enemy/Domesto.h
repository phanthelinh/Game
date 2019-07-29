#pragma once
#include "Enemy.h"
#include "../Effect/Explode.h"
#include "../Player/Player.h"
#include <unordered_map>

class Domesto : public Enemy
{
private:
	std::unordered_map<EnemyStateName, Animation*> anims;
	EnemyStateName	currentState, prevState;
	DWORD		startTime;

public:
	Domesto();
	//posX, posY is the left + width/2, bottom of enemies
	Domesto(float posX, float posY);
	Domesto(RECT r);

	void ChangeEnemyState(EnemyStateName state);

	void OnCollision(GameObject* object, float deltaTime = 0);
	void Update(float deltaTime);
	void Draw(D3DXVECTOR3 position, D3DXVECTOR3 cameraPosition, RECT sourceRect = RECT(), D3DXVECTOR3 center = D3DXVECTOR3());
	//Draw at its position
	void Draw();
	RECT GetBound();
	BoundingBox GetBoundingBox();
	void Release();
};
