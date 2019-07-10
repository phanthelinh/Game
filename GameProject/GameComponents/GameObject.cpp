#include "GameObject.h"



GameObject::GameObject()
{
}


GameObject::~GameObject()
{
}

BoundingBox GameObject::GetBoundingBox()
{
	BoundingBox bound;

	bound.left = posX - width / 2;
	bound.top = posY - height / 2;
	bound.right = posX + width / 2;
	bound.bottom = posY + height / 2;
	bound.vX = this->vX;
	bound.vY = this->vY;

	return bound;
}

D3DXVECTOR3 GameObject::GetPosition()
{
	return D3DXVECTOR3(posX, posY, 0);
}

RECT GameObject::GetBound()
{
	RECT bound;

	bound.left = posX - width / 2;
	bound.top = posY - height / 2;
	bound.right = posX + width / 2;
	bound.bottom = posY + height / 2;

	return bound;
}

void GameObject::Update(float deltaTime)
{
	posX = posX + deltaTime * vX;
	posY = posY + deltaTime * vY;
}

bool GameObject::IsCollide(RECT r)
{
	return false;
}

