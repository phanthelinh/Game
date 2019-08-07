#include "Water.h"

Water::Water(RECT r) :GameObject(r)
{
	tag = WaterTag;
	vX = vY = 0;
}

Water::Water(float x, float y, float width, float height):GameObject(x, y, width, height, WaterTag)
{
}

Water::~Water()
{
}

void Water::Update(float deltaTime)
{
}

void Water::Draw()
{
}

void Water::Draw(D3DXVECTOR3 position, D3DXVECTOR3 cameraPosition, RECT sourceRect, D3DXVECTOR3 center)
{
}

BoundingBox Water::GetBoundingBox()
{
	BoundingBox b;
	b.left = posX;
	b.top = posY;
	b.right = b.left + width;
	b.bottom = b.top + height;
	b.vX = b.vY = 0;
	return b;
}

RECT Water::GetBound()
{
	RECT b;
	b.left = posX;
	b.top = posY;
	b.right = b.left + width;
	b.bottom = b.top + height;
	
	return b;
}

void Water::Release()
{
}
