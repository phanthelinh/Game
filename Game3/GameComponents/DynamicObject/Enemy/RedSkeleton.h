#pragma once
#include "../DynamicObject.h"
#include "../../../Framework/UIDrawing.h"
#include <string>

#define ACCELERATE_X_REDSKELETON 100.0f

class RedSkeleton
	:public DynamicObject
{
public:
	RedSkeleton();
	RedSkeleton(int x, int y);
	~RedSkeleton();
	virtual void Update(float deltaTime);
	// Inherited via GameObject
	virtual void Draw(D3DXVECTOR3 position, D3DXVECTOR3 cameraPosition, RECT sourceRect = RECT(), D3DXVECTOR3 center = D3DXVECTOR3());
	//player position to enable animation
	virtual void SetPlayerPosition(D3DXVECTOR3 player);
	virtual Box getBox();
	virtual void OnCollision(GameObject* entity, float deltaTime);
private:
	void ResetFrame(int index);
	float prevTime, sleepTime;
	bool isLeft;
	int frameReset;
	D3DXVECTOR3 playerPos;
	int step;
};