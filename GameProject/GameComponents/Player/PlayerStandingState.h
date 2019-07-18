#pragma once
#include "Player.h"
#include "PlayerState.h"
#include "PlayerRunningState.h"
#include "PlayerJumpingState.h"

class PlayerStandingState : public PlayerState
{
public:
	PlayerStandingState();
	// Inherited via PlayerState
	virtual void Update(float deltaTime) override;
	virtual void HandleKeyboard(std::map<int, bool> keys, float deltaTime) override;
	virtual StateName GetState() override;
};
