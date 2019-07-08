#pragma once
#include "../DynamicObject.h"
#include "Axe.h"
#include "../../../Framework/UIDrawing.h"
#include <string>
#define TIME_CHANGE					0.1f //time for an update
#define ACCELARATE_X				70.0f	//accelerate x to increase posX
#define DISTANCE_MAX				40.0f	//distance max of fleamen moving forward two different sides

class AxeKnight :public DynamicObject
{
public:
	AxeKnight();
	AxeKnight(float x, float y);
	~AxeKnight();
	void Update(float deltaTime);
	void Draw(D3DXVECTOR3 position, D3DXVECTOR3 cameraPosition, RECT sourceRect, D3DXVECTOR3 center);
	virtual void SetPlayerPosition(D3DXVECTOR3 player);
	virtual Box getBox();
	void CheckCollisionWithAxe(float deltaTime);
private:
	D3DXVECTOR3 playerPos;
	Axe * axe;
	float prevTime, prev1;
	int oldX, oldY;
	bool isMoveLeft; //true if move to left, false if move to right
	bool throwing;	//throw hammer
	
};