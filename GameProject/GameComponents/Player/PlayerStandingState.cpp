#include "PlayerStandingState.h"

PlayerStandingState::PlayerStandingState()
{
	PLAYER->vX = PLAYER->vY = 0;
	PLAYER->allow[Jumping] = true;
	PLAYER->allow[Moving] = true;
	//sitting?

}

void PlayerStandingState::Update(float deltaTime)
{
	
}

void PlayerStandingState::HandleKeyboard(std::map<int, bool> keys)
{
	if (keys[VK_LEFT] || keys[VK_RIGHT])
	{
		PLAYER->ChangeState(new PlayerRunningState());
	}
	if (keys[VK_Z])
	{
		PLAYER->ChangeState(new PlayerAttackingState());
	}
}

StateName PlayerStandingState::GetState()
{
	return Standing;
}
