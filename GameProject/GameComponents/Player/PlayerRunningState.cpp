#include "PlayerRunningState.h"

#define PLAYER_RUNNING_SPEED 80.0f

PlayerRunningState::PlayerRunningState()
{
	PLAYER->allow[Attacking] = true;
	PLAYER->allow[Jumping] = true;
	PLAYER->vY = 0;
}

void PlayerRunningState::Update(float deltaTime)
{
	PLAYER->posX = PLAYER->posX + PLAYER->vX * deltaTime;
	PLAYER->posY = PLAYER->posY + PLAYER->vY * deltaTime;
}

void PlayerRunningState::HandleKeyboard(std::map<int, bool> keys, float deltaTime)
{
	if (keys['X'] && PLAYER->allow[Jumping] && !PLAYER->LastKeyState[X])
	{
		PLAYER->LastKeyState[X] = true;
		PLAYER->LastPressTime[X] = deltaTime;
		PLAYER->KeyHoldTime[X] = 0.0f;
		PLAYER->ChangeState(Jumping);
	}
	if (keys[VK_LEFT])
	{
		PLAYER->isReverse = true;
		PLAYER->vX = -PLAYER_RUNNING_SPEED;
	}
	else
	{
		if (keys[VK_RIGHT])
		{
			PLAYER->isReverse = false;
			PLAYER->vX = PLAYER_RUNNING_SPEED;
		}
		else
		{
			PLAYER->ChangeState(Standing);
		}
	}
	if (GetKeyState('X') >= 0)
	{
		PLAYER->LastKeyState[X] = false;
		PLAYER->KeyHoldTime[X] = 0.0f;
	}
}

StateName PlayerRunningState::GetState()
{
	return Running;
}
