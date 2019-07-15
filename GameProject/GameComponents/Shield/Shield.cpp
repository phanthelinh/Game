#include "Shield.h"

#define SHIELD_FLYING_SPEED_MIN -70.0f
#define SHIELD_FLYING_SPEED_MAX 70.0f
#define MAX_DISTANCE_SHIELD_FLYING (GLOBAL->g_ScreenWidth/2)

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
		shield->_sourceRect = { 51,0,59,16 };
		shield->_textureWidth = width = 8;
		shield->_textureHeight = height = 16;
		break;
	case Shielded:
		shield->_sourceRect = { 27,0,43,16 };
		shield->_textureWidth = width = 16;
		shield->_textureHeight = height = 16;
		break;
	case Shield_Upward:
		shield->_sourceRect = { 2,2,18,12 };
		shield->_textureWidth = width = 16;
		shield->_textureHeight = height = 10;
		break;
	case Flying:
		shield->_sourceRect = { 2,2,18,12 };
		shield->_textureWidth = width = 16;
		shield->_textureHeight = height = 10;
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
		if (!playerReverse) //face to left
		{
			_translationToPlayer = { -13,-6,0 };
		}
		else
		{
			_translationToPlayer = { 13,-6,0 };
		}
		break;
	case Shielded:
		_translationToPlayer = { 0,0,0 };
		break;
	case Shield_Upward:
		if (!playerReverse) //face to left
		{
			_translationToPlayer = { -10,-10,0 };
		}
		else
		{
			_translationToPlayer = { 10,-20,0 };
		}
		break;
	case Flying:
		if (!playerReverse)
		{
			vX = SHIELD_FLYING_SPEED_MIN;
			if (spriteIndex == 0)
			{
				_translationToPlayer = { 24,-12,0 };
			}
			else
			{
				_translationToPlayer = { -34,3,0 };
				startingPos = GetPosition() + _translationToPlayer;
			}
		}
		else
		{
			vX = SHIELD_FLYING_SPEED_MAX;
			if (spriteIndex == 0)
			{
				_translationToPlayer = { -24,-12,0 };
			}
			else
			{
				_translationToPlayer = { 34,3,0 };
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
		if (isReverse)
		{
			vX += 10;
		}
		else
		{
			vX -= 10;
		}
	}
}
