#include "PlayerFallingState.h"

#define PLAYER_FALLING_SPEED 250.0f
#define PLAYER_RUNNING_SPEED 80.0f
#define GRAVITY 10.0f

PlayerFallingState::PlayerFallingState()
{
	PLAYER->allow[Attacking] = true;
	PLAYER->allow[Jumping] = false;
	//if (PLAYER->PreviousState != Kicking)
	if (PLAYER->PreviousState == Spinning)
	{
		PLAYER->vY += PLAYER_FALLING_SPEED + 100.0f;
	}
	else
	{
		PLAYER->vY += PLAYER_FALLING_SPEED;
	}
	
	
}

void PlayerFallingState::Update(float deltaTime)
{
	PLAYER->posX = PLAYER->posX + PLAYER->vX * deltaTime;
	PLAYER->posY = PLAYER->posY + PLAYER->vY * deltaTime;
	PLAYER->vY -= GRAVITY;
	if (PLAYER->vY == 0)
		PLAYER->ChangeState(Standing);
}

void PlayerFallingState::HandleKeyboard(std::map<int, bool> keys, float deltaTime)
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
	if (GetKeyState('X') >= 0)
	{
		PLAYER->LastKeyState[X] = false;
		PLAYER->KeyHoldTime[X] = 0.0f;
	}
}

StateName PlayerFallingState::GetState()
{
	return Falling;
}
