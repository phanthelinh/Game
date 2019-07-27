#include "PlayerFallingState.h"

#define PLAYER_FALLING_SPEED 30.0f
#define PLAYER_RUNNING_SPEED 6.5f
#define GRAVITY 3.0f

PlayerFallingState::PlayerFallingState()
{
	PLAYER->allow[Attacking] = true;
	PLAYER->allow[Jumping] = false;
	PLAYER->isOnGround = false;
	//if (PLAYER->PreviousState != Kicking)
	if (PLAYER->PreviousState == Spinning)
	{
		PLAYER->vY += PLAYER_FALLING_SPEED + 13.0f;
	}
	else
	{
		PLAYER->vY += PLAYER_FALLING_SPEED;
	}
	PLAYER->shield->isVisible = false;
	
}

void PlayerFallingState::Update(float deltaTime)
{
	PLAYER->posX = PLAYER->posX + PLAYER->vX * deltaTime;
	PLAYER->posY = PLAYER->posY + PLAYER->vY * deltaTime;
	PLAYER->vY -= GRAVITY;
	if (PLAYER->vY <= 0)
		PLAYER->ChangeState(Standing);
}

void PlayerFallingState::HandleKeyboard(std::map<int, bool> keys, float deltaTime)
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
	if (keys[VK_DOWN] && PLAYER->PreviousState == Spinning)
	{
		PLAYER->ChangeState(OnShield);
	}
	if (keys['Z'])
	{
		PLAYER->ChangeState(Kicking);
	}
	if (!keys['X'])
	{
		PLAYER->LastKeyState[X] = false;
	}
}

StateName PlayerFallingState::GetState()
{
	return Falling;
}

void PlayerFallingState::OnCollision(std::unordered_set<GameObject*> colliableObjects, float deltaTime)
{

}
