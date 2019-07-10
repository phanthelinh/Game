#pragma once
#include <map>
#include "PlayerData.h"

class PlayerState
{
public:
	PlayerState(PlayerData* playerData);
	~PlayerState();

	enum StateName
	{
		Standing,
		Running,
		Falling,
		Jumping,
		Die
	};

	virtual void Update(float deltaTime);
	virtual void HandleKeyboard(std::map<int, bool>keys);
	virtual StateName GetState() = 0;
protected:
	PlayerData* playerData;
};
