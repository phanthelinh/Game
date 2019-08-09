#include "PlayerWaterStand.h"
#define WATER_FORCE 2.0f

PlayerWaterStand::PlayerWaterStand()
{
	PLAYER->allow[Running] = true;
	PLAYER->allow[Jumping] = true;
	PLAYER->allow[Attacking] = PLAYER->allow[Attacking_Shield]=false;
	PLAYER->allow[Sitting] = false;
	PLAYER->shield->isVisible = false;
}

void PlayerWaterStand::Update(float deltaTime)
{
	PLAYER->vX = -WATER_FORCE;
	PLAYER->vY = 0.0f;
	PLAYER->posX += PLAYER->vX*deltaTime;
	PLAYER->posY += PLAYER->vY*deltaTime;
}

void PlayerWaterStand::HandleKeyboard(std::map<int, bool> keys, float deltaTime)
{
	if (keys[VK_LEFT] || keys[VK_RIGHT])
	{
		PLAYER->ChangeState(WaterRun);
	}
	if (keys['X'] && PLAYER->allow[Jumping] && !PLAYER->LastKeyState[X])
	{
		PLAYER->isOnWater = false;
		PLAYER->LastKeyState[X] = true;
		SOUND->play("jump");
		PLAYER->ChangeState(Jumping);
	}
	if (!keys['X'])
	{
		PLAYER->LastKeyState[X] = false;
	}
}

StateName PlayerWaterStand::GetState()
{
	return StateName::WaterStand;
}

void PlayerWaterStand::OnCollision(GameObject* entity, float deltaTime)
{
}
