#include "PlayerAttackingState.h"
#include <iostream>

PlayerAttackingState::PlayerAttackingState()
{
	PLAYER->isOnGround = true;
	PLAYER->shield->isVisible = true;
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
	}
	else if (prevState == Sitting)
	{
		PLAYER->currentAnim = PLAYER->animations[Attacking_SitBump];
		PLAYER->allow[Attacking_SitBump] = true;
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
		{
			PLAYER->posY -= 10;
			PLAYER->ChangeState(Sitting);
		}
		else if(currentState == Attacking_StandBump || currentState == Attacking_Shield)
			PLAYER->ChangeState(Standing);
	}
}

void PlayerAttackingState::HandleKeyboard(std::map<int, bool> keys, float deltaTime)
{
	if (!keys['X'])
	{
		PLAYER->LastKeyState[X] = false;
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
	else if (prevState == Attacking_StandBump)
		return Attacking_StandBump;
	return Standing;
}

void PlayerAttackingState::OnCollision(GameObject* entity, float deltaTime)
{
}
