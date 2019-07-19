#pragma once
#include "Player.h"
#include "PlayerState.h"
#include "PlayerRunningState.h"
#include "PlayerAttackingState.h"

class PlayerSittingState : public PlayerState
{
public:
	PlayerSittingState();
	// Inherited via PlayerState
	virtual void Update(float deltaTime) override;
	virtual void HandleKeyboard(std::map<int, bool> keys) override;
	virtual StateName GetState() override;
};
