#include "PlayerFallingState.h"

#define PLAYER_FALLING_SPEED 40.0f
#define PLAYER_RUNNING_SPEED 7.5f
#define GRAVITY 3.0f

PlayerFallingState::PlayerFallingState()
{
	PLAYER->allow[Attacking] = true;
	PLAYER->allow[Jumping] = false;
	PLAYER->isOnGround = false;
	PLAYER->shield->isVisible = true;
	if (!PLAYER->shieldFlying)
		PLAYER->shield->SetState(ShieldState::OnJump);
}

void PlayerFallingState::Update(float deltaTime)
{
	PLAYER->posX = PLAYER->posX + PLAYER->vX * deltaTime;
	PLAYER->posY = PLAYER->posY + PLAYER->vY * deltaTime;
	PLAYER->vY += GRAVITY;
	PLAYER->vY >= 10.0f ? 10.0f : PLAYER->vY;
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

void PlayerFallingState::OnCollision(GameObject* entity, float deltaTime)
{
	CollisionResult res = COLLISION->SweptAABB(PLAYER->GetBoundingBox(), entity->GetBoundingBoxFromCorner(), deltaTime);
	if (res.isCollide && entity->tag == GroundTag && res.sideCollided == Bottom)
	{
		PLAYER->isOnGround = true;
		PLAYER->posY = entity->GetBoundFromCorner().top - PLAYER->height / 2;
		PLAYER->ChangeState(Standing);
		PLAYER->shield->SetState(ShieldState::Normal);
	}
	else if (res.isCollide && entity->tag == WaterTag && res.sideCollided == Bottom)
	{
		PLAYER->posY = entity->GetBoundFromCorner().top;
		PLAYER->isOnWater = true;
		PLAYER->ChangeState(WaterStand);
	}
	else
	{
		PLAYER->ChangeState(Falling);
	}
}
