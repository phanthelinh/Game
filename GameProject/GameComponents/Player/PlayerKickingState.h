#pragma once
#include "Player.h"
#include "PlayerState.h"
#include <unordered_set>

class PlayerKickingState : public PlayerState
{
public:
	PlayerKickingState();
	// Inherited via PlayerState
	virtual void Update(float deltaTime) override;

	virtual void HandleKeyboard(std::map<int, bool> keys, float deltaTime) override;

	virtual StateName GetState() override;
	virtual void OnCollision(std::unordered_set<GameObject*> colliableObjects, float deltaTime);
};
