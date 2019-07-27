#include "ExitGem.h"

ExitGem::ExitGem(int left, int top, int width, int height)
{
	posX = left;
	posY = top;
	this->width = width;
	this->height = height;
	vY = 12.0f;
	exitGem = new Animation("Resources/items/exitgem_32_16.png", 2, 1, 2, true, 0.5);
	tag = Tag::ExitGemTag;
}

ExitGem::ExitGem(RECT rect):ExitGem(rect.left,rect.top,rect.right-rect.left, rect.bottom-rect.top)
{
}

void ExitGem::OnCollision(GameObject * object, float deltaTime)
{
	if (isDead)
		return;
	if (object->tag != Tag::Captain || object->tag != Tag::Ground)
	{
		return;
	}
	auto collideRes = COLLISION->SweptAABB(object->GetBoundingBox(), GetBoundingBox());
	if (collideRes.isCollide)
	{
		switch (object->tag)
		{
		case Tag::Ground:
			posY += vY * collideRes.entryTime;
			vY = 0;
			break;
		default:
			break;
		}
	}
	//if collide with captain america
	isDead = true;
	//increase score
	//..
}

void ExitGem::Update(float deltaTime)
{
	if (!isDead)
	{
		exitGem->Update(deltaTime);
		posY += deltaTime * vY;
	}
}

void ExitGem::Draw()
{
	if (!isDead)
		Draw(D3DXVECTOR3(posX, posY, 0), CAMERA->camPosition, RECT(), D3DXVECTOR3(0, 0, 0));
}

void ExitGem::Draw(D3DXVECTOR3 position, D3DXVECTOR3 cameraPosition, RECT sourceRect, D3DXVECTOR3 center)
{
	if (!isDead)
		exitGem->Draw(position, cameraPosition, sourceRect, center);
}

BoundingBox ExitGem::GetBoundingBox()
{
	BoundingBox b;
	b.left = posX;
	b.top = posY;
	b.right = b.left + width;
	b.bottom = b.top + height;
	b.vX = 0;
	b.vY = vY;
	return b;
}

void ExitGem::Release()
{
	if (exitGem != nullptr)
	{
		delete exitGem;
	}
}
