#include "Enemy.h"

Enemy::Enemy():GameObject()
{
	tag = Tag::EnemyTag;
}

Enemy::Enemy(float posX, float posY, float width, float height):GameObject(posX,posY,width,height,Tag::EnemyTag)
{
}

Enemy::Enemy(RECT r):GameObject(r)
{
	tag = Tag::EnemyTag;
}

void Enemy::OnCollision(GameObject * object, float deltaTime)
{
}

RECT Enemy::GetBound()
{
	RECT r;
	r.left = posX;
	r.top = posY;
	r.right = r.left + width;
	r.bottom = r.top + height;
	return r;
}

BoundingBox Enemy::GetBoundingBox()
{
	BoundingBox b;
	b.left = posX;
	b.top = posY;
	b.right = b.left + width;
	b.bottom = b.top + height;
	b.vX = vX;
	b.vY = vY;
	return b;
}

void Enemy::Update(float deltaTime)
{
}

void Enemy::Draw()
{
}

void Enemy::Release()
{
}

