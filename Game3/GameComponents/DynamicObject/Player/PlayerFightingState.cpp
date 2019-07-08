#include "PlayerFightingState.h"

PlayerFightingState::PlayerFightingState(PlayerData * playerData):PlayerState(playerData)
{
	this->playerData = playerData;

}

PlayerFightingState::~PlayerFightingState()
{
}

void PlayerFightingState::Update(float deltaTime)
{
	if (playerData->player->GetCurrentAnimation()->isFinishedAnim())
	{
		playerData->player->SetState(playerData->player->GetLastState());
	}
}

void PlayerFightingState::HandleKeyboard(std::map<int, bool> keys)
{
	
}

void PlayerFightingState::OnCollision(GameObject * entity, float deltaTime)
{
	//if (this->playerData->player->getWhip() != NULL)
	//{
	//	if (entity->Tag > GameObject::WallObj)
	//	{
	//		/*GameCollision* collision = new GameCollision();
	//		float collisionTime, normalX, normalY;
	//		Box playerBox = this->playerData->player->getBox();
	//		Box broadPhase = collision->getBroadPhaseRect(playerBox, deltaTime);
	//		if (collision->isCollide(broadPhase, entity->getBox()))
	//		{
	//			entity->SetVisible(false);
	//		}*/
	//		this->playerData->player->getWhip()->OnCollision(entity, deltaTime);
	//		//Memory::SafeDelete(collision);
	//	}
	//}
}

PlayerState::StateName PlayerFightingState::GetState()
{
	return StateName::Fighting;
}
