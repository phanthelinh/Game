#pragma once
#include "../DynamicObject.h"

#define ACCELERATE_X 100.0f

class Bullet
	:public DynamicObject
{
public:
	Bullet();
	Bullet(int x, int y, bool isLeft);
	~Bullet();
	virtual void Update(float deltaTime);
	// Inherited via GameObject
	virtual void Draw(D3DXVECTOR3 position, D3DXVECTOR3 cameraPosition, RECT sourceRect = RECT(), D3DXVECTOR3 center = D3DXVECTOR3());
	//player position to enable animation
	virtual void SetPlayerPosition(D3DXVECTOR3 player);
	virtual Box getBox();
	//handle collision when player attack
	virtual void OnCollision(GameObject* entity, float deltaTime);
private:
	bool isLeft;
};
