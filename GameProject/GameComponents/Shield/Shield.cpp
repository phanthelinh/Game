#include "Shield.h"

#define SHIELD_FLYING_SPEED_MIN -30.0f
#define SHIELD_FLYING_SPEED_MAX  30.0f


Shield::Shield()
{
	shield = new Sprite("Resources/shield/shield_60_16.png");
	SetState(ShieldState::Normal);
	tag = Tag::ShieldTag;
	isDead = false;
	isVisible = true;
	playerPos = { 0,0,0 };
	shieldPower = 1;
}

void Shield::SetState(ShieldState state)
{
	curState = state;
	switch (curState)
	{
	case Normal:
	case Normal_Sit:
	case OnKick:
		shield->_sourceRect = { 2,0,10,16 };
		shield->_textureWidth = width = 8;
		shield->_textureHeight = height = 16;
		vX = vY = 0;
		break;
	case Shielded:
	case OnJump:
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
			vX = 50.0f;
		}
		else
		{
			vX = -50.0f;
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
	case OnJump:
		if (playerReverse) //face to right
		{
			_translationToPlayer = { -4, -6, 0 };
		}
		else
		{
			_translationToPlayer = { 4, -6, 0 };
		}
		SetPosition(GetPosition() + _translationToPlayer);
		break;
	case OnKick:
		if (playerReverse) //face to right
		{
			_translationToPlayer = { -17, -1, 0 };
		}
		else
		{
			_translationToPlayer = { 17, 1, 0 };
		}
		SetPosition(GetPosition() + _translationToPlayer);
		break;
	case Normal:
		if (playerReverse) //face to right
		{
			_translationToPlayer = { 13,-4,0 };
		}
		else
		{
			_translationToPlayer = { -13,-4,0 };
		}
		SetPosition(GetPosition() + _translationToPlayer);
		break;
	case Normal_Sit:
		if (playerReverse) //face to right
		{
			_translationToPlayer = { 13,5,0 };
		}
		else
		{
			_translationToPlayer = { -13,5,0 };
		}
		SetPosition(GetPosition() + _translationToPlayer);
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
		SetPosition(GetPosition() + _translationToPlayer);
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
			}
			startingPos = GetPosition() + _translationToPlayer;
			SetPosition(startingPos);
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
			}
			startingPos = GetPosition() + _translationToPlayer;
			SetPosition(startingPos);
		}
		break;
	default:
		break;
	}
}

void Shield::Draw()
{
	Draw(GetPosition(), CAMERA->camPosition);

}

void Shield::Draw(D3DXVECTOR3 position, D3DXVECTOR3 cameraPosition, RECT sourceRect, D3DXVECTOR3 center)
{
	if (curState == ShieldState::OnKick)
		shield->_isFlipHor = !isReverse;
	else
		shield->_isFlipHor = isReverse;
	if (isVisible == true)
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
			vX -= 5;
			vX = vX <= SHIELD_FLYING_SPEED_MIN ? SHIELD_FLYING_SPEED_MIN : vX;
			if (vX <= 0)
			{
				if (posY > playerPos.y && (startingPos.y-1) > playerPos.y)
				{
					vY -= 5.0f;
				}
				else if (posY < playerPos.y && (startingPos.y+1) < playerPos.y)
				{
					vY += 5.0f;
				}
				else 
				{
					posY = playerPos.y;
					vY = 0;
				}
			}
		}
		else
		{
			vX += 5;
			vX = vX >= SHIELD_FLYING_SPEED_MAX ? SHIELD_FLYING_SPEED_MAX : vX;
			if (vX >= 0)
			{
				if (posY > playerPos.y && (startingPos.y - 1) > playerPos.y)
				{
					vY -= 5.0f;
				}
				else if (posY < playerPos.y && (startingPos.y + 1) < playerPos.y)
				{
					vY += 5.0f;
				}
				else
				{
					posY = playerPos.y;
					vY = 0;
				}
			}
		}
		//check for whether shield goes over player or not
		if (isReverse)
		{
			if (posX <= CAMERA->GetBound().left)
			{
				vX = SHIELD_FLYING_SPEED_MIN;
				isReverse = !isReverse;
			}
		}
		else
		{
			if (posX >= CAMERA->GetBound().right)
			{
				vX = SHIELD_FLYING_SPEED_MAX;
				isReverse = !isReverse;
			}
		}
	}
}

BoundingBox Shield::GetBoundingBox()
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
