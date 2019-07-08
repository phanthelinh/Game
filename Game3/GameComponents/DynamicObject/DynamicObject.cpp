#include "DynamicObject.h"

DynamicObject::DynamicObject()
{
	animObject = NULL;
	animHit = new Animation("Resources/effects/hit_10_10.png", 1, 1, 1);
	animDeath = new Animation("Resources/effects/hiteffect_16_16.png", 2, 1, 2);

	timeDead = timeHit = 0;
}

DynamicObject::DynamicObject(float x, float y)
{
	animObject = NULL;
}

DynamicObject::~DynamicObject()
{
	Memory::SafeDelete(animObject);
	Memory::SafeDelete(animHit);
	Memory::SafeDelete(animDeath);
}

void DynamicObject::SetVx(float vx)
{
	vX = vx;
}

float DynamicObject::GetVx()
{
	return vX;
}

void DynamicObject::AddVx(float vx)
{
	SetVx(GetVx() + vx);
}

void DynamicObject::SetVy(float vy)
{
	vY = vy;
}

float DynamicObject::GetVy()
{
	return vY;
}

void DynamicObject::AddVy(float vy)
{
	SetVy(GetVy() + vy);
}


void DynamicObject::Update(float deltaTime)
{
	posX = posX + deltaTime * vX;
	posY = posY + deltaTime * vY;

	animHit->Update(deltaTime);
	animDeath->Update(deltaTime);
	//check for disable drawing
	float now = GetTickCount();
	if (isHurted)
	{
		if (timeHit == 0)
		{
			timeHit = now;
		}
		if ((now - timeHit) / 1000.0f >= 0.2f)
		{
			isHurted = false;
			timeHit = 0;
		}
	}

	if (isDead)
	{
		if (timeDead == 0)
		{
			timeDead = now;
		}
		if ((now - timeDead) / 1000.0f >= 1.0f)
		{
			isDead = false;
			timeDead = 0;
		}
	}
}

void DynamicObject::Draw(D3DXVECTOR3 position, D3DXVECTOR3 cameraPosition, RECT sourceRect, D3DXVECTOR3 center)
{
	if (isHurted)
		animHit->Draw(position, cameraPosition, sourceRect, center);
	if(isDead)
		animDeath->Draw(position, cameraPosition, sourceRect, center);
}

void DynamicObject::GravityAffect(float deltaTime)
{
	vY += GRAVITY *deltaTime;
}

