#include "Bone.h"
#include <stdlib.h>
#include <time.h>

Bone::Bone()
{
}

Bone::Bone(int x, int y, bool isLeft)
{
	srand(time(NULL));
	posX = x;
	posY = y;
	this->isLeft = isLeft;
	oldX = x;
	oldY = y;
	Tag = GameObjectTypes::BoneObj;
	animObject = new Animation("Resources/enemies/skeleton_weapon_16_16.png", 2, 1, 2);
	accelerateX = rand() % 15 + 70;
	accelerateY = rand() % 9 + 11;
	maxDistance = rand() % 50 + 100;
}

Bone::~Bone()
{
}

void Bone::Update(float deltaTime)
{
	if (isLeft) //throw to the left
	{
		if (oldX - posX <= maxDistance)
		{
			SetVx(-accelerateX);
		}
		else
		{
			SetVx(0);
		}
	}
	else //throw to the right
	{
		if (posX - oldX <= maxDistance)
		{
			SetVx(accelerateX);
		}
		else
		{
			SetVx(0);
		}
	}
	//code for Vy
	if (vY == 0)
	{
		SetVy(BONE_MIN_VY);
	}
	else
	{
		AddVy(accelerateY);
	}
	AddVy(accelerateY);
	if (vY >= 120.0f)
	{
		SetVy(120.0f);
	}
	animObject->Update(deltaTime);
	DynamicObject::Update(deltaTime);
	
}

void Bone::Draw(D3DXVECTOR3 position, D3DXVECTOR3 cameraPosition, RECT sourceRect, D3DXVECTOR3 center)
{
	if (posX < (cameraPosition.x - GlobalVar::GetScreenWidth() / 2) ||
		posX >(cameraPosition.x + GlobalVar::GetScreenWidth() / 2) ||
		posY > (cameraPosition.y + GlobalVar::GetScreenHeight() / 2 - GlobalVar::GetGameUIArea() / 2))
	{
		this->isVisible = false;
	}
	if(isVisible)
		animObject->Draw(D3DXVECTOR3(posX, posY, 0), cameraPosition, RECT(), D3DXVECTOR3(0, 0, 0));
}

void Bone::SetPlayerPosition(D3DXVECTOR3 player)
{
}

Box Bone::getBox()
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

void Bone::OnCollision(GameObject * entity, float deltaTime)
{
}
