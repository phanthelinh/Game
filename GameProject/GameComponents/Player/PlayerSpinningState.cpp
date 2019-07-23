#include "PlayerSpinningState.h"

#define SPINNING_BOOST -40.0f
#define PLAYER_RUNNING_SPEED 8.0f
#define GRAVITY 4.0f

PlayerSpinningState::PlayerSpinningState()
{
	PLAYER->allow[Attacking] = true;
	PLAYER->allow[Jumping] = false;
	PLAYER->vY = SPINNING_BOOST;
	PLAYER->shield->isVisible = false;
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
	if (keys[VK_DOWN])
	{
		PLAYER->ChangeState(OnShield);
	}
	if (!keys['X'])
	{
		PLAYER->LastKeyState[X] = false;
	}
}

StateName PlayerSpinningState::GetState()
{
	return Spinning;
}
