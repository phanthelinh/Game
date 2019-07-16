#include "PlayerSpinningState.h"

#define PLAYER_RUNNING_SPEED 80.0f

PlayerSpinningState::PlayerSpinningState()
{
	PLAYER->allow[Attacking] = true;
	PLAYER->allow[Jumping] = false;
	PLAYER->vY = 0;
}

void PlayerSpinningState::Update(float deltaTime)
{
}

void PlayerSpinningState::HandleKeyboard(std::map<int, bool> keys)
{
	PLAYER->isReverse = !PLAYER->isReverse;
	if (GetKeyState('X') < 0)
	{
		PLAYER->LastKeyState[X] = true;
	}
	else
	{
		PLAYER->LastKeyState[X] = false;
	}
}

StateName PlayerSpinningState::GetState()
{
	return Spinning;
}
