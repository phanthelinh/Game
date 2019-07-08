#pragma once
#include "Player.h"

class PlayerJumpingState
	:public PlayerState
{
public:

	PlayerJumpingState(PlayerData* playerData);

	~PlayerJumpingState();

	virtual void Update(float deltaTime);
	virtual void OnCollision(GameObject* entity, float deltaTime);
	virtual void HandleKeyboard(std::map<int, bool>keys);
	// Inherited via PlayerState
	virtual StateName GetState() override;
private:
	float acceleratorY;
};
