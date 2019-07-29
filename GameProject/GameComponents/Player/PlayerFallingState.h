#pragma once
#include "Player.h"
#include "PlayerState.h"
#include "PlayerStandingState.h"
#include "PlayerKickingState.h"
#include <unordered_set>

class PlayerFallingState : public PlayerState
{
public:
	PlayerFallingState();
	// Inherited via PlayerState
	virtual void Update(float deltaTime) override;

	virtual void HandleKeyboard(std::map<int, bool> keys, float deltaTime) override;

	virtual StateName GetState() override;
	virtual void OnCollision(GameObject* entity, float deltaTime);
};
