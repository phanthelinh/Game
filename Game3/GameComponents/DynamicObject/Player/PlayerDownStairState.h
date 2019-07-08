#pragma once
#include "Player.h"

class PlayerDownStairState
	:public PlayerState
{
public:

	PlayerDownStairState(PlayerData * playerData);

	~PlayerDownStairState();

	virtual void Update(float deltaTime);

	virtual void HandleKeyboard(std::map<int, bool>keys);
	//handle collision when player attack
	virtual void OnCollision(GameObject* entity, float deltaTime);
	// Inherited via PlayerState
	virtual StateName GetState() override;
private:
	float accelerateX, accelerateY;
	bool isStopped;
};
