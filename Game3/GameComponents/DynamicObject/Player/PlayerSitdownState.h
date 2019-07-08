#pragma once
#include "Player.h"

class PlayerSitdownState
	: public PlayerState
{
public:
	PlayerSitdownState(PlayerData* playerData);
	~PlayerSitdownState();

	void Update(float deltaTime);
	void HandleKeyboard(std::map<int, bool>keys);
	// Inherited via PlayerState
	StateName GetState() override;
	//handle collision when player attack
	virtual void OnCollision(GameObject* entity, float deltaTime);

};
