#pragma once
#include "Player.h"
#include "PlayerState.h"
#include <unordered_set>
#include "PlayerStandingState.h"

class PlayerAttackingState :public PlayerState
{
private:
	StateName prevState;
public:
	PlayerAttackingState();

	// Inherited via PlayerState
	virtual void Update(float deltaTime) override;
	virtual void HandleKeyboard(std::map<int, bool> keys, float deltaTime) override;
	virtual StateName GetState() override;
	virtual void OnCollision(std::unordered_set<GameObject*> colliableObjects, float deltaTime);
};
