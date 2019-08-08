#include "PlayerFallingState.h"

#define PLAYER_FALLING_SPEED 40.0f
#define GRAVITY 3.0f

PlayerFallingState::PlayerFallingState()
{
	PLAYER->allow[Attacking] = true;
	PLAYER->allow[Moving] = true;
	PLAYER->allow[Jumping] = false;
	PLAYER->isOnGround = false;
	PLAYER->shield->isVisible = true;
	if (!PLAYER->shieldFlying)
		PLAYER->shield->SetState(ShieldState::OnJump);
	if (PLAYER->isImmu != false)
		PLAYER->isImmu = false;
}

void PlayerFallingState::Update(float deltaTime)
{
	PLAYER->posX = PLAYER->posX + PLAYER->vX * deltaTime;
	PLAYER->posY = PLAYER->posY + PLAYER->vY * deltaTime;
	auto v = PLAYER->vY;
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
	if (keys['Z'] && PLAYER->allow[Kicking])
	{
		auto v = PLAYER->vY;
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
	if (entity == NULL)
		return;
	CollisionResult res = COLLISION->SweptAABB(PLAYER->GetBoundingBox(), entity->GetBoundingBoxFromCorner());
	if (res.isCollide && entity->tag == GroundTag && res.sideCollided == Bottom)
	{
		PLAYER->isOnGround = true;
		PLAYER->posY += PLAYER->vY*res.entryTime;//= entity->GetBoundFromCorner().top - PLAYER->height / 2;
		PLAYER->ChangeState(Standing);
		PLAYER->shield->SetState(ShieldState::Normal);
		PLAYER->standingGround = entity->GetBoundFromCorner();
	}
	else if (res.isCollide && entity->tag == GroundTag && (res.sideCollided == Left || res.sideCollided == Right))
	{
		/*PLAYER->posX += PLAYER->vX*deltaTime;
		PLAYER->posY += PLAYER->vY*deltaTime;*/
		PLAYER->vX = 0.0f;
	}
	else if (res.isCollide && entity->tag == WaterTag && res.sideCollided == Bottom)
	{
		PLAYER->posY += PLAYER->vY*res.entryTime + 5;
		PLAYER->isOnWater = true;
		PLAYER->ChangeState(WaterStand);
	}
}
