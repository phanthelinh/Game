#pragma once
#include "Player.h"

class PlayerRunningState 
	:public PlayerState
{
public:
	PlayerRunningState(PlayerData *playerData);
	~PlayerRunningState();

	void Update(float deltaTime);
	void HandleKeyboard(std::map<int, bool>keys);
	//handle collision when player attack
	virtual void OnCollision(GameObject* entity, float deltaTime);
	// Inherited via PlayerState
	StateName GetState() override;
private:
	//do bien tien van toc sau moi frame tinh bang pixel / s
	float acceleratorX;
};