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

void PlayerSittingState::HandleKeyboard(std::map<int, bool> keys)
{
	if (!keys[VK_DOWN])
	{
		PLAYER->posY -= 10;
		if(keys[VK_LEFT] || keys[VK_RIGHT])
			PLAYER->ChangeState(new PlayerRunningState());
		else
			PLAYER->ChangeState(new PlayerStandingState());
	}
}

StateName PlayerSittingState::GetState()
{
	return Sitting;
}
