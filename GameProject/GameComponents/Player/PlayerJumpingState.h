#pragma once
#include "Player.h"
#include "PlayerState.h"
#include "PlayerFallingState.h"
#include "PlayerSpinningState.h"

class PlayerJumpingState : public PlayerState
{
public:
	PlayerJumpingState();
	// Inherited via PlayerState
	virtual void Update(float deltaTime) override;

	virtual void HandleKeyboard(std::map<int, bool> keys, float deltaTime) override;

	virtual StateName GetState() override;

};
