#pragma once
#include "../DynamicObject.h"
#include "Bullet.h"
class BoneTower
	:public DynamicObject
{
public:
	BoneTower();
	BoneTower(int x, int y, bool isLeft);
	~BoneTower();
	virtual void Update(float deltaTime);
	// Inherited via GameObject
	virtual void Draw(D3DXVECTOR3 position, D3DXVECTOR3 cameraPosition, RECT sourceRect = RECT(), D3DXVECTOR3 center = D3DXVECTOR3());
	//player position to enable animation
	virtual void SetPlayerPosition(D3DXVECTOR3 player);
	virtual Box getBox();
private:
	float prevTime;
	bool isLeft;
	Bullet * bullet;
};
