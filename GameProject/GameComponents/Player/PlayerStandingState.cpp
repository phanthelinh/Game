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
	else if (keys[VK_UP])
	{
		PLAYER->currentAnim = PLAYER->animations[LookUpward];
		PLAYER->shield->SetState(ShieldState::Shield_Upward);
	}
	else
	{
		PLAYER->currentAnim = PLAYER->animations[Standing];
	}
}

StateName PlayerStandingState::GetState()
{
	return Standing;
}
