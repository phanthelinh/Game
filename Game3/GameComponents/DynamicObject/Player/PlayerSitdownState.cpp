#include "PlayerSitdownState.h"

PlayerSitdownState::PlayerSitdownState(PlayerData * playerData):PlayerState(playerData)
{
	this->playerData = playerData;
}

PlayerSitdownState::~PlayerSitdownState()
{
}

void PlayerSitdownState::Update(float deltaTime)
{
}

void PlayerSitdownState::HandleKeyboard(std::map<int, bool> keys)
{
	if (keys[VK_C]) //C key
	{
		this->playerData->player->weaponPos = { 20, 5, 0 };
		this->playerData->player->SetState(new PlayerFightingState(this->playerData));
		return;
	}
	if (!keys[VK_DOWN])
	{
		this->playerData->player->SetState(new PlayerStandingState(playerData));
		return;
	}
	
}

PlayerState::StateName PlayerSitdownState::GetState()
{
	return StateName::Sitting;
}

void PlayerSitdownState::OnCollision(GameObject * entity, float deltaTime)
{
	if (entity->Tag == GameObject::StairTopObj && this->playerData->player->allowDownStair)
	{
		GameCollision* collision = new GameCollision();
		float collisionTime, normalX, normalY;
		Box playerBox = this->playerData->player->getBox();
		Box broadPhase = collision->getBroadPhaseRect(playerBox, deltaTime);
		if (collision->isCollide(broadPhase, entity->getBox()))
		{
			this->playerData->player->SetReverse(entity->IsLeft());
			this->playerData->player->SetState(PlayerState::DownStair);
		}
		Memory::SafeDelete(collision);
	}
}
