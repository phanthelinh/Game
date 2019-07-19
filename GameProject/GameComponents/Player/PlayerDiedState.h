#pragma once
#include "Player.h"
#include "PlayerState.h"

class PlayerDiedState : public PlayerState
{
public:


	// Inherited via PlayerState
	virtual void Update(float deltaTime) override;

	virtual void HandleKeyboard(std::map<int, bool> keys) override;

	virtual StateName GetState() override;

};
