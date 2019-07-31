#include "PlayerWaterRun.h"

PlayerWaterRun::PlayerWaterRun()
{
	PLAYER->allow[Running] = false;
	PLAYER->allow[Jumping] = false;
	PLAYER->allow[Attacking] = PLAYER->allow[Attacking_Shield]=false;
	PLAYER->allow[Sitting] = false;
}

void PlayerWaterRun::Update(float deltaTime)
{
	/*if (PLAYER->currentAnim->_isFinished)
	{
		PLAYER->ChangeState(StateName::Standing);
	}*/
}

void PlayerWaterRun::HandleKeyboard(std::map<int, bool> keys, float deltaTime)
{
}

StateName PlayerWaterRun::GetState()
{
	return StateName::WaterRun;
}

void PlayerWaterRun::OnCollision(GameObject* entity, float deltaTime)
{
}
