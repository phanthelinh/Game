#pragma once
#include "../DynamicObject.h"

#define ACCELERATE_X	70.0f
#define RANGE_X			40.0f //the range it will fly, reach that range, it will return

class Axe :public DynamicObject
{
public:
	Axe();
	Axe(float x, float y);
	~Axe();

	virtual void Update(float deltaTime);
	// Inherited via GameObject
	virtual void Draw(D3DXVECTOR3 position, D3DXVECTOR3 cameraPosition, RECT sourceRect = RECT(), D3DXVECTOR3 center = D3DXVECTOR3());

	void IsRenderLeft(bool flag);

	virtual Box getBox();

private:
	D3DXVECTOR3 startPos;//start position to draw
	bool isToLeft;//true if render to left
};
