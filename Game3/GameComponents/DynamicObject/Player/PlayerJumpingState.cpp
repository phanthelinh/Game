#include "PlayerJumpingState.h"
#include <math.h>
#define PI 3.14159265358979323846

PlayerJumpingState::PlayerJumpingState(PlayerData * playerData):PlayerState(playerData)
{
	this->playerData = playerData;
	playerData->player->SetVy(PLAYER_MIN_JUMP_VELOCITY);
	acceleratorY = 17.0f;
	this->playerData->player->onGround = false;
}

PlayerJumpingState::~PlayerJumpingState()
{
}

void PlayerJumpingState::Update(float deltaTime)
{
	this->playerData->player->AddVy(acceleratorY);
	if (playerData->player->GetVy() > PLAYER_MAX_JUMP_VELOCITY)
	{
		playerData->player->SetVy(PLAYER_MAX_JUMP_VELOCITY);
	}
}

void PlayerJumpingState::OnCollision(GameObject * entity, float deltaTime)
{
	GameCollision* collision = new GameCollision();
	float collisionTime, normalX, normalY;
	Box playerBox = this->playerData->player->getBox();
	Box broadPhase = collision->getBroadPhaseRect(playerBox, deltaTime);
	if (entity->Tag == GameObject::Ground)
	{

		if (collision->isCollide(broadPhase, entity->getBox()))
		{
			collisionTime = collision->sweptAABB(playerBox, entity->getBox(), normalX, normalY);
			if (collisionTime > 0.0f && collisionTime < 1.0f)
			{
				if (normalY < 0 && playerData->player->GetPosition().x <= entity->getBox().right && playerData->player->GetPosition().x >= entity->getBox().left)//bottom
				{
					playerData->player->SetPosition(playerData->player->GetPosition().x, entity->getBox().top);
					playerData->player->onGround = true;
					playerData->player->SetState(PlayerState::Standing);
				}
			}
		}
	}
	else if (entity->Tag == GameObject::WallObj)
	{
		if (collision->isCollide(broadPhase, entity->getBox()))
		{
			collisionTime = collision->sweptAABB(playerBox, entity->getBox(), normalX, normalY);
			if (collisionTime > 0.0f && collisionTime < 1.0f)
			{
				this->playerData->player->SetVx(0);
			}
		}
	}
	Memory::SafeDelete(collision);
}


void PlayerJumpingState::HandleKeyboard(std::map<int, bool> keys)
{
	
}

PlayerState::StateName PlayerJumpingState::GetState()
{
	return StateName::Jumping;
}
