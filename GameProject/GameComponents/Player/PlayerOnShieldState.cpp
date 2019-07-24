#include "PlayerOnShieldState.h"

#define PLAYER_FALLING_SPEED 30.0f
#define GRAVITY 3.0f

PlayerOnShieldState::PlayerOnShieldState()
{
	PLAYER->allow[Attacking] = true;
	PLAYER->allow[Jumping] = false;
	PLAYER->shield->isVisible = false;
}

void PlayerOnShieldState::Update(float deltaTime)
{
	PLAYER->posX = PLAYER->posX + PLAYER->vX * deltaTime;
	PLAYER->posY = PLAYER->posY + PLAYER->vY * deltaTime;
	PLAYER->vY -= GRAVITY;
	if (PLAYER->vY <= 0)
		PLAYER->vY = 0;
}

void PlayerOnShieldState::HandleKeyboard(std::map<int, bool> keys, float deltaTime)
{
	if (keys[VK_LEFT])
	{
		PLAYER->ChangeState(Running);
	}
	if (keys[VK_RIGHT])
	{
		PLAYER->ChangeState(Running);
	}
	if (keys['Z'])
	{
		PLAYER->ChangeState(Attacking);
	}
	if (!keys[VK_DOWN])
	{
		PLAYER->ChangeState(Standing);
	}
	if (!keys['X'])
	{
		PLAYER->LastKeyState[X] = false;
	}
}

StateName PlayerOnShieldState::GetState()
{
	return OnShield;
}
