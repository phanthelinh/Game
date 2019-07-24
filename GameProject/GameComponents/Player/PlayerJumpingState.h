#pragma once
#include "Player.h"
#include "PlayerState.h"
#include "PlayerFallingState.h"
#include "PlayerSpinningState.h"
#include <unordered_set>

class PlayerJumpingState : public PlayerState
{
public:
	float StartJumpDeltaTime = 0.0f; //the time player starts to jump
	PlayerJumpingState();
	// Inherited via PlayerState
	virtual void Update(float deltaTime) override;

	virtual void HandleKeyboard(std::map<int, bool> keys, float deltaTime) override;

	virtual StateName GetState() override;
	virtual void OnCollision(std::unordered_set<GameObject*> colliableObjects, float deltaTime);
};
