#pragma once
#include "Player.h"
#include "PlayerState.h"
#include "PlayerStandingState.h"
#include "PlayerAttackingState.h"

class PlayerRunningState : public PlayerState
{
public:
	PlayerRunningState();
	// Inherited via PlayerState
	virtual void Update(float deltaTime) override;

	virtual void HandleKeyboard(std::map<int, bool> keys) override;

	virtual StateName GetState() override;

};
