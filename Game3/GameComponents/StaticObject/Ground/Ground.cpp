#include "Ground.h"

Ground::Ground(int x, int y, int width, int height)
{
	posX = x;
	posY = y;
	this->width = width;
	this->height = height;
	Tag = GameObjectTypes::Ground;
}

Ground::~Ground()
{
}

void Ground::Draw(D3DXVECTOR3 position, D3DXVECTOR3 cameraPosition, RECT sourceRect, D3DXVECTOR3 center)
{
}

Box Ground::getBox()
{
	Box b;
	b.left = posX;
	b.top = posY;
	b.right = b.left + width;
	b.bottom = b.top + height;
	b.vx = b.vy = 0;
	return b;
}
