#pragma once
#include "StaticObject.h"

class StairBottomObj
	:public StaticObject
{
public:
	StairBottomObj(int x, int y, int width, int height, bool isLeft);
	~StairBottomObj();

	virtual void Draw(D3DXVECTOR3 position, D3DXVECTOR3 cameraPosition, RECT sourceRect = RECT(), D3DXVECTOR3 center = D3DXVECTOR3());

	virtual Box getBox();

	bool IsLeft();
private:
	bool isLeft;
};