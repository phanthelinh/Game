#include "PlayerJumpingState.h"

#define PLAYER_JUMPING_SPEED -250.0f
#define PLAYER_RUNNING_SPEED 80.0f
#define GRAVITY 10.0f

PlayerJumpingState::PlayerJumpingState()
{
	PLAYER->allow[Attacking] = true;
	PLAYER->allow[Jumping] = false;
	PLAYER->vY += PLAYER_JUMPING_SPEED;
}

void PlayerJumpingState::Update(float deltaTime)
{
	PLAYER->posX = PLAYER->posX + PLAYER->vX * deltaTime;
	PLAYER->posY = PLAYER->posY + PLAYER->vY * deltaTime;
	PLAYER->vY += GRAVITY;
	if (PLAYER->vY >= 0)
		PLAYER->ChangeState(Falling);
}

void PlayerJumpingState::HandleKeyboard(std::map<int, bool> keys, float deltaTime)
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
		PLAYER->ChangeState(Kicking);
	}
	if (GetKeyState('X') < 0)
	{
		if (PLAYER->LastKeyState[X] == true)
		{
			PLAYER->KeyHoldTime[X] += deltaTime - PLAYER->LastPressTime[X];
			PLAYER->LastPressTime[X] = deltaTime;
			if (PLAYER->KeyHoldTime[X] >= 0.016)
			{
				PLAYER->ChangeState(Spinning);
			}
		}	
		PLAYER->LastKeyState[X] = true;
	}
	else
	{
		PLAYER->LastKeyState[X] = false;
		PLAYER->KeyHoldTime[X] = 0.0f;
	}
}

StateName PlayerJumpingState::GetState()
{
	return Jumping;
}
