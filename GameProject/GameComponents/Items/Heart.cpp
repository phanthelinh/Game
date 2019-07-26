#include "Heart.h"

Heart::Heart(int left, int top, int width, int height)
{
	posX = left;
	posY = top;
	this->width = width;
	this->height = height;
	vY = 12.0f;
	heart = new Animation("Resources/items/heart_24_12.png", 2, 1, 2, true, 0.5);
	tag = Tag::HeartTag;
}

Heart::Heart(RECT rect):Heart(rect.left,rect.top, rect.right-rect.left,rect.bottom-rect.top)
{
}

void Heart::ExecuteCollision(GameObject * object)
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

void Heart::Update(float deltaTime)
{
	if (!isDead)
	{
		heart->Update(deltaTime);
		posY += vY * deltaTime;
	}
}

void Heart::Draw()
{
	if(!isDead)
		Draw(D3DXVECTOR3(posX, posY, 0), CAMERA->camPosition, RECT(), D3DXVECTOR3(0, 0, 0));
}

void Heart::Draw(D3DXVECTOR3 position, D3DXVECTOR3 cameraPosition, RECT sourceRect, D3DXVECTOR3 center)
{
	if(!isDead)
		heart->Draw(position, cameraPosition, sourceRect, center);
}

BoundingBox Heart::GetBoundingBox()
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

void Heart::Release()
{
	if (heart != nullptr)
	{
		delete heart;
	}
}
