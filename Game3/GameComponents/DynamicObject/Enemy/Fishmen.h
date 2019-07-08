#pragma once
#include "../DynamicObject.h"
#include "Bullet.h"
#include "../Items/LargeHeart.h"
class Fishmen : public DynamicObject
{
public:
	Fishmen();
	Fishmen(int x, int y);
	~Fishmen();

	virtual void Update(float deltaTime);
	// Inherited via GameObject
	virtual void Draw(D3DXVECTOR3 position, D3DXVECTOR3 cameraPosition, RECT sourceRect = RECT(), D3DXVECTOR3 center = D3DXVECTOR3());
	//player position to enable animation
	virtual void SetPlayerPosition(D3DXVECTOR3 player);
	//Get box for collision detection
	virtual Box getBox();
	//handle collision when player attack
	virtual void OnCollision(GameObject* entity, float deltaTime);
	//get waepon of certain object, used to check collision
	virtual GameObject* GetWeaponObject();
	//get items after this object was destroyed
	virtual GameObject* GetItems();
private:
	void SetFrame(int index);
	GameObject* heart;
	Bullet * bullet;
	int currentIndex;
	bool startBullet, startMoving, isLeft, onGround;
	D3DXVECTOR3 playerPos;
	float bulletTime, timePerFrame;
	D3DXVECTOR3 hittedPosition;
};
