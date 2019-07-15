#include "PlayerAttackingState.h"

PlayerAttackingState::PlayerAttackingState()
{
	prevState = PLAYER->currentState->GetState();
	if (prevState == Standing || prevState == Running)
	{
		PLAYER->allow[Jumping] = true;
		PLAYER->allow[Sitting] = true;
		PLAYER->allow[Running] = true;
		if (!PLAYER->shieldFlying)
		{
			PLAYER->currentAnim = PLAYER->animations[Attacking_Shield];
			PLAYER->shield->SetState(ShieldState::Flying);
		}
		else
		{
			PLAYER->currentAnim = PLAYER->animations[Attacking_StandBump];
		}
		//reset anim
		PLAYER->currentAnim->ResetAnim();
	}
	
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
	
}

StateName PlayerAttackingState::GetState()
{
	if (prevState == Standing || prevState == Running)
	{
		if (PLAYER->shieldFlying)
			return Attacking_StandBump;
		else
			return Attacking_Shield;
	}
	return Attacking;
}
