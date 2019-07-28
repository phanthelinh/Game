#pragma once
#include "Player.h"
#include "PlayerState.h"

class PlayeDiedState : public PlayerState
{
public:
	PlayeDiedState();

	// Inherited via PlayerState
	virtual void Update(float deltaTime) override;
	virtual void HandleKeyboard(std::map<int, bool> keys, float deltaTime) override;
	virtual StateName GetState() override;
	virtual void OnCollision(GameObject* entity, float deltaTime);
};
