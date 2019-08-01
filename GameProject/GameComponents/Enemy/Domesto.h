#pragma once
#include "Enemy.h"
#include "../../Framework/Grid.h"
#include "../Effect/Explode.h"
#include "../Player/Player.h"
#include "Weapon/Missile.h"
#include <unordered_map>
#include <vector>
#include <fstream>

enum EnemyDomestoType
{
	DomestoRunning,
	DomestoJumping
};

class Domesto : public Enemy
{
private:
	std::unordered_map<EnemyStateName, Animation*>	anims;
	EnemyStateName									currentState, prevState;
	DWORD											startTime;
	std::vector<Missile*>							missles;
	bool											isPauseMissile;
	bool											isStopUpdate;
	EnemyDomestoType								domestoType;
public:
	//Call this constructor for insert all Domesto to grid
	Domesto(int level);
	//posX, posY is the left + width/2, bottom of enemies
	Domesto(float x, float y);
	Domesto(float posX, float posY, EnemyDomestoType type);
	
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
