#pragma once
#include "Player.h"
#include "PlayerState.h"
#include "PlayerStandingState.h"
#include "PlayerKickingState.h"

class PlayerSpinningState : public PlayerState
{
public:
	PlayerSpinningState();
	// Inherited via PlayerState
	virtual void Update(float deltaTime) override;

	virtual void HandleKeyboard(std::map<int, bool> keys) override;

	virtual StateName GetState() override;

};
