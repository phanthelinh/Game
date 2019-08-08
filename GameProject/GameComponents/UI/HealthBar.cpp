#include "HealthBar.h"
#include "../Player/Player.h"

#define X_OFFSET 20
#define Y_OFFSET -200

HealthBar::HealthBar()
{
	healthbarsprite = new Sprite("Resources/UI/HealthBar.png");
	isDead = false;
	isVisible = true;
	SetState(HB1);
	GRID->AddObject(this);
	
}

void HealthBar::SetState(HBState state)
{
	curState = state;
	switch (curState)
	{
		case HB1:
		{
			healthbarsprite->_sourceRect = { 0, 32, 8, 8 };
			healthbarsprite->_textureWidth = width = 8;
			healthbarsprite->_textureHeight = height = 8;
			break;
		}
		case HB2:
		{
			healthbarsprite->_sourceRect = { 8, 24, 8, 8 };
			healthbarsprite->_textureWidth = width = 8;
			healthbarsprite->_textureHeight = height = 8;
			break;
		}
		case HB3:
		{
			healthbarsprite->_sourceRect = { 16, 16, 8, 8 };
			healthbarsprite->_textureWidth = width = 8;
			healthbarsprite->_textureHeight = height = 8;
			break;
		}
		case HB4:
		{
			healthbarsprite->_sourceRect = { 24, 8, 8, 8 };
			healthbarsprite->_textureWidth = width = 8;
			healthbarsprite->_textureHeight = height = 8;
			break;
		}
		case HB5:
		{
			healthbarsprite->_sourceRect = { 32, 0, 8, 8 };
			healthbarsprite->_textureWidth = width = 8;
			healthbarsprite->_textureHeight = height = 8;
			break;
		}
	}
}


void HealthBar::Draw()
{
	Draw(GetPosition(), CAMERA->camPosition);
}

void HealthBar::Draw(D3DXVECTOR3 position, D3DXVECTOR3 cameraPosition, RECT sourceRect, D3DXVECTOR3 center)
{
	if (isVisible == true)
		healthbarsprite->Draw(position, cameraPosition, sourceRect, center);
}

void HealthBar::Update(float deltaTime)
{
	posX = CAMERA->GetBound().left + X_OFFSET;
	posY = CAMERA->GetBound().top + Y_OFFSET;

	if (PLAYER->health / 20 >= 5)
	{
		SetState(HB5);
	}
	else if (PLAYER->health / 20 >= 4)
	{
		SetState(HB4);
	}
	else if (PLAYER->health / 20 >= 3)
	{
		SetState(HB3);
	}
	else if (PLAYER->health / 20 >= 2)
	{
		SetState(HB2);
	}
	else
	{
		SetState(HB1);
	}
}

BoundingBox HealthBar::GetBoundingBox()
{
	BoundingBox bound;

	bound.left = posX - width/2;
	bound.top = posY - height/2;
	bound.right = posX + width;
	bound.bottom = posY + height;
	bound.vX = this->vX;
	bound.vY = this->vY;

	return bound;
}
