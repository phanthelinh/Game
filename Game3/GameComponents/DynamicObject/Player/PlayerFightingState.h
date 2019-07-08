#pragma once
#include "PlayerState.h"
#include "Player.h"

class PlayerFightingState
	:public PlayerState
{
public:

	PlayerFightingState(PlayerData *playerData);
	~PlayerFightingState();

	virtual void Update(float deltaTime);
	virtual void HandleKeyboard(std::map<int, bool>keys);
	virtual void OnCollision(GameObject* entity, float deltaTime);
	// Inherited via PlayerState
	virtual StateName GetState() override;
private:
};
