#include "PlayerUpStairState.h"

PlayerUpStairState::PlayerUpStairState(PlayerData * playerData):PlayerState(playerData)
{
	this->playerData = playerData;
	acceleratorY = 20.0f;
	acceleratorX = 20.0f;
	isStopped = false;
}

PlayerUpStairState::~PlayerUpStairState()
{
}

void PlayerUpStairState::Update(float deltaTime)
{
	if (!isStopped)
	{
		playerData->player->SetVy(-acceleratorY);
		if (playerData->player->GetCurrentReverse())
		{
			playerData->player->SetVx(-acceleratorX);
		}
		else
		{
			playerData->player->SetVx(acceleratorX);
		}
	}
}

void PlayerUpStairState::HandleKeyboard(std::map<int, bool> keys)
{
	if (!keys[VK_UP])
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
	if (keys[VK_DOWN])
	{
		bool curReverse = playerData->player->GetCurrentReverse();
		playerData->player->SetReverse(!curReverse);
		playerData->player->SetState(PlayerState::DownStair);
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

void PlayerUpStairState::OnCollision(GameObject * entity, float deltaTime)
{
	if (entity->Tag == GameObject::StairTopObj)
	{
		GameCollision* collision = new GameCollision();
		float collisionTime, normalX, normalY;
		Box playerBox = this->playerData->player->getBox();
		Box broadPhase = collision->getBroadPhaseRect(playerBox, deltaTime);
		if (collision->isCollide(broadPhase, entity->getBox()))
		{
			collisionTime = collision->sweptAABB(playerBox, entity->getBox(), normalX, normalY);
			if (collisionTime > 0.0f && collisionTime < 1.0f)
			{
				this->playerData->player->onGround = true;
				this->playerData->player->AddPosition(playerData->player->GetVx()*collisionTime /*+ entity->IsLeft()? 5 : -5*/,
					playerData->player->GetVy()*collisionTime);
				//this->playerData->player->AddPosition(playerData->player->GetVx()*collisionTime, playerData->player->GetVy()*collisionTime);
				//this->playerData->player->SetPosition(playerData->player->GetPosition().x, entity->getBox().bottom);
				this->playerData->player->SetState(PlayerState::Standing);
			}
		}
		Memory::SafeDelete(collision);
	}
}

PlayerState::StateName PlayerUpStairState::GetState()
{
	return StateName::UpStair;
}