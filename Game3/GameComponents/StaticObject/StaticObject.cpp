#include "StaticObject.h"

StaticObject::StaticObject()
{
	spriteObj = NULL;
}

StaticObject::StaticObject(int x, int y, int width, int height)
{
	posX = x;
	posY = y;
	this->width = width;
	this->height = height;
}

StaticObject::~StaticObject()
{
	Memory::SafeDelete(spriteObj);
}

void StaticObject::Draw(D3DXVECTOR3 position, D3DXVECTOR3 cameraPosition, RECT sourceRect, D3DXVECTOR3 center)
{
}

Box StaticObject::getBox()
{
	return GameObject::getBox();
}

