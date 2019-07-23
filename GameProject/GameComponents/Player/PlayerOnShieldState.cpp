#include "PlayerOnShieldState.h"

#define PLAYER_FALLING_SPEED 100.0f
#define PLAYER_RUNNING_SPEED 8.0f

PlayerOnShieldState::PlayerOnShieldState()
{
	PLAYER->allow[Attacking] = true;
	PLAYER->allow[Jumping] = false;
	PLAYER->shield->isVisible = false;
	int a = PLAYER->vY;
	if (a % 2 == 0)
	{
		Gravity = 4;
	}
	else
	{
		Gravity = 1;
	}
	PLAYER->vY = PLAYER_FALLING_SPEED + -PLAYER->vY;
	
}

void PlayerOnShieldState::Update(float deltaTime)
{
	PLAYER->posX = PLAYER->posX + PLAYER->vX * deltaTime;
	PLAYER->posY = PLAYER->posY + PLAYER->vY * deltaTime;
	PLAYER->vY -= Gravity;
	if (PLAYER->vY <= 0)
	{
		PLAYER->vY = 0;
	}
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
	if (keys['X'] && PLAYER->allow[Jumping] && !PLAYER->LastKeyState[X])
	{
		PLAYER->LastKeyState[X] = true;
		PLAYER->ChangeState(Jumping);
	}
	else
	{
		PLAYER->LastKeyState[X] = false;
	}
}

StateName PlayerOnShieldState::GetState()
{
	return OnShield;
}
