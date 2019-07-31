#include "PlayerHurt.h"
#define GRAVITY 3.0f

PlayerHurt::PlayerHurt()
{
	PLAYER->allow[Running] = false;
	PLAYER->allow[Jumping] = false;
	PLAYER->allow[Attacking] = PLAYER->allow[Attacking_Shield]= false;
	PLAYER->allow[Sitting] = false;
	PLAYER->isImmu = true;
}

void PlayerHurt::Update(float deltaTime)
{
	PLAYER->posY = PLAYER->posY + PLAYER->vY * deltaTime;
	if (PLAYER->PreviousState == Jumping)
	{
		PLAYER->vY += GRAVITY;
	}
	if (PLAYER->currentAnim->_isFinished)
	{
		PLAYER->isImmu = false;
		PLAYER->ChangeState(StateName::Standing);
	}
}

void PlayerHurt::HandleKeyboard(std::map<int, bool> keys, float deltaTime)
{
}

StateName PlayerHurt::GetState()
{
	return StateName::Hurt;
}

void PlayerHurt::OnCollision(GameObject* entity, float deltaTime)
{
	CollisionResult res = COLLISION->SweptAABB(PLAYER->GetBoundingBox(), entity->GetBoundingBoxFromCorner(), deltaTime);
	if (res.isCollide && entity->tag == GroundTag && res.sideCollided == Bottom)
	{
		PLAYER->isOnGround = true;
		PLAYER->vY = 0;
	}
}
