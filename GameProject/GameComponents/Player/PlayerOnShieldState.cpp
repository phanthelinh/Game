#include "PlayerOnShieldState.h"

#define PLAYER_RUNNING_SPEED 8.0f
#define GRAVITY 4.0f

PlayerOnShieldState::PlayerOnShieldState()
{
	PLAYER->allow[Attacking] = true;
	PLAYER->allow[Jumping] = true;
	PLAYER->shield->isVisible = false;
}

void PlayerOnShieldState::Update(float deltaTime)
{
	PLAYER->posX = PLAYER->posX + PLAYER->vX * deltaTime;
	PLAYER->posY = PLAYER->posY + PLAYER->vY * deltaTime;
	PLAYER->vY += GRAVITY;
	if (PLAYER->vY == 0)
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
	if (keys[VK_DOWN])
	{
		PLAYER->ChangeState(Standing);
	}
	if (keys['X'] && PLAYER->allow[Jumping] && !PLAYER->LastKeyState[X])
	{
		PLAYER->LastKeyState[X] = true;
		PLAYER->LastPressTime[X] = deltaTime;
		PLAYER->KeyHoldTime[X] = 0.0f;
		PLAYER->ChangeState(Jumping);
	}
	else
	{
		PLAYER->LastKeyState[X] = false;
		PLAYER->KeyHoldTime[X] = 0.0f;
		PLAYER->LastPressTime[X] = 0.0f;
	}
}

StateName PlayerOnShieldState::GetState()
{
	return OnShield;
}
