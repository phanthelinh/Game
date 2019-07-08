#pragma once
#include "../StaticObject.h"

class Ground
	:public StaticObject
{
public:
	Ground(int x, int y, int width, int height);
	~Ground();

	virtual void Draw(D3DXVECTOR3 position, D3DXVECTOR3 cameraPosition, RECT sourceRect = RECT(), D3DXVECTOR3 center = D3DXVECTOR3());

	virtual Box getBox();
};