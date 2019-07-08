#include "Bullet.h"

Bullet::Bullet()
{
}

Bullet::Bullet(int x, int y, bool isLeft)
{
	posX = x;
	posY = y;
	this->isLeft = isLeft;
	animObject = new Animation("Resources/enemies/bullet_7_6.png", 1, 1, 1);
	Tag = GameObjectTypes::BulletObj;
}

Bullet::~Bullet()
{
}

void Bullet::Update(float deltaTime)
{
	if (isLeft)
	{
		SetVx(-ACCELERATE_X);
	}
	else
	{
		SetVx(ACCELERATE_X);
	}
	DynamicObject::Update(deltaTime);
}

void Bullet::Draw(D3DXVECTOR3 position, D3DXVECTOR3 cameraPosition, RECT sourceRect, D3DXVECTOR3 center)
{
	if(isVisible)
		animObject->Draw(D3DXVECTOR3(posX, posY, 0), cameraPosition, RECT(), D3DXVECTOR3(0,0,0));
}

void Bullet::SetPlayerPosition(D3DXVECTOR3 player)
{
}

Box Bullet::getBox()
{
	Box b;
	b.left = GetPosition().x;
	b.top = GetPosition().y;
	b.right = b.left + animObject->GetWidth();
	b.bottom = b.top + animObject->GetHeight();
	b.vx = GetVx();
	b.vy = GetVy();
	return b;
}

void Bullet::OnCollision(GameObject * entity, float deltaTime)
{
	if (entity->Tag = GameObject::WhipObj)
	{
		GameCollision * collision = new GameCollision();

		if (collision->isCollide(entity->getBox(), this->getBox()))
		{
			this->isVisible = false;
		}
	}
}
