#include "PlayerJumpingState.h"

#define PLAYER_JUMPING_SPEED -250.0f
#define PLAYER_RUNNING_SPEED 80.0f
#define GRAVITY 10.0f

PlayerJumpingState::PlayerJumpingState()
{
	PLAYER->allow[Attacking] = true;
	PLAYER->allow[Jumping] = false;
	PLAYER->vY = PLAYER_JUMPING_SPEED;
}

void PlayerJumpingState::Update(float deltaTime)
{
	PLAYER->posX = PLAYER->posX + PLAYER->vX * deltaTime;
	PLAYER->posY = PLAYER->posY + PLAYER->vY * deltaTime;
	PLAYER->vY += GRAVITY;
	if (PLAYER->vY == 0)
		PLAYER->ChangeState(new PlayerFallingState());
}

void PlayerJumpingState::HandleKeyboard(std::map<int, bool> keys)
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
	if (GetKeyState('X') < 0)
	{
		PLAYER->LastKeyState[X] = true;
	}
	else
	{
		PLAYER->LastKeyState[X] = false;
	}
}

StateName PlayerJumpingState::GetState()
{
	return Jumping;
}
