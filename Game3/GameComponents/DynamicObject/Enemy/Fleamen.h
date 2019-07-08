#pragma once
#include "../DynamicObject.h"

#define TIME_CHANGE					0.1f //time for an update
#define FLEAMEN_VX					60.0f	//accelerate x to increase posX
#define ACCELARATE_Y				10.0f

class Fleamen
	:public DynamicObject
{
public:
	Fleamen();
	Fleamen(int x, int y);
	~Fleamen();

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
private:
	float prevTime, accelerateX;
	int oldX, oldY; //the init pos of fleamen
	bool isMoveLeft; //true if move to left, false if move to right
	int step; //it will start two short hops before going to high leap
	D3DXVECTOR3 playerPos;
};

