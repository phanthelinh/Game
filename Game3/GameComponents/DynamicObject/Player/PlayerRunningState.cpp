#include "PlayerRunningState.h"

PlayerRunningState::PlayerRunningState(PlayerData * playerData):PlayerState(playerData)
{
	this->playerData = playerData;
	acceleratorX = 70.0f;
}

PlayerRunningState::~PlayerRunningState()
{
}

void PlayerRunningState::Update(float deltaTime)
{
	/*if (!playerData->player->onGround)
	{
		playerData->player->SetState(PlayerState::Falling);
	}*/
}

void PlayerRunningState::HandleKeyboard(std::map<int, bool> keys)
{
	if (keys[VK_RIGHT])
	{
		if (playerData->player->allowMoveRight)
		{
			playerData->player->SetReverse(false);
			this->playerData->player->SetVx(acceleratorX);
			playerData->player->allowMoveLeft = true;
		}
		else
		{
			playerData->player->SetVx(0);
		}
	}
	else if (keys[VK_LEFT])
	{
		if (playerData->player->allowMoveLeft)
		{
			playerData->player->SetReverse(true);
			this->playerData->player->SetVx(-acceleratorX);
			playerData->player->allowMoveRight = true;
		}
		else
		{
			playerData->player->SetVx(0);
		}
	}
	else
	{
		this->playerData->player->SetState(new PlayerStandingState(this->playerData));
	}
}

void PlayerRunningState::OnCollision(GameObject * entity, float deltaTime)
{
	GameCollision* collision = new GameCollision();
	float collisionTime, normalX, normalY;
	Box playerBox = this->playerData->player->getBox();
	Box broadPhase = collision->getBroadPhaseRect(playerBox, deltaTime);

	if (entity->Tag == GameObject::Ground)
	{
		if (collision->isCollide(this->playerData->player->getBox(), entity->getBox()))
		{
			if (this->playerData->player->GetPosition().y <= entity->getBox().top &&
				this->playerData->player->GetPosition().x > entity->getBox().left &&
				this->playerData->player->GetPosition().x < entity->getBox().right) //stand on ground
				playerData->player->onGround = true;
		}
	}
	else if (entity->Tag == GameObject::WallObj)
	{
		if (collision->isCollide(broadPhase, entity->getBox()))
		{
			collisionTime = collision->sweptAABB(playerBox, entity->getBox(), normalX, normalY);
			if (collisionTime > 0.0f && collisionTime < 1.0f)
			{
				if (playerData->player->GetVx() > 0)
				{
					playerData->player->allowMoveRight = false;
				}
				else
				{
					playerData->player->allowMoveLeft = false;
				}
				this->playerData->player->SetVx(0);
			}
		}
	}
	else if (entity->Tag > GameObject::WallObj && this->playerData->player->isEnable)
	{
		
		float collisionTime, normalX, normalY;
		Box playerBox = this->playerData->player->getBox();
		Box broadPhase = collision->getBroadPhaseRect(playerBox, deltaTime);
		if (collision->isCollide(playerBox, entity->getBox()))
		{
			this->playerData->player->JumpBack();
		}
		else if (collision->isCollide(broadPhase, entity->getBox()))
		{
			collisionTime = collision->sweptAABB(playerBox, entity->getBox(), normalX, normalY);
			if (collisionTime > 0.0f && collisionTime < 1.0f)
			{
				this->playerData->player->JumpBack();
			}
		}

		Memory::SafeDelete(collision);
	}

}

PlayerState::StateName PlayerRunningState::GetState()
{
	return StateName::Running;
}
