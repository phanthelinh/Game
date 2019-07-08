#pragma once
#include "../GameObject.h"
#include "../../Framework/Sprite.h"

class StaticObject
	:public GameObject
{
public:
	StaticObject();
	StaticObject(int x, int y, int width, int height);
	 virtual ~StaticObject();

	// Inherited via GameObject
	virtual void Draw(D3DXVECTOR3 position, D3DXVECTOR3 cameraPosition, RECT sourceRect = RECT(), D3DXVECTOR3 center = D3DXVECTOR3());
	virtual Box getBox();
protected:
	//Sprite to draw static object
	Sprite * spriteObj;
};
