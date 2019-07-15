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
		return;
	}
	if (keys[VK_Z])
	{
		PLAYER->ChangeState(new PlayerAttackingState());
		return;
	}
	if (keys[VK_UP])
	{
		PLAYER->currentAnim = PLAYER->animations[LookUpward];
		PLAYER->shield->SetState(ShieldState::Shield_Upward);
	}
	if (keys[VK_DOWN])
	{
		PLAYER->ChangeState(new PlayerSittingState());
		PLAYER->shield->SetState(ShieldState::Shielded);
	}
	else
	{
		PLAYER->currentAnim = PLAYER->animations[Standing];
		PLAYER->shield->SetState(ShieldState::Normal);
	}
}

StateName PlayerStandingState::GetState()
{
	return Standing;
}
