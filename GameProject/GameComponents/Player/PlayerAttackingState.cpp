#include "PlayerAttackingState.h"
#include <iostream>

PlayerAttackingState::PlayerAttackingState()
{
	PLAYER->shield->isVisible = true;
	prevState = PLAYER->currentState->GetState();
	if (prevState == Standing || prevState == Running)
	{
		PLAYER->allow[Jumping] = true;
		PLAYER->allow[Sitting] = true;
		PLAYER->allow[Running] = true;
		if (!PLAYER->shieldFlying || PLAYER->shield->curState != Flying)
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
		if(!PLAYER->shieldFlying)
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
		if (prevState == Sitting)
		{
			PLAYER->posY -= 10;
		}
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
	return Attacking;
}

void PlayerAttackingState::OnCollision(GameObject* entity, float deltaTime)
{
}
