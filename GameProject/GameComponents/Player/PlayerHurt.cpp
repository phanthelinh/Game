#include "PlayerHurt.h"

PlayerHurt::PlayerHurt()
{
	PLAYER->allow[Running] = false;
	PLAYER->allow[Jumping] = false;
	PLAYER->allow[Attacking] = PLAYER->allow[Attacking_Shield]=false;
	PLAYER->allow[Sitting] = false;
}

void PlayerHurt::Update(float deltaTime)
{
	/*if (PLAYER->currentAnim->_isFinished)
	{
		PLAYER->ChangeState(StateName::Standing);
	}*/
}

void PlayerHurt::HandleKeyboard(std::map<int, bool> keys, float deltaTime)
{
}

StateName PlayerHurt::GetState()
{
	return StateName::Hurt;
}

void PlayerHurt::OnCollision(GameObject* entity, float deltaTime)
{
}
