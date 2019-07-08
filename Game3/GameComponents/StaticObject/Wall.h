#pragma once
#include "StaticObject.h"
class Wall : public StaticObject
{
public:
	Wall();
	Wall(int x, int y, int width, int height);
	~Wall();

	// Inherited via GameObject
	virtual void Draw(D3DXVECTOR3 position, D3DXVECTOR3 cameraPosition, RECT sourceRect = RECT(), D3DXVECTOR3 center = D3DXVECTOR3());
	virtual Box getBox();
};
