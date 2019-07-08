#pragma once
#include "../DynamicObject.h"
class SmallHeart : public DynamicObject
{
public:
	SmallHeart();
	SmallHeart(int x, int y);
	~SmallHeart();

	//handle collision when player attack
	virtual void OnCollision(GameObject* entity, float deltaTime);
	virtual void Update(float deltaTime);
	virtual void Draw(D3DXVECTOR3 position, D3DXVECTOR3 cameraPosition, RECT sourceRect = RECT(), D3DXVECTOR3 center = D3DXVECTOR3());
	virtual Box getBox();
private:
	bool stopFalling;
	float existTime;
};