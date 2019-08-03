#include "PlayerJumpingState.h"

#define PLAYER_JUMPING_SPEED -35.0f
#define GRAVITY 3.0f

PlayerJumpingState::PlayerJumpingState()
{
	PLAYER->allow[Attacking] = true;
	PLAYER->allow[Jumping] = false;
	PLAYER->vY = PLAYER_JUMPING_SPEED;
	PLAYER->isOnGround = false;
	if (PLAYER->shieldFlying == false)
		PLAYER->shield->SetState(ShieldState::OnJump);
}

void PlayerJumpingState::Update(float deltaTime)
{
	PLAYER->posX += PLAYER->vX * deltaTime;
	PLAYER->posY += PLAYER->vY * deltaTime;
	PLAYER->vY += GRAVITY;
	if (PLAYER->vY >= 0 && PLAYER->LastKeyState[X] == false)
	{
		PLAYER->ChangeState(Falling);
	}
}

void PlayerJumpingState::HandleKeyboard(std::map<int, bool> keys, float deltaTime)
{
	if (keys[VK_LEFT])
	{
		PLAYER->isReverse = false;
		PLAYER->vX = -PLAYER_RUNNING_SPEED;
	}
	if (keys[VK_RIGHT])
	{
		PLAYER->isReverse = true;
		PLAYER->vX = PLAYER_RUNNING_SPEED;
	}
	if (keys['Z'])
	{
		PLAYER->ChangeState(Kicking);
	}
	if (keys['X'])
	{
		if (PLAYER->vY >= 0)
		{
			PLAYER->ChangeState(Spinning);
		}
		PLAYER->LastKeyState[X] = true;
	}
	else
	{
		PLAYER->LastKeyState[X] = false;
	}
}

StateName PlayerJumpingState::GetState()
{
	return Jumping;
}

void PlayerJumpingState::OnCollision(GameObject* entity, float deltaTime)
{
}
