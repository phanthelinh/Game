#pragma once
#include "Player.h"
#include "PlayerState.h"
#include "PlayerOnShieldState.h"

class PlayerSpinningState : public PlayerState
{
public:
	PlayerSpinningState();
	// Inherited via PlayerState
	virtual void Update(float deltaTime) override;

	virtual void HandleKeyboard(std::map<int, bool> keys, float deltaTime) override;

	virtual StateName GetState() override;

};
