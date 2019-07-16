#include "PlayerFallingState.h"

#define PLAYER_FALLING_SPEED 230.0f
#define PLAYER_RUNNING_SPEED 80.0f
#define GRAVITY 10.0f

PlayerFallingState::PlayerFallingState()
{
	PLAYER->allow[Attacking] = true;
	PLAYER->allow[Jumping] = false;
	PLAYER->vY = PLAYER_FALLING_SPEED;
}

void PlayerFallingState::Update(float deltaTime)
{
	if (PLAYER->vY == 0)
		PLAYER->ChangeState(new PlayerStandingState());
	PLAYER->vY -= GRAVITY;
	PLAYER->posX = PLAYER->posX + PLAYER->vX * deltaTime;
	PLAYER->posY = PLAYER->posY + PLAYER->vY * deltaTime;
}

void PlayerFallingState::HandleKeyboard(std::map<int, bool> keys)
{
	if (keys[VK_LEFT])
	{
		PLAYER->isReverse = true;
		PLAYER->vX = -PLAYER_RUNNING_SPEED;
	}
	if (keys[VK_RIGHT])
	{
		PLAYER->isReverse = false;
		PLAYER->vX = PLAYER_RUNNING_SPEED;
	}
}

StateName PlayerFallingState::GetState()
{
	return Falling;
}
