#include "PlayerRunningState.h"

#define PLAYER_RUNNING_SPEED 12.0f

PlayerRunningState::PlayerRunningState()
{
	PLAYER->allow[Attacking] = true;
	PLAYER->allow[Jumping] = true;
	PLAYER->allow[Sitting] = true;
	PLAYER->vY = 0;
}

void PlayerRunningState::Update(float deltaTime)
{
	PLAYER->posX = PLAYER->posX + PLAYER->vX * deltaTime;
	PLAYER->posY = PLAYER->posY + PLAYER->vY * deltaTime;
}

void PlayerRunningState::HandleKeyboard(std::map<int, bool> keys)
{
	if (keys[VK_LEFT])
	{
		PLAYER->isReverse = false;
		PLAYER->vX = -PLAYER_RUNNING_SPEED;
	}
	else if (keys[VK_RIGHT])
	{
		PLAYER->isReverse = true;
		PLAYER->vX = PLAYER_RUNNING_SPEED;
	}
	else
	{
		PLAYER->ChangeState(new PlayerStandingState());
	}
}

StateName PlayerRunningState::GetState()
{
	return Running;
}
