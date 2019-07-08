#include "StairTopObj.h"

StairTopObj::StairTopObj(int x, int y, int width, int height, bool isLeft)
{
	posX = x;
	posY = y;
	this->width = width;
	this->height = height;
	this->isLeft = isLeft;
	Tag = GameObjectTypes::StairTopObj;
}

StairTopObj::~StairTopObj()
{
}

void StairTopObj::Draw(D3DXVECTOR3 position, D3DXVECTOR3 cameraPosition, RECT sourceRect, D3DXVECTOR3 center)
{
}

Box StairTopObj::getBox()
{
	Box b;
	b.left = posX;
	b.top = posY;
	b.right = b.left + width;
	b.bottom = b.top + height;
	b.vx = b.vy = 0;
	return b;
}

bool StairTopObj::IsLeft()
{
	return isLeft;
}
