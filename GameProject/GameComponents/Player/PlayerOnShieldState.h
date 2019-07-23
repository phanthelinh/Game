#pragma once
#include "Player.h"
#include "PlayerState.h"

class PlayerOnShieldState : public PlayerState
{
public:
	int Gravity;
	float StartJumpDeltaTime = 0.0f; //the time player starts to jump
	PlayerOnShieldState();
	// Inherited via PlayerState
	virtual void Update(float deltaTime) override;

	virtual void HandleKeyboard(std::map<int, bool> keys, float deltaTime) override;

	virtual StateName GetState() override;

};
