#pragma once
#include "Player.h"
#include "PlayerState.h"

class PlayerDashingState : public PlayerState
{
public:
	float StartJumpDeltaTime = 0.0f; //the time player starts to jump
	PlayerDashingState();
	// Inherited via PlayerState
	virtual void Update(float deltaTime) override;

	virtual void HandleKeyboard(std::map<int, bool> keys, float deltaTime) override;

	virtual StateName GetState() override;

};
