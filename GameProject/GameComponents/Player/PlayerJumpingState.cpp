#include "PlayerJumpingState.h"

#define PLAYER_JUMPING_SPEED -250.0f
#define PLAYER_RUNNING_SPEED 80.0f
#define GRAVITY 10.0f

PlayerJumpingState::PlayerJumpingState()
{
	PLAYER->allow[Attacking] = true;
	PLAYER->allow[Jumping] = false;
	PLAYER->vY = PLAYER_JUMPING_SPEED;
}

void PlayerJumpingState::Update(float deltaTime)
{
	if (PLAYER->vY == 0)
		PLAYER->ChangeState(new PlayerFallingState());
	PLAYER->vY += GRAVITY;
	PLAYER->posX = PLAYER->posX + PLAYER->vX * deltaTime;
	PLAYER->posY = PLAYER->posY + PLAYER->vY * deltaTime;
}

void PlayerJumpingState::HandleKeyboard(std::map<int, bool> keys)
{
	if (keys[VK_LEFT])
	{
		PLAYER->isReverse = true;
		PLAYER->vX = -PLAYER_RUNNING_SPEED;
	}
	if (keys[VK_RIGHT])
	{
		PLAYER->isReverse = false;
		PLAYER->vX = PLAYER_RUNNING_SPEED;
	}
}

StateName PlayerJumpingState::GetState()
{
	return Jumping;
}
