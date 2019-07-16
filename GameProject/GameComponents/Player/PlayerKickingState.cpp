#include "PlayerKickingState.h"

#define PLAYER_RUNNING_SPEED 80.0f

PlayerKickingState::PlayerKickingState()
{
	PLAYER->allow[Attacking] = true;
	PLAYER->allow[Jumping] = true;
	PLAYER->vY = 0;
}

void PlayerKickingState::Update(float deltaTime)
{
	PLAYER->posX = PLAYER->posX + PLAYER->vX * deltaTime;
	PLAYER->posY = PLAYER->posY + PLAYER->vY * deltaTime;
}

void PlayerKickingState::HandleKeyboard(std::map<int, bool> keys)
{
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
			PLAYER->ChangeState(new PlayerStandingState());
		}
	}
}

StateName PlayerKickingState::GetState()
{
	return Kicking;
}
