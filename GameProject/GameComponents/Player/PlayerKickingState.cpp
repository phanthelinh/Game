#include "PlayerKickingState.h"

#define PLAYER_RUNNING_SPEED 5.5f
#define GRAVITY 3.0f

PlayerKickingState::PlayerKickingState()
{
	PLAYER->allow[Attacking] = true;
	PLAYER->allow[Jumping] = false;
	PLAYER->isOnGround = true;
	if (PLAYER->shieldFlying == false)
		PLAYER->shield->SetState(ShieldState::OnKick);
}

void PlayerKickingState::Update(float deltaTime)
{
	PLAYER->posX = PLAYER->posX + PLAYER->vX * deltaTime;
	PLAYER->posY = PLAYER->posY + PLAYER->vY * deltaTime;
	if (PLAYER->PreviousState == Jumping)
	{
		PLAYER->vY += GRAVITY;
		if (PLAYER->vY >= 0)
			PLAYER->ChangeState(Falling);
	}
	else
	{
		PLAYER->vY -= GRAVITY;
		if (PLAYER->vY <= 0)
		{
			PLAYER->shield->SetState(ShieldState::Normal);
			PLAYER->ChangeState(Standing);
		}
	}
}

void PlayerKickingState::HandleKeyboard(std::map<int, bool> keys, float deltaTime)
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
	if (!keys['X'])
	{
		PLAYER->LastKeyState[X] = false;
	}
}

StateName PlayerKickingState::GetState()
{
	return Kicking;
}

void PlayerKickingState::OnCollision(std::unordered_set<GameObject*> colliableObjects, float deltaTime)
{
}
