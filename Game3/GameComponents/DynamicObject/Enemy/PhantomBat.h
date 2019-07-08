#pragma once
#include "../DynamicObject.h"
#include "../Items/Crystal.h"

#define BOSS_VX 10
#define BOSS_VY 10

class PhantomBat
	:public DynamicObject
{
public:
	PhantomBat();
	PhantomBat(int x, int y);
	~PhantomBat();

	virtual void Update(float deltaTime);
	// Inherited via GameObject
	virtual void Draw(D3DXVECTOR3 position, D3DXVECTOR3 cameraPosition,
		RECT sourceRect = RECT(), D3DXVECTOR3 center = D3DXVECTOR3());
	//player position to enable animation
	virtual void SetPlayerPosition(D3DXVECTOR3 player);
	//get box to detect collision
	virtual Box getBox();
	//handle collision when player attack
	virtual void OnCollision(GameObject* entity, float deltaTime);
	//get items after this object was destroyed
	virtual GameObject* GetItems();
	void Sleep();
	void Fly(float deltaTime);
	void FollowPlayer(float deltaTime);
	void GetRandomPosition();
	void FlyRandom(float deltaTime);

	bool Start(float deltaTime);
private:
	void SetFrame(int index);
	D3DXVECTOR3 playerPos;
	D3DXVECTOR2 direction;
	D3DXVECTOR2 random;
	RECT* cameraBound;
	float distance;

	float startTime;
	float waitTime;
	int frameIndex;
	int hp;
	D3DXVECTOR3 hittedPosition, campos;
	GameObject* crystal;
};

