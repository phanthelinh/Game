#include "PlayerAttackingState.h"

PlayerAttackingState::PlayerAttackingState()
{
	prevState = PLAYER->currentState->GetState();
	if (prevState == Standing || prevState == Running)
	{
		PLAYER->allow[Jumping] = true;
		PLAYER->allow[Sitting] = true;
		PLAYER->allow[Running] = true;
		PLAYER->currentAnim = PLAYER->animations[Attacking] = PLAYER->animations[Attacking_Shield];
		PLAYER->shield->SetState(ShieldState::Flying);
		
	}
	else if (prevState == Sitting)
	{
		PLAYER->currentAnim = PLAYER->animations[Attacking] = PLAYER->animations[Attacking_SitBump];
		PLAYER->shield->SetState(ShieldState::Shielded);
	}
	//reset anim
	PLAYER->currentAnim->ResetAnim();
}

void PlayerAttackingState::Update(float deltaTime)
{
	if (PLAYER->currentAnim->_isFinished)
	{
		PLAYER->ChangeState(new PlayerStandingState());
	}
}

void PlayerAttackingState::HandleKeyboard(std::map<int, bool> keys)
{
	if (!keys[VK_Z])
	{
		PLAYER->ChangeState(new PlayerStandingState());
	}
}

StateName PlayerAttackingState::GetState()
{
	return Attacking;
}
