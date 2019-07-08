#include "PlayerDownStairState.h"


PlayerDownStairState::PlayerDownStairState(PlayerData * playerData):PlayerState(playerData)
{
	this->playerData = playerData;
	accelerateX = accelerateY = 20.0f;
}

PlayerDownStairState::~PlayerDownStairState()
{
}

void PlayerDownStairState::Update(float deltaTime)
{
	if (!isStopped)
	{
		playerData->player->SetVy(accelerateY);
		if (playerData->player->GetCurrentReverse())
		{
			playerData->player->SetVx(-accelerateX);
		}
		else
		{
			playerData->player->SetVx(accelerateX);
		}
	}
}

void PlayerDownStairState::HandleKeyboard(std::map<int, bool> keys)
{
	if (!keys[VK_DOWN])
	{
		//Stop anim
		playerData->player->SetVx(0);
		playerData->player->SetVy(0);
		isStopped = true;
	}
	else
	{
		isStopped = false;
	}
	if (keys[VK_UP])
	{
		bool curReverse = playerData->player->GetCurrentReverse();
		playerData->player->SetReverse(!curReverse);
		playerData->player->SetState(PlayerState::UpStair);
		return;
	}
	//Fighting
	if (keys[VK_C])
	{
		this->playerData->player->weaponPos = { 20,0,0 };
		this->playerData->player->SetState(new PlayerFightingState(playerData));
		return;
	}
}

void PlayerDownStairState::OnCollision(GameObject * entity, float deltaTime)
{
	if (entity->Tag == GameObject::StairBottomObj)
	{
		GameCollision* collision = new GameCollision();
		float collisionTime, normalX, normalY;
		Box playerBox = this->playerData->player->getBox();
		Box broadPhase = collision->getBroadPhaseRect(playerBox, deltaTime);
		if (collision->isCollide(broadPhase, entity->getBox()))
		{
			this->playerData->player->SetPosition(entity->GetPosition().x + entity->GetWidth() / 2,
				entity->getBox().top);
			this->playerData->player->SetState(PlayerState::Standing);
		}
		Memory::SafeDelete(collision);
	}
}

PlayerState::StateName PlayerDownStairState::GetState()
{
	return StateName::DownStair;
}
