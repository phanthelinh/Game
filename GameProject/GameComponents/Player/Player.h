#pragma once
#include "../../Framework/Animation.h"
#include "PlayerState.h"
#include "../GameObject.h"
#include "PlayerStandingState.h"
#include <unordered_map>
#include <unordered_set>

#define PLAYER	Player::GetInstance()

enum Button
{
	Z,
	X,
	C
};

class Player
	:public GameObject
{
public:
	Player();

	static Player* GetInstance();
	std::unordered_map<Button, bool> LastKeyState; //save laststate of a key to handle input: true means last state it is helddown
	void Update(float deltaTime);

	void Draw();

	void ChangeState(PlayerState* newState);

	void CheckCollision(std::unordered_set<GameObject*> colliableObjects);

	void HandleKeyboard(std::map<int, bool> keys);


	std::unordered_map<StateName, Animation*> animations;
	std::unordered_map<StateName, bool> allow;
	Animation*		currentAnim;
	PlayerState*	currentState;
	StateName PreviousState; //save the laststate of the character
	int				health, lives;
	bool			isOnGround, isAttacking;
private:
	static Player*	instance;
};
