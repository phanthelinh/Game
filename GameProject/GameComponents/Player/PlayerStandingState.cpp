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
	if (keys['X'] && PLAYER->allow[Jumping] && !PLAYER->LastKeyState[X])
	{
		PLAYER->ChangeState(new PlayerJumpingState());
		PLAYER->LastKeyState[X] = true;
	}
	if (GetKeyState('X') < 0)
	{
		PLAYER->LastKeyState[X] = true;
	}
	else
	{
		PLAYER->LastKeyState[X] = false;
	}
}

StateName PlayerStandingState::GetState()
{
	return Standing;
}
