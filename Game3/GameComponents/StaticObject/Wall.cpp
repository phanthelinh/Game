#include "Wall.h"

Wall::Wall()
{
}

Wall::Wall(int x, int y, int width, int height)
{
	posX = x;
	posY = y;
	this->width = width;
	this->height = height;
	Tag = GameObjectTypes::WallObj;
}

Wall::~Wall()
{
}

void Wall::Draw(D3DXVECTOR3 position, D3DXVECTOR3 cameraPosition, RECT sourceRect, D3DXVECTOR3 center)
{
}

Box Wall::getBox()
{
	Box b;
	b.left = posX;
	b.top = posY;
	b.right = b.left + width;
	b.bottom = b.top + height;
	b.vx = b.vy = 0;
	return b;
}
