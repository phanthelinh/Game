#include "PlayerSittingState.h"

PlayerSittingState::PlayerSittingState()
{
	PLAYER->allow[Jumping] = false;
	PLAYER->isOnGround = true;
	PLAYER->allow[Attacking_SitBump] = true;
	PLAYER->vX = PLAYER->vY = 0;
	if(!PLAYER->shieldFlying)
		PLAYER->shield->SetState(ShieldState::Normal_Sit);
	PLAYER->posY += 10;		//make sure sprite is sitting on the ground
	PLAYER->shield->isVisible = true;
}

void PlayerSittingState::Update(float deltaTime)
{
	
}

void PlayerSittingState::HandleKeyboard(std::map<int, bool> keys, float deltaTime)
{
	if (!keys[VK_DOWN])
	{
		PLAYER->posY -= 10;
		PLAYER->ChangeState(Standing);
		if(!PLAYER->shieldFlying)
			PLAYER->shield->SetState(ShieldState::Normal);
	}
	if (!keys['X'])
	{
		PLAYER->LastKeyState[X] = false;
	}
	if (keys[VK_X])
	{
		if (PLAYER->standingGround.bottom - PLAYER->standingGround.top > 16)
			PLAYER->ChangeState(Jumping);
		else if(PLAYER->LastKeyState[X] == false)
		{
			PLAYER->ChangeState(Falling);
			PLAYER->LastKeyState[X] = true;
		}
		
	}
}

StateName PlayerSittingState::GetState()
{
	return Sitting;
}

void PlayerSittingState::OnCollision(GameObject* entity, float deltaTime) 
{
}
