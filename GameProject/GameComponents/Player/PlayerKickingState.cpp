#include "PlayerKickingState.h"

#define PLAYER_RUNNING_SPEED 80.0f
#define GRAVITY 10.0f

PlayerKickingState::PlayerKickingState()
{
	PLAYER->allow[Attacking] = true;
	PLAYER->allow[Jumping] = false;
}

void PlayerKickingState::Update(float deltaTime)
{
	PLAYER->posX = PLAYER->posX + PLAYER->vX * deltaTime;
	PLAYER->posY = PLAYER->posY + PLAYER->vY * deltaTime;
	if (PLAYER->PreviousState == Jumping)
	{
		PLAYER->vY += GRAVITY;
		if (PLAYER->vY >= 0)
			PLAYER->ChangeState(new PlayerFallingState());
	}
	else
	{
		PLAYER->vY -= GRAVITY;
		if (PLAYER->vY <= 0)
			PLAYER->ChangeState(new PlayerStandingState());
	}
	/*if (PLAYER->currentAnim->_curIndex == PLAYER->currentAnim->_totalFrames - 1)
	{
		if (PLAYER->PreviousState == Jumping)
			PLAYER->ChangeState(new PlayerJumpingState());
		else
			PLAYER->ChangeState(new PlayerFallingState());
	}*/
}

void PlayerKickingState::HandleKeyboard(std::map<int, bool> keys)
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

StateName PlayerKickingState::GetState()
{
	return Kicking;
}
