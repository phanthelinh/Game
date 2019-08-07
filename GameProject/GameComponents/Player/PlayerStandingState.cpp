#include "PlayerStandingState.h"

PlayerStandingState::PlayerStandingState()
{
	PLAYER->vX = PLAYER->vY = 0;
	PLAYER->allow[Jumping] = true;
	PLAYER->allow[Moving] = true;
	PLAYER->allow[Attacking_Shield] = true;
	PLAYER->shield->isVisible = true;
	if (PLAYER->isImmu != false)
		PLAYER->isImmu = false;
	//sitting?
}

void PlayerStandingState::Update(float deltaTime)
{
	
}

void PlayerStandingState::HandleKeyboard(std::map<int, bool> keys, float deltaTime)
{
	if (keys[VK_LEFT] || keys[VK_RIGHT])
	{
		PLAYER->ChangeState(Running);
	}
	else if (keys[VK_UP])
	{
		PLAYER->currentAnim = PLAYER->animations[LookUpward];
		if (!PLAYER->shieldFlying)
		{
			PLAYER->shield->SetState(ShieldState::Shield_Upward);
		}
	}
	else if (keys[VK_DOWN])
	{
		PLAYER->ChangeState(Sitting);
	}
	else
	{
		PLAYER->currentAnim = PLAYER->animations[Standing];
	}
	if (keys['C'])
	{
		PLAYER->ChangeState(Dashing);
	}
	if (keys['X'] && PLAYER->allow[Jumping] && !PLAYER->LastKeyState[X])
	{
		PLAYER->LastKeyState[X] = true;
		PLAYER->ChangeState(Jumping);
	}
	if (!keys['X'])
	{
		PLAYER->LastKeyState[X] = false;
	}
}

StateName PlayerStandingState::GetState()
{
	return Standing;
}

void PlayerStandingState::OnCollision(GameObject* entity, float deltaTime) 
{
}
