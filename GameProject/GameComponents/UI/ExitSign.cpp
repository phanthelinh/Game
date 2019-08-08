#include "ExitSign.h"

ExitSign::ExitSign()
{
	isDead = false;
	isVisible = true;
	playerPos = { 0,0,0 };
}

void ExitSign::Draw()
{
	Draw(GetPosition(), CAMERA->camPosition);

}

void ExitSign::Draw(D3DXVECTOR3 position, D3DXVECTOR3 cameraPosition, RECT sourceRect, D3DXVECTOR3 center)
{
	if (isVisible == true)
		Draw(position, cameraPosition, sourceRect, center);
}

void ExitSign::Update(float deltaTime)
{
	
}

BoundingBox ExitSign::GetBoundingBox()
{
	BoundingBox bound;

	bound.left = posX - width/2;
	bound.top = posY - height/2;
	bound.right = posX + width;
	bound.bottom = posY + height;
	bound.vX = this->vX;
	bound.vY = this->vY;

	return bound;
}
