#include "Explode.h"

Explode* Explode::instance = nullptr;

Explode::Explode()
{
	explode = new Animation("Resources/effect/explode.png", 3, 1, 3, false, 0.5);
	isStart = false;
}

Explode * Explode::GetInstance()
{
	if (instance == nullptr)
		instance = new Explode();
	return instance;
}

void Explode::ExplodeAt(int x, int y)
{
	ExplodeAt(D3DXVECTOR3(x, y, 0));
}

void Explode::ExplodeAt(D3DXVECTOR3 postion)
{
	posX = postion.x;
	posY = postion.y;
	if (isStart)
	{
		isStart = false;
	}
	isStart = true;
}

void Explode::Update(float deltaTime)
{
	if (isStart)
	{
		explode->Update(deltaTime);
	}
	if (explode->_isFinished)
	{
		isStart = false;
		explode->ResetAnim();
	}
}

void Explode::Draw()
{
	if (isStart)
	{
		explode->Draw(D3DXVECTOR3(posX, posY, 0), CAMERA->camPosition);
	}
}

void Explode::Release()
{
	if (explode != nullptr)
		delete explode;
}
