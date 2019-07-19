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

void PlayerStandingState::HandleKeyboard(std::map<int, bool> keys, float deltaTime)
{
	if (keys[VK_LEFT] || keys[VK_RIGHT])
	{
		PLAYER->ChangeState(Running);
	}
	else if (keys[VK_UP])
	{
		PLAYER->currentAnim = PLAYER->animations[LookUpward];
		PLAYER->shield->SetState(ShieldState::Shield_Upward);
	}
	else if (keys[VK_DOWN])
	{
		PLAYER->ChangeState(Sitting);
		PLAYER->shield->SetState(ShieldState::Shielded);
	}
	else
	{
		PLAYER->currentAnim = PLAYER->animations[Standing];
	}
	if (keys['X'] && PLAYER->allow[Jumping] && !PLAYER->LastKeyState[X])
	{
		PLAYER->LastKeyState[X] = true;
		PLAYER->LastPressTime[X] = deltaTime;
		PLAYER->KeyHoldTime[X] = 0.0f;
		PLAYER->ChangeState(Jumping);
	}
	if (!keys['X'])
	{
		PLAYER->LastKeyState[X] = false;
		PLAYER->KeyHoldTime[X] = 0.0f;
		PLAYER->LastPressTime[X] = 0.0f;
	}
}

StateName PlayerStandingState::GetState()
{
	return Standing;
}
