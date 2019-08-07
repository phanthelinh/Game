#include "PlayerKickingState.h"
#include "../Enemy/Enemy.h"
#include "../Enemy/DynamiteNapalm.h"
#include "../Effect/Explode.h"
#define GRAVITY 3.0f

PlayerKickingState::PlayerKickingState()
{
	PLAYER->allow[Attacking] = true;
	PLAYER->allow[Jumping] = false;
	PLAYER->allow[Kicking] = false;
	if (PLAYER->shieldFlying == false)
		PLAYER->shield->SetState(ShieldState::OnKick);
	startTime = GetTickCount();
}

void PlayerKickingState::Update(float deltaTime)
{
	PLAYER->posX = PLAYER->posX + PLAYER->vX * deltaTime;
	PLAYER->posY = PLAYER->posY + PLAYER->vY * deltaTime;
	auto v = PLAYER->vY;
	if (PLAYER->PreviousState == Jumping)
	{
		
			
	}
	PLAYER->vY += GRAVITY;
	if (PLAYER->vY >= 0)
	{
		PLAYER->allow[Kicking] = true;
		PLAYER->ChangeState(Falling);
	}
}

void PlayerKickingState::HandleKeyboard(std::map<int, bool> keys, float deltaTime)
{
	if (keys[VK_LEFT])
	{
		PLAYER->isReverse = false;
		PLAYER->vX = -PLAYER_RUNNING_SPEED;
	} 
	else if (keys[VK_RIGHT])
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

void PlayerKickingState::OnCollision(GameObject* entity, float deltaTime) 
{
	if (entity->tag == Tag::EnemyTag)
	{
		Enemy* temp = (Enemy*)entity;
		if (temp->enemySubTag == DMBossTag)
		{
			DynamiteNapalm* dmboss = (DynamiteNapalm*)temp;
			auto colRes = COLLISION->SweptAABB(PLAYER->GetBoundingBox(), dmboss->GetBoundingBox(), deltaTime);
			if (colRes.isCollide && dmboss->GetState() == DMThrowWait)
			{
				EXPLODE->ExplodeAt(dmboss->posX, dmboss->posY - 50);
				dmboss->currHealth -= 3;
				if (dmboss->currHealth <= 6)
				{
					dmboss->SetState(DMInjuredStand);
					dmboss->StateTime = GetTickCount();
				}
				else
				{
					dmboss->SetState(DMHurt);
					dmboss->StateTime = GetTickCount();
				}
			}
		}	
	}

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
