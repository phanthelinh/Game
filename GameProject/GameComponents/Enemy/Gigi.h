#pragma once
#include "Enemy.h"
#include "Weapon/HomingMissile.h"
#include "../../Framework/Grid.h"
#include "../Effect/Explode.h"
#include "../Player/Player.h"
#include <unordered_map>

enum GigiState
{
	GigiStand,
	GigiSuprised,
	GigiShot,
	GigiFly,
	GigiFlyStill,
	GigiDie
};

class Gigi : public Enemy
{
private:
	std::unordered_map<GigiState, Animation*> animations;
	GigiState	currentState, prevState;
	std::vector<HomingMissile*>	missiles;
	float LastShotTime = 0.0f;
	float DeadStartTime = 0.0f;
	float StateTime = 0.0f;
	float savedvX = 0.0f;

	bool isWaiting = true;
	bool isAttacking = false;
	bool isDying = false;
public:

	Gigi(int level);
	Gigi(float posX, float posY);
	Gigi(RECT r);

	static void InsertFromFile(int level);

	int CheckPosition(); 
	void CheckReverse();
	//necessary functions
	void SetState(GigiState state);
	void OnCollision(GameObject* object, float deltaTime = 0);
	void Update(float deltaTime);
	void Draw(D3DXVECTOR3 position, D3DXVECTOR3 cameraPosition, RECT sourceRect = RECT(), D3DXVECTOR3 center = D3DXVECTOR3());
	void Draw();
	RECT GetBound();
	BoundingBox GetBoundingBox();
	void Release();
};
