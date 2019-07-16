#pragma once
#include "Player.h"
#include "PlayerState.h"

class PlayerKickingState : public PlayerState
{
public:
	PlayerKickingState();
	// Inherited via PlayerState
	virtual void Update(float deltaTime) override;

	virtual void HandleKeyboard(std::map<int, bool> keys) override;

	virtual StateName GetState() override;

};
