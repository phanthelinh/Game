#pragma once
#include "../DynamicObject.h"
class Crystal : public DynamicObject
{
public:
	Crystal();
	Crystal(int x, int y);
	~Crystal();
	//handle collision when player attack
	virtual void OnCollision(GameObject* entity, float deltaTime);
	virtual void Update(float deltaTime);
	virtual void Draw(D3DXVECTOR3 position, D3DXVECTOR3 cameraPosition, RECT sourceRect = RECT(), D3DXVECTOR3 center = D3DXVECTOR3());
	virtual Box getBox();
private:
	bool stopFalling, onGround;
	float fallingTime;
};