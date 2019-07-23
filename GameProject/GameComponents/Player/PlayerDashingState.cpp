#include "PlayerDashingState.h"

#define PLAYER_DASHING_SPEED 25.0f
#define PLAYER_RUNNING_SPEED 8.0f
#define GRAVITY 1.0f

PlayerDashingState::PlayerDashingState()
{
	PLAYER->allow[Attacking] = true;
	PLAYER->allow[Jumping] = true;
	PLAYER->vY = 0;
	if (PLAYER->isReverse == true)
		PLAYER->vX += PLAYER_DASHING_SPEED;
	else
		PLAYER->vX -= PLAYER_DASHING_SPEED;
	PLAYER->shield->isVisible = false;
}

void PlayerDashingState::Update(float deltaTime)
{
	PLAYER->posX = PLAYER->posX + PLAYER->vX * deltaTime;
	PLAYER->posY = PLAYER->posY + PLAYER->vY * deltaTime;
	if (PLAYER->currentAnim->_isFinished)
	{
		PLAYER->ChangeState(Standing);
	}
}

void PlayerDashingState::HandleKeyboard(std::map<int, bool> keys, float deltaTime)
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
		PLAYER->ChangeState(Attacking);
	}
	if (keys['X'] && PLAYER->allow[Jumping] && !PLAYER->LastKeyState[X])
	{
		PLAYER->LastKeyState[X] = true;
		PLAYER->ChangeState(Jumping);
	}
	if (!keys['X'])
	{
		PLAYER->LastKeyState[X] = false;
	}
}

StateName PlayerDashingState::GetState()
{
	return Dashing;
}
