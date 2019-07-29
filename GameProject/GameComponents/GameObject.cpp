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
	vY = vX = 0;
}

GameObject::GameObject(RECT r)
{
	this->posX = r.left;
	this->posY = r.top;
	this->width = r.right - r.left;
	this->height = r.bottom - r.top;
}

GameObject::~GameObject()
{
}

BoundingBox GameObject::GetBoundingBox()
{
	BoundingBox bound;

	bound.left = posX ;
	bound.top = posY;
	bound.right = posX + width ;
	bound.bottom = posY + height;
	bound.vX = this->vX;
	bound.vY = this->vY;

	return bound;
}

BoundingBox GameObject::GetBoundingBoxFromCorner()
{
	BoundingBox r;
	r.left = posX;
	r.top = posY;
	r.right = posX + width;
	r.bottom = posY + height;
	r.vX = vX;
	r.vY = vY;
	return r;
}

void GameObject::OnCollision(GameObject * object, float deltaTime)
{
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

RECT GameObject::GetBoundFromCorner()
{
	RECT r;
	r.left = posX;
	r.top = posY;
	r.right = posX + width;
	r.bottom = posY + height;
	return r;
}

void GameObject::Update(float deltaTime)
{
	dX = vX * deltaTime;
	dY = vY * deltaTime;
	posX = posX + dX;
	posY = posY + dY;
}

bool GameObject::IsCollide(RECT r)
{
	RECT b1 = GetBound();
	return !(b1.right < r.left || b1.left > r.right || b1.top > r.bottom || b1.bottom < r.top);
}

void GameObject::Draw()
{
}

void GameObject::Release()
{
}

