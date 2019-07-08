#include "GameObject.h"



GameObject::GameObject()
{
	isVisible = true;
	reviveTime = 0;
	invicibleTime = 0;
}

GameObject::GameObject(float x, float y)
{
	isVisible = true;
	posX = x;
	posY = y;
	reviveTime = 0;
	invicibleTime = 0;
}

GameObject::~GameObject()
{

}

GameObject::GameObjectTypes GameObject::getTag()
{
	return Tag;
}

bool GameObject::IsLeft()
{
	return false;
}

RECT GameObject::GetBoundTopLeft()
{
	RECT bound;
	bound.top = this->GetPosition().x;
	bound.left = this->GetPosition().y;
	bound.right = posX + width;
	bound.bottom = posY + height;
	return bound;
}

RECT GameObject::GetBound()
{
	RECT bound;
	//lay diem center 0,0
	bound.left = posX;
	bound.top = posY;
	bound.right = posX + width;
	bound.bottom = posY + height;

	return bound;
}

void GameObject::SetPosition(int x, int y)
{
	SetPosition(D3DXVECTOR2(x, y));
}

void GameObject::SetPosition(D3DXVECTOR3 pos)
{
	posX = pos.x;
	posY = pos.y;
	OnSetPosition(pos);
}

void GameObject::SetPosition(D3DXVECTOR2 pos)
{
	SetPosition(D3DXVECTOR3(pos));
}

D3DXVECTOR3 GameObject::GetPosition()
{
	return D3DXVECTOR3(posX,posY,0);
}

void GameObject::AddPosition(int x, int y)
{
	AddPosition(D3DXVECTOR3(x, y, 0));
}

void GameObject::AddPosition(D3DXVECTOR3 pos)
{
	SetPosition(GetPosition() + pos);
}

void GameObject::AddPosition(D3DXVECTOR2 pos)
{
	AddPosition(D3DXVECTOR3(pos));
}

void GameObject::SetWidth(int w)
{
	width = w;
}

int GameObject::GetWidth()
{
	return width;
}

void GameObject::SetHeight(int h)
{
	height = h;
}

int GameObject::GetHeight()
{
	return height;
}


void GameObject::Update(float deltaTime)
{
}

void GameObject::Draw(D3DXVECTOR3 position, D3DXVECTOR3 cameraPosition, RECT sourceRect, D3DXVECTOR3 center)
{
}

void GameObject::OnSetPosition(D3DXVECTOR3 pos)
{
}

void GameObject::setBox(float x, float y, float width, float height, float vx, float vy)
{
	box.left = x;
	box.top = y;
	box.right = x + width;
	box.bottom = y + height;
	box.vx = vx;
	box.vy = vy;
}

Box GameObject::getBox()
{
	Box b;
	b.left = posX;
	b.top = posY;
	b.right = b.left + width;
	b.bottom = b.top + height;
	b.vx = b.vy = 0;
	return b;
}

void GameObject::SetVisible(bool _isVisible)
{
	this->isVisible = _isVisible;
}

void GameObject::SetPlayerPosition(D3DXVECTOR3 player)
{
}

float GameObject::getReviveTime()
{
	return reviveTime;
}

void GameObject::OpeningTheDoor(int flag)
{
}

void GameObject::OnCollision(GameObject * entity, float deltaTime)
{
}

GameObject * GameObject::GetWeaponObject()
{
	return nullptr;
}

GameObject * GameObject::GetItems()
{
	return nullptr;
}
