#include "Ground.h"

Ground::Ground(RECT r):GameObject(r)
{
	tag = GroundTag;
	vX = vY = 0;
}

Ground::Ground(float x, float y, float width, float height):GameObject(x, y, width, height, GroundTag)
{
	
}

Ground::~Ground()
{
}

void Ground::Update(float deltaTime)
{
}

void Ground::Draw()
{
}

void Ground::Draw(D3DXVECTOR3 position, D3DXVECTOR3 cameraPosition, RECT sourceRect, D3DXVECTOR3 center)
{
}

BoundingBox Ground::GetBoundingBox()
{
	BoundingBox b;
	b.left = posX;
	b.top = posY;
	b.right = b.left + width;
	b.bottom = b.top + height;
	b.vX = b.vY = 0;
	return b;
}

void Ground::Release()
{
}
