#include "PlayerSpinningState.h"

#define SPINNING_BOOST -30.0f
#define GRAVITY 3.0f

PlayerSpinningState::PlayerSpinningState()
{
	PLAYER->allow[Attacking] = true;
	PLAYER->allow[Jumping] = false;
	PLAYER->vY = SPINNING_BOOST;
	if (PLAYER->shieldFlying == false)
		PLAYER->shield->isVisible = false;
}

void PlayerSpinningState::Update(float deltaTime)
{
	PLAYER->posX = PLAYER->posX + PLAYER->vX * deltaTime;
	PLAYER->posY = PLAYER->posY + PLAYER->vY * deltaTime;
	PLAYER->vY += GRAVITY;
	if (PLAYER->vY == 0)
	{
		PLAYER->ChangeState(Falling);
	}
}

void PlayerSpinningState::HandleKeyboard(std::map<int, bool> keys, float deltaTime)
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
	if (keys[VK_DOWN])
	{
		PLAYER->ChangeState(OnShield);
	}
	if (!keys['X'])
	{
		PLAYER->LastKeyState[X] = false;
	}
}

StateName PlayerSpinningState::GetState()
{
	return Spinning;
}

void PlayerSpinningState::OnCollision(GameObject* entity, float deltaTime) 
{
	if (entity->tag == GroundTag)
	{
		auto colRes = COLLISION->SweptAABB(PLAYER->GetBoundingBox(), entity->GetBoundingBox(), deltaTime);
		if (colRes.isCollide)
		{
			switch (colRes.sideCollided)
			{
			case CollisionSide::Top:
			{
				PLAYER->posX += PLAYER->vX*deltaTime;
				PLAYER->posY += PLAYER->vY*deltaTime;
				PLAYER->vY = 0.0f;
				SOUND->stop("jump");
				SOUND->play("jump");
				PLAYER->ChangeState(Falling);
				break;
			}
			case CollisionSide::Right:
			case CollisionSide::Left:
			{
				/*PLAYER->posX += PLAYER->vX*deltaTime;
				PLAYER->posY += PLAYER->vY*deltaTime;*/
				PLAYER->vX = 0.0f;
				SOUND->stop("jump");
				SOUND->play("jump");
				PLAYER->ChangeState(Falling);
				break;
			}
			default:
				break;
			}
		}
	}
}
