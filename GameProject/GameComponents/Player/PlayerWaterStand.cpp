#include "PlayerWaterStand.h"

PlayerWaterStand::PlayerWaterStand()
{
	PLAYER->allow[Running] = false;
	PLAYER->allow[Jumping] = false;
	PLAYER->allow[Attacking] = PLAYER->allow[Attacking_Shield]=false;
	PLAYER->allow[Sitting] = false;
}

void PlayerWaterStand::Update(float deltaTime)
{
	/*if (PLAYER->currentAnim->_isFinished)
	{
		PLAYER->ChangeState(StateName::Standing);
	}*/
}

void PlayerWaterStand::HandleKeyboard(std::map<int, bool> keys, float deltaTime)
{
}

StateName PlayerWaterStand::GetState()
{
	return StateName::WaterStand;
}

void PlayerWaterStand::OnCollision(GameObject* entity, float deltaTime)
{
}
