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
			PLAYER->allow[Sitting] = false;
			PLAYER->currentAnim = PLAYER->animations[Attacking_StandBump];
		}	
	}
	else if (prevState == Sitting)
	{
		PLAYER->currentAnim = PLAYER->animations[Attacking_SitBump];
		PLAYER->shield->SetState(ShieldState::Shielded);
	}
	//reset anim
	PLAYER->currentAnim->ResetAnim();
}

void PlayerAttackingState::Update(float deltaTime)
{
	StateName currentState = PLAYER->currentState->GetState();
	if (PLAYER->currentAnim->_isFinished)
	{
		if (currentState == Attacking_SitBump)
			PLAYER->ChangeState(Sitting);
		else if(currentState == Attacking_StandBump || currentState == Attacking_Shield)
			PLAYER->ChangeState(Standing);
	}
}

void PlayerAttackingState::HandleKeyboard(std::map<int, bool> keys, float deltaTime)
{
	if (!keys['X'])
	{
		PLAYER->LastKeyState[X] = false;
		PLAYER->KeyHoldTime[X] = 0.0f;
		PLAYER->LastPressTime[X] = 0.0f;
	}
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
	else if (prevState == Sitting)
		return Attacking_SitBump;
	return Attacking;
}
