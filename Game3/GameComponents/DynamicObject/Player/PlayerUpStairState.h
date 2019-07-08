#pragma once
#include "Player.h"
 
class PlayerUpStairState :public PlayerState
{
public:
	PlayerUpStairState(PlayerData* playerData);
	~PlayerUpStairState();

	void Update(float deltaTime);
	void HandleKeyboard(std::map<int, bool>keys);
	//handle collision when player attack
	virtual void OnCollision(GameObject* entity, float deltaTime);
	// Inherited via PlayerState
	StateName GetState() override;
private:
	float acceleratorY;
	float acceleratorX;
	bool isStopped;
};
