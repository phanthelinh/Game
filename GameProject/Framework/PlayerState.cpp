#include "PlayerState.h"

PlayerState::PlayerState(PlayerData* playerData)
{
	this->playerData = playerData;
}

PlayerState::~PlayerState()
{
}

void PlayerState::Update(float deltaTime)
{
}

void PlayerState::HandleKeyboard(std::map<int, bool> keys)
{
}
