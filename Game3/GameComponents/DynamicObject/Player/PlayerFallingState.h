#pragma once
#include "Player.h"

class PlayerFallingState
	:public PlayerState
{
public:

	PlayerFallingState(PlayerData* playerData);

	~PlayerFallingState();

	virtual void Update(float deltaTime);

	virtual void HandleKeyboard(std::map<int, bool>keys);
	//handle collision when player attack
	virtual void OnCollision(GameObject* entity, float deltaTime);
	// Inherited via PlayerState
	virtual StateName GetState() override;

};
