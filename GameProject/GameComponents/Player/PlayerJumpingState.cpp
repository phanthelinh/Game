#include "PlayerJumpingState.h"

#define PLAYER_JUMPING_SPEED -40.0f
#define PLAYER_RUNNING_SPEED 8.0f
#define GRAVITY 4.0f

PlayerJumpingState::PlayerJumpingState()
{
	PLAYER->allow[Attacking] = true;
	PLAYER->allow[Jumping] = false;
	PLAYER->vY += PLAYER_JUMPING_SPEED;
	PLAYER->shield->isVisible = false;
}

void PlayerJumpingState::Update(float deltaTime)
{
	PLAYER->posX = PLAYER->posX + PLAYER->vX * deltaTime;
	PLAYER->posY = PLAYER->posY + PLAYER->vY * deltaTime;
	PLAYER->vY += GRAVITY;
	if (PLAYER->vY >= 0 & PLAYER->LastKeyState[X] == false)
	{
		PLAYER->ChangeState(Falling);
	}
}

void PlayerJumpingState::HandleKeyboard(std::map<int, bool> keys, float deltaTime)
{
	if (keys[VK_LEFT])
	{
		PLAYER->isReverse = false;
		PLAYER->vX = -PLAYER_RUNNING_SPEED;
	}
	if (keys[VK_RIGHT])
	{
		PLAYER->isReverse = true;
		PLAYER->vX = PLAYER_RUNNING_SPEED;
	}
	if (keys['Z'])
	{
		PLAYER->ChangeState(Kicking);
	}
	if (keys['X'])
	{
		if (PLAYER->vY == 0)
		{
			PLAYER->ChangeState(Spinning);
		}
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
