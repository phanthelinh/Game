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
	PLAYER->posX = PLAYER->posX + PLAYER->vX * deltaTime;
	PLAYER->posY = PLAYER->posY + PLAYER->vY * deltaTime;
}

void PlayerSpinningState::HandleKeyboard(std::map<int, bool> keys)
{
	PLAYER->isReverse = !PLAYER->isReverse;
	PLAYER->vX = -PLAYER_RUNNING_SPEED;
}

StateName PlayerSpinningState::GetState()
{
	return Spinning;
}
