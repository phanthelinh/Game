#pragma once
#include "Enemy.h"
#include "Weapon/Bullet.h"
#include "../../Framework/Grid.h"
#include "../Effect/Explode.h"
#include "../Player/Player.h"
#include <unordered_map>

class Gigi : public Enemy
{
private:
	std::unordered_map<EnemyStateName, Animation*> animations;
	EnemyStateName	currentState, prevState;
	std::vector<Bullet*>	bullets;
	float LastShotTime = 0.0f;
	float DeadStartTime = 0.0f;

	//variables that helps control runningman's behaviour
	bool isWaiting = true;
	bool isAttacking = false;
	bool isDying = false;
public:
	int type, color;

	Gigi(int level);
	Gigi(float posX, float posY, int type = 0, int color = 0); //type 0 binh thuong, type 1 ngoi tai cho //color = 0 la mau xanh duong, color = 1 la mau xanh la
	Gigi(RECT r);

	static void InsertFromFile(int level);

	int CheckPosition(); //0 is shooting range, 1 is running range

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
