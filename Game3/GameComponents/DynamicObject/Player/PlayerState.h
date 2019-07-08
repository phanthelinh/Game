#pragma once
#include <map>
#include "PlayerData.h"
#include"../../GameObject.h"

class PlayerState
{
public:
	PlayerState(PlayerData *playerData);
	~PlayerState();

	enum StateName
	{
		Standing,
		Running,
		Sitting,
		Fighting,
		OnStair,
		Falling,
		Jumping,
		UpStair, DownStair
	};

	virtual void Update(float deltaTime);
	virtual void HandleKeyboard(std::map<int,bool>keys);
	//handle collision when player attack
	virtual void OnCollision(GameObject* entity, float deltaTime);
	virtual StateName GetState() = 0;
protected:
	PlayerData * playerData;
};
