#include "PlayerSittingState.h"

PlayerSittingState::PlayerSittingState()
{
	PLAYER->allow[Jumping] = false;
	PLAYER->allow[Attacking_SitBump] = true;
	PLAYER->vX = PLAYER->vY = 0;
	PLAYER->posY += 10;		//make sure sprite is sitting on the ground
}

void PlayerSittingState::Update(float deltaTime)
{
	
}

void PlayerSittingState::HandleKeyboard(std::map<int, bool> keys, float deltaTime)
{
	if (!keys[VK_DOWN])
	{
		PLAYER->posY -= 10;
		if(keys[VK_LEFT] || keys[VK_RIGHT])
			PLAYER->ChangeState(Running);
		else
		{
			PLAYER->ChangeState(Standing);
			PLAYER->shield->SetState(ShieldState::Normal);
		}
	}
	if (!keys['X'])
	{
		PLAYER->LastKeyState[X] = false;
		PLAYER->KeyHoldTime[X] = 0.0f;
		PLAYER->LastPressTime[X] = 0.0f;
	}
}

StateName PlayerSittingState::GetState()
{
	return Sitting;
}
