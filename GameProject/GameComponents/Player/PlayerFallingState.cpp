#include "PlayerFallingState.h"

#define PLAYER_FALLING_SPEED 250.0f
#define PLAYER_RUNNING_SPEED 80.0f
#define GRAVITY 10.0f

PlayerFallingState::PlayerFallingState()
{
	PLAYER->allow[Attacking] = true;
	PLAYER->allow[Jumping] = false;
	//if (PLAYER->PreviousState != Kicking)
		PLAYER->vY += PLAYER_FALLING_SPEED;
}

void PlayerFallingState::Update(float deltaTime)
{
	PLAYER->posX = PLAYER->posX + PLAYER->vX * deltaTime;
	PLAYER->posY = PLAYER->posY + PLAYER->vY * deltaTime;
	PLAYER->vY -= GRAVITY;
	if (PLAYER->vY <= 0)
		PLAYER->ChangeState(new PlayerStandingState());
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
	if (keys['Z'])
	{
		PLAYER->ChangeState(new PlayerKickingState());
	}
	if (GetKeyState('X') < 0)
	{
		PLAYER->LastKeyState[X] = true;
	}
	else
	{
		PLAYER->LastKeyState[X] = false;
	}
}

StateName PlayerFallingState::GetState()
{
	return Falling;
}
