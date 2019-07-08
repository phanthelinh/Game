#include "StairBottomObj.h"

StairBottomObj::StairBottomObj(int x, int y, int width, int height, bool isLeft)
{
	posX = x;
	posY = y;
	this->width = width;
	this->height = height;
	this->isLeft = isLeft;
	Tag = GameObjectTypes::StairBottomObj;
}

StairBottomObj::~StairBottomObj()
{
}

void StairBottomObj::Draw(D3DXVECTOR3 position, D3DXVECTOR3 cameraPosition, RECT sourceRect, D3DXVECTOR3 center)
{
}

Box StairBottomObj::getBox()
{
	Box b;
	b.left = posX;
	b.top = posY;
	b.right = b.left + width;
	b.bottom = b.top + height;
	b.vx = b.vy = 0;
	return b;
}

bool StairBottomObj::IsLeft()
{
	return isLeft;
}
