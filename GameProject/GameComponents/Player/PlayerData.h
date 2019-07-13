#pragma once
class PlayerState;
class Player;
//Temporary class, help to set one state to another state in Player class.
//This is a connection class
class PlayerData
{
public:
	PlayerData();
	~PlayerData();

	Player* player;
	PlayerState* state;

protected:
};