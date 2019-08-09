#include "PlayerOnShieldState.h"

#define PLAYER_FALLING_SPEED 40.0f
#define GRAVITY 3.0f

PlayerOnShieldState::PlayerOnShieldState()
{
	PLAYER->allow[Attacking] = true;
	PLAYER->allow[Jumping] = false;
	if (PLAYER->shieldFlying == false)
		PLAYER->shield->isVisible = false;
}

void PlayerOnShieldState::Update(float deltaTime)
{
	PLAYER->posX = PLAYER->posX + PLAYER->vX * deltaTime;
	PLAYER->posY = PLAYER->posY + PLAYER->vY * deltaTime;
	if (PLAYER->isOnGround == false && PLAYER->isOnWater == false)
		PLAYER->vY += GRAVITY;
}

void PlayerOnShieldState::HandleKeyboard(std::map<int, bool> keys, float deltaTime)
{
	if (keys[VK_LEFT])
	{
		if (PLAYER->isOnWater)
			PLAYER->ChangeState(WaterRun);
		else
		{
			PLAYER->ChangeState(Running);
		}
	}
	if (keys[VK_RIGHT])
	{
		if (PLAYER->isOnWater)
			PLAYER->ChangeState(WaterRun);
		else
		{
			PLAYER->ChangeState(Running);
		}
	}
	if (keys['Z'] && PLAYER->isOnWater == false)
	{
		SOUND->stop("jump");
		SOUND->play("attack");
		PLAYER->ChangeState(Attacking);
	}
	if (!keys[VK_DOWN])
	{
		if (PLAYER->isOnWater)
		{
			PLAYER->ChangeState(WaterStand);
		}
		else
		{
			PLAYER->posY -= 2;
			PLAYER->ChangeState(Standing);
			PLAYER->shield->SetState(ShieldState::Normal);
		}
	}
	if (!keys['X'])
	{
		PLAYER->LastKeyState[X] = false;
	}
}

StateName PlayerOnShieldState::GetState()
{
	return OnShield;
}

void PlayerOnShieldState::OnCollision(GameObject* entity, float deltaTime)
{
	CollisionResult res = COLLISION->SweptAABB(PLAYER->GetBoundingBox(), entity->GetBoundingBoxFromCorner(), deltaTime);
	if (res.isCollide && entity->tag == GroundTag && res.sideCollided == Bottom)
	{
		PLAYER->isOnGround = true;
		PLAYER->posX += PLAYER->vX*res.entryTime;
		PLAYER->posY += PLAYER->vY*res.entryTime;
		PLAYER->vY = 0;
		PLAYER->standingGround = entity->GetBoundFromCorner();
	}
	else if (res.isCollide && entity->tag == WaterTag && res.sideCollided == Bottom)
	{
		PLAYER->isOnWater = true;
		PLAYER->posX += PLAYER->vX*res.entryTime;
		PLAYER->posY += PLAYER->vY*res.entryTime;
		PLAYER->posY = entity->GetBoundFromCorner().top;
		PLAYER->vY = 0;
	}
}
