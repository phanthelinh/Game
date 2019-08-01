#include "PlayerWaterRun.h"

#define PLAYER_RUNNING_SPEED 5.5f

PlayerWaterRun::PlayerWaterRun()
{
	PLAYER->allow[Running] = true;
	PLAYER->allow[Jumping] = true;
	PLAYER->allow[Attacking] = PLAYER->allow[Attacking_Shield]=false;
	PLAYER->allow[Sitting] = false;
	PLAYER->shield->isVisible = false;
}

void PlayerWaterRun::Update(float deltaTime)
{
	PLAYER->posX += PLAYER->vX * deltaTime;
}

void PlayerWaterRun::HandleKeyboard(std::map<int, bool> keys, float deltaTime)
{
	if (keys[VK_RIGHT])
	{
		PLAYER->isReverse = true;
		PLAYER->vX = PLAYER_RUNNING_SPEED;
	}
	if (keys[VK_LEFT])
	{
		PLAYER->isReverse = false;
		PLAYER->vX = -PLAYER_RUNNING_SPEED;
	}
	else
	{
		PLAYER->ChangeState(WaterStand);
	}
	if (keys['X'] && PLAYER->allow[Jumping] && !PLAYER->LastKeyState[X])
	{
		PLAYER->isOnWater = false;
		PLAYER->LastKeyState[X] = true;
		PLAYER->ChangeState(Jumping);
	}
	if (!keys['X'])
	{
		PLAYER->LastKeyState[X] = false;
	}
}

StateName PlayerWaterRun::GetState()
{
	return StateName::WaterRun;
}

void PlayerWaterRun::OnCollision(GameObject* entity, float deltaTime)
{
}
