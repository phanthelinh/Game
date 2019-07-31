#pragma once
#include "Player.h"
#include "PlayerState.h"

class PlayerWaterRun : public PlayerState
{
public:
	PlayerWaterRun();

	// Inherited via PlayerState
	virtual void Update(float deltaTime) override;
	virtual void HandleKeyboard(std::map<int, bool> keys, float deltaTime) override;
	virtual StateName GetState() override;
	virtual void OnCollision(GameObject* entity, float deltaTime);
};
