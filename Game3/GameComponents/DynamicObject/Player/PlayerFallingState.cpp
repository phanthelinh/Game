#include "PlayerFallingState.h"

PlayerFallingState::PlayerFallingState(PlayerData * playerData):PlayerState(playerData)
{
	this->playerData = playerData;
	playerData->player->onGround = false;

}

PlayerFallingState::~PlayerFallingState()
{
}

void PlayerFallingState::Update(float deltaTime)
{
	this->playerData->player->SetVx(0);
	this->playerData->player->SetVy(PLAYER_FALLING);
}

void PlayerFallingState::HandleKeyboard(std::map<int, bool> keys)
{
}

void PlayerFallingState::OnCollision(GameObject * entity, float deltaTime)
{
	if (entity->Tag == GameObject::Ground)
	{
		GameCollision* collision = new GameCollision();
		float collisionTime, normalX, normalY;
		Box playerBox = this->playerData->player->getBox();
		Box broadPhase = collision->getBroadPhaseRect(playerBox, deltaTime);
		if (collision->isCollide(broadPhase, entity->getBox()))
		{
			if (playerData->player->GetPosition().x <= entity->getBox().right && playerData->player->GetPosition().x >= entity->getBox().left)
			{
				playerData->player->SetPosition(playerData->player->GetPosition().x,
					entity->getBox().top);
				playerData->player->SetState(PlayerState::Standing);
			}
		}
		Memory::SafeDelete(collision);
	}
}

PlayerState::StateName PlayerFallingState::GetState()
{
	return StateName::Falling;
}
