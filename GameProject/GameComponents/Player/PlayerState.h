#pragma once
#include "Player.h"
#include <map>

enum StateName
{
	Standing,
	Moving,
	Running,
	Falling,
	Jumping,
	Attacking,
	Attacking_Jump,
	Attacking_Sit,
	Attacking_Shield,
	Attacking_StandBump,
	Sitting,
	Die
};

class PlayerState
{
public:
	PlayerState(){}

	virtual void Update(float deltaTime) = 0;
	virtual void HandleKeyboard(std::map<int, bool>keys) = 0;
	virtual StateName GetState() = 0;
};