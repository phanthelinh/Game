#include "Shield.h"

#define SHIELD_FLYING_SPEED_MIN -70.0f
#define SHIELD_FLYING_SPEED_MAX  70.0f


Shield::Shield()
{
	shield = new Sprite("Resources/shield/shield_60_16.png");
	SetState(ShieldState::Normal);
}

void Shield::SetState(ShieldState state)
{
	curState = state;
	switch (curState)
	{
	case Normal:
		shield->_sourceRect = { 2,0,10,16 };
		shield->_textureWidth = width = 8;
		shield->_textureHeight = height = 16;
		vX = vY = 0;
		break;
	case Shielded:
		shield->_sourceRect = { 18,0,34,16 };
		shield->_textureWidth = width = 16;
		shield->_textureHeight = height = 16;
		vX = vY = 0;
		break;
	case Shield_Upward:
		shield->_sourceRect = { 42,2,58,12 };
		shield->_textureWidth = width = 16;
		shield->_textureHeight = height = 10;
		vX = vY = 0;
		break;
	case Flying:
		shield->_sourceRect = { 42,2,58,12 };
		shield->_textureWidth = width = 16;
		shield->_textureHeight = height = 10;
		if (isReverse)
		{
			vX = SHIELD_FLYING_SPEED_MAX;
		}
		else
		{
			vX = SHIELD_FLYING_SPEED_MIN;
		}
		break;
	default:
		break;
	}
}

void Shield::SetTranslationToPlayer(bool playerReverse, ShieldState state, int spriteIndex)
{
	switch (state)
	{
	case Normal:
		if (playerReverse) //face to right
		{
			_translationToPlayer = { 13,-6,0 };
		}
		else
		{
			_translationToPlayer = { -13,-6,0 };
		}
		break;
	case Shielded:
		_translationToPlayer = { 0,0,0 };
		break;
	case Shield_Upward:
		if (playerReverse) //face to right
		{
			_translationToPlayer = { 5,-18,0 };
		}
		else
		{
			_translationToPlayer = { -5,-18,0 };
		}
		break;
	case Flying:
		if (playerReverse)//face to right
		{
			
			if (spriteIndex == 0)
			{
				_translationToPlayer = { -25,-13,0 };
			}
			else
			{
				_translationToPlayer = { 31,0,0 };
				startingPos = GetPosition() + _translationToPlayer;
			}
		}
		else
		{
			if (spriteIndex == 0)
			{
				_translationToPlayer = { 25,-13,0 };
			}
			else
			{
				_translationToPlayer = { -31,0,0 };
				startingPos = GetPosition() + _translationToPlayer;
			}
		}
		break;
	default:
		break;
	}
}

void Shield::Draw()
{
	Draw(GetPosition() + _translationToPlayer, CAMERA->camPosition);

}

void Shield::Draw(D3DXVECTOR3 position, D3DXVECTOR3 cameraPosition, RECT sourceRect, D3DXVECTOR3 center)
{
	shield->_isFlipHor = isReverse;
	shield->Draw(position, cameraPosition, sourceRect, center);
}

void Shield::Update(float deltaTime)
{
	if (curState == ShieldState::Flying)
	{
		posX = posX + vX * deltaTime;
		posY = posY + vY * deltaTime;
		//set reverse velocity
		if (isReverse) //face to right
		{
			vX -= 10;
			vX = vX <= SHIELD_FLYING_SPEED_MIN ? SHIELD_FLYING_SPEED_MIN : vX;
		}
		else
		{
			vX += 10;
			vX = vX >= SHIELD_FLYING_SPEED_MAX ? SHIELD_FLYING_SPEED_MAX : vX;
		}
	}
}
