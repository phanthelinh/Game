#include "PlayerKickingState.h"

#define PLAYER_RUNNING_SPEED 8.0f
#define GRAVITY 4.0f

PlayerKickingState::PlayerKickingState()
{
	PLAYER->allow[Attacking] = true;
	PLAYER->allow[Jumping] = false;
	PLAYER->shield->isVisible = false;
}

void PlayerKickingState::Update(float deltaTime)
{
	PLAYER->posX = PLAYER->posX + PLAYER->vX * deltaTime;
	PLAYER->posY = PLAYER->posY + PLAYER->vY * deltaTime;
	if (PLAYER->PreviousState == Jumping)
	{
		PLAYER->vY += GRAVITY;
		if (PLAYER->vY >= 0)
			PLAYER->ChangeState(Falling);
	}
	else
	{
		PLAYER->vY -= GRAVITY;
		if (PLAYER->vY <= 0)
			PLAYER->ChangeState(Standing);
	}
	/*if (PLAYER->currentAnim->_curIndex == PLAYER->currentAnim->_totalFrames - 1)
	{
		if (PLAYER->PreviousState == Jumping)
			PLAYER->ChangeState(new PlayerJumpingState());
		else
			PLAYER->ChangeState(new PlayerFallingState());
	}*/
}

void PlayerKickingState::HandleKeyboard(std::map<int, bool> keys, float deltaTime)
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
	if (!keys['X'])
	{
		PLAYER->LastKeyState[X] = false;
		PLAYER->KeyHoldTime[X] = 0.0f;
		PLAYER->LastPressTime[X] = 0.0f;
	}
}

StateName PlayerKickingState::GetState()
{
	return Kicking;
}
