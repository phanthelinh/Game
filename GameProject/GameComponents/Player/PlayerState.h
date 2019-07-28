#pragma once
#include "Player.h"
#include <unordered_set>
#include <map>
#include "../GameObject.h"

enum StateName
{
	Standing,
	Moving,
	Running,
	Falling,
	Jumping,
	Spinning,
	OnShield,
	Dashing,
	Kicking,
	LookUpward,
	Attacking,
	Attacking_Jump,
	Attacking_SitBump,
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
	virtual void HandleKeyboard(std::map<int, bool>keys, float deltaTime) = 0;
	virtual StateName GetState() = 0;
	virtual void OnCollision(GameObject* entity, float deltaTime) = 0;
};
