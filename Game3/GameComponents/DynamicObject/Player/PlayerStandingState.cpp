#include "PlayerStandingState.h"

PlayerStandingState::PlayerStandingState(PlayerData * playerData):PlayerState(playerData)
{
	this->playerData = playerData;
	playerData->player->SetVx(0);
	playerData->player->SetVy(0);
	//playerData->player->onGround = true;
}

PlayerStandingState::~PlayerStandingState()
{

}

void PlayerStandingState::Update(float deltaTime)
{
}

void PlayerStandingState::OnCollision(GameObject * entity, float deltaTime)
{
	GameCollision* collision = new GameCollision();
	float collisionTime, normalX, normalY;
	Box playerBox = this->playerData->player->getBox();
	Box broadPhase = collision->getBroadPhaseRect(playerBox, deltaTime);

	

	if (entity->Tag == GameObject::StairBottomObj && this->playerData->player->allowUpStair)
	{
		if (collision->isCollide(broadPhase, entity->getBox()))
		{
			if (entity->IsLeft())
			{
				this->playerData->player->SetReverse(true);
			}
			else
			{
				this->playerData->player->SetReverse(false);
			}
			this->playerData->player->SetPosition(entity->GetPosition().x + entity->GetWidth() / 2,
				entity->getBox().top + 2);
			this->playerData->player->SetState(PlayerState::UpStair);
		}
	}
	else if (entity->Tag > GameObject::WallObj && this->playerData->player->isEnable)
	{
		GameCollision* collision = new GameCollision();
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
	}
	Memory::SafeDelete(collision);
}

void PlayerStandingState::HandleKeyboard(std::map<int, bool> keys)
{
	if (keys[VK_LEFT] || keys[VK_RIGHT])
	{
		this->playerData->player->SetState(new PlayerRunningState(this->playerData));
		return;
	}
	if (keys[VK_DOWN])
	{
		this->playerData->player->allowDownStair = true;
		this->playerData->player->SetState(new PlayerSitdownState(playerData));
		return;
	}
	if (keys[VK_C])
	{
		this->playerData->player->weaponPos = { 20, 0, 0 };
		this->playerData->player->SetState(new PlayerFightingState(playerData));
		return;
	}
	if (keys[VK_UP]) 
	{
		this->playerData->player->allowUpStair = true;
		return;
	}
}

PlayerState::StateName PlayerStandingState::GetState()
{
	return PlayerState::Standing;
}
