#include "PlayerSpinningState.h"

#define SPINNING_BOOST -140.0f
#define PLAYER_RUNNING_SPEED 80.0f
#define GRAVITY 10.0f

PlayerSpinningState::PlayerSpinningState()
{
	PLAYER->allow[Attacking] = true;
	PLAYER->allow[Jumping] = false;
	PLAYER->vY += SPINNING_BOOST;
}

void PlayerSpinningState::Update(float deltaTime)
{
	PLAYER->posX = PLAYER->posX + PLAYER->vX * deltaTime;
	PLAYER->posY = PLAYER->posY + PLAYER->vY * deltaTime;
	PLAYER->vY += GRAVITY;
	if (PLAYER->vY == 0)
		PLAYER->ChangeState(Falling);
}

void PlayerSpinningState::HandleKeyboard(std::map<int, bool> keys, float deltaTime)
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
	if (GetKeyState('X') >= 0)
	{
		PLAYER->LastKeyState[X] = false;
		PLAYER->KeyHoldTime[X] = 0.0f;
	}
}

StateName PlayerSpinningState::GetState()
{
	return Spinning;
}
