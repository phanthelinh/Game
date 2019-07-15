#include "PlayerSittingState.h"

PlayerSittingState::PlayerSittingState()
{
	PLAYER->allow[Jumping] = false;
	PLAYER->allow[Attacking] = true;
	PLAYER->vX = PLAYER->vY = 0;
	PLAYER->posY += 10;		//make sure sprite is sitting on the ground
}

void PlayerSittingState::Update(float deltaTime)
{
	
}

void PlayerSittingState::HandleKeyboard(std::map<int, bool> keys)
{
	
	if (keys[VK_Z])
	{
		PLAYER->posY -= 10;
		PLAYER->ChangeState(new PlayerAttackingState());
	}
	else if (!keys[VK_DOWN])
	{
		PLAYER->posY -= 10;
		PLAYER->ChangeState(new PlayerStandingState());
	}
}

StateName PlayerSittingState::GetState()
{
	return Sitting;
}
