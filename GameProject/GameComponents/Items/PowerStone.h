#pragma once
#include "../GameObject.h"
#include "../../Framework/Animation.h"
#include "../../Framework/Collision.h"

class PowerStone :public GameObject
{
private:
	bool isSmallType;
	Animation*	curDiamon;
	DWORD	firstTimeCollideGround;
public:
	PowerStone(int x, int y, int width, int height, bool isSmallType);
	PowerStone(RECT rect, bool isSmallType);
	void OnCollision(GameObject* object, float deltaTime = 0);
	void Update(float deltaTime);
	//Draw to its left-top position
	void Draw();
	virtual void Draw(D3DXVECTOR3 position, D3DXVECTOR3 cameraPosition, RECT sourceRect = RECT(), D3DXVECTOR3 center = D3DXVECTOR3()) override;
	virtual BoundingBox GetBoundingBox() override;
	void Release();
};