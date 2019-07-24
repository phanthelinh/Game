#include "GameObject.h"



GameObject::GameObject()
{
}

GameObject::GameObject(float posX, float posY, float width, float height, Tag tag)
{
	this->posX = posX;
	this->posY = posY;
	this->width = width;
	this->height = height;
	this->tag = tag;
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

void GameObject::SetPosition(D3DXVECTOR3 pos)
{
	posX = pos.x;
	posY = pos.y;
}

RECT GameObject::GetBound()
{
	RECT bound;

	bound.left = (posX - width / 2);
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
	RECT b1 = GetBound();
	return !(b1.right < r.left || b1.left > r.right || b1.top > r.bottom || b1.bottom < r.top);
}

void GameObject::Release()
{
}

