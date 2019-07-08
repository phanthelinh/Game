#pragma once
#include "../DynamicObject.h"

#define BONE_MIN_VY -200.0f
class Bone :public DynamicObject
{
public:
	Bone();
	Bone(int x, int y, bool isLeft);
	~Bone();

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
	float accelerateX, accelerateY;
	float oldX, oldY;
	float maxDistance;
};
