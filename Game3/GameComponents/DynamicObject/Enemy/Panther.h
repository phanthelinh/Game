#pragma once
#include "../DynamicObject.h"
#define PANTHER_VX 20
#define PANTHER_VY 30
#define ACCELERATEY 20

class Panther: public DynamicObject
{
public:
	Panther();
	Panther(float x, float y);
	~Panther();
	Panther getPanther();
	void Update(float deltaTime);
	void Draw(D3DXVECTOR3 position, D3DXVECTOR3 cameraPosition, RECT sourceRect, D3DXVECTOR3 center);
	virtual void SetPlayerPosition(D3DXVECTOR3 player);
	virtual Box getBox();
	void ResetFrame(int index);
	virtual void OnCollision(GameObject* entity, float deltaTime);
	void Jump();
	void Stop();
	void Run();
private:
	D3DVECTOR playerPos;
	int frameIndex;
	bool onGround;
	bool isMoveLeft;
	bool isJumped; //if it already jumped 
	bool willOnGround;	//identify if panther collide with ground on next frame
};

