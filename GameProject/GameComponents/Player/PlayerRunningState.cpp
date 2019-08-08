#include "PlayerRunningState.h"

PlayerRunningState::PlayerRunningState()
{
	PLAYER->allow[Attacking] = true;
	PLAYER->allow[Jumping] = true;
	PLAYER->allow[Sitting] = true;
	PLAYER->vY = 0;
	PLAYER->isOnGround = true;
	PLAYER->shield->isVisible = true;
	if (PLAYER->shield->curState != ShieldState::Flying)
		PLAYER->shield->SetState(ShieldState::Normal);
}

void PlayerRunningState::Update(float deltaTime)
{
	PLAYER->posX = PLAYER->posX + PLAYER->vX * deltaTime;
	PLAYER->posY = PLAYER->posY + PLAYER->vY * deltaTime;
}

void PlayerRunningState::HandleKeyboard(std::map<int, bool> keys, float deltaTime)
{
	if (keys[VK_LEFT])
	{
		PLAYER->isReverse = false;
		PLAYER->vX = -PLAYER_RUNNING_SPEED;
	}
	else
	{
		if (keys[VK_RIGHT])
		{
			PLAYER->isReverse = true;
			PLAYER->vX = PLAYER_RUNNING_SPEED;
		}
		else
		{
			PLAYER->ChangeState(Standing);
		}
	}
	if (keys['C'])
	{
		SOUND->play("dash");
		PLAYER->ChangeState(Dashing);
	}
	if (keys['X'] && PLAYER->allow[Jumping] && !PLAYER->LastKeyState[X])
	{
		PLAYER->LastKeyState[X] = true;
		SOUND->play("jump");
		PLAYER->ChangeState(Jumping);
	}
	if (!keys['X'])
	{
		PLAYER->LastKeyState[X] = false;
	}
}

StateName PlayerRunningState::GetState()
{
	return Running;
}

void PlayerRunningState::OnCollision(GameObject* entity, float deltaTime) 
{
	CollisionResult res = COLLISION->SweptAABB(PLAYER->GetBoundingBox(), entity->GetBoundingBoxFromCorner(), deltaTime);
	if (res.isCollide && entity->tag == GroundTag && (res.sideCollided == Left || res.sideCollided == Right))
	{
		PLAYER->vX = 0;
	}
}
