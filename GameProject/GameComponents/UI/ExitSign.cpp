#include "ExitSign.h"
#include "../Player/Player.h"

#define X_OFFSET 40
#define Y_OFFSET 30

ExitSign::ExitSign()
{
	isDead = false;
	isVisible = true;
	currAnim = new Animation("Resources/UI/Exit.png", 2, 1, 2, true, 1.5f);
	isReverse = false;
}

void ExitSign::Draw()
{
	Draw(GetPosition(), CAMERA->camPosition);

}

void ExitSign::Draw(D3DXVECTOR3 position, D3DXVECTOR3 cameraPosition, RECT sourceRect, D3DXVECTOR3 center)
{
	if (isVisible == true)
		currAnim->Draw(position, cameraPosition, sourceRect, center);
}

void ExitSign::Update(float deltaTime)
{
	posX = CAMERA->GetBound().left + X_OFFSET;
	posY = CAMERA->GetBound().top + Y_OFFSET;

	currAnim->Update(deltaTime);
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
