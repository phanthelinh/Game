#pragma once
#include "Player.h"
#include "PlayerState.h"

class PlayerStandingState
	:public PlayerState
{
public:
	PlayerStandingState(PlayerData *playerData);
	~PlayerStandingState();

	virtual void Update(float deltaTime);
	//handle collision when player attack
	virtual void OnCollision(GameObject* entity, float deltaTime);
	virtual void HandleKeyboard(std::map<int, bool> keys);

	StateName GetState();
};
