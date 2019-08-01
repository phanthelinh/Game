#include "PlayerInjuringState.h"

PlayerInjuringState::PlayerInjuringState()
{
	PLAYER->isOnGround = true;
}

void PlayerInjuringState::Update(float deltaTime)
{
}

void PlayerInjuringState::HandleKeyboard(std::map<int, bool> keys, float deltaTime)
{
	if (keys[VK_LEFT] || keys[VK_RIGHT])
	{
		PLAYER->ChangeState(Running);
	}
}

StateName PlayerInjuringState::GetState()
{
	return Injuring;
}

void PlayerInjuringState::OnCollision(GameObject* entity, float deltaTime)
{
}
