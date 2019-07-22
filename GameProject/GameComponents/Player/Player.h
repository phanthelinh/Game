#pragma once
#include <unordered_map>
#include <unordered_set>
#include <exception>
#include "../../Framework/Animation.h"
#include "PlayerState.h"
#include "../GameObject.h"
#include "PlayerStandingState.h"
#include "PlayerDiedState.h"
#include "../Shield/Shield.h"
#include "../../Framework/Global.h"
#include "../../Framework/Collision.h"

#define PLAYER	Player::GetInstance()

enum Button
{
	Z,
	X,
	C,
	LEFT,
	RIGHT
};

class Player
	:public GameObject
{
public:
	Player();

	static Player* GetInstance();
	std::unordered_map<Button, bool> LastKeyState; //save laststate of a key to handle input: true means last state it is helddown
	std::unordered_map<Button, float> LastPressTime; //save the deltaTime when the key was pressed last
	std::unordered_map<Button, float> KeyHoldTime; //calculate the time the key was held down
	void Update(float deltaTime);

	void Draw();

	//void ChangeState(PlayerState* newState);
	void ChangeState(StateName statename);

	void CheckCollision(std::unordered_set<GameObject*> colliableObjects);

	void HandleKeyboard(std::map<int, bool> keys, float deltaTime);

	void OnKeyDown(int keyCode);

	void OnKeyUp(int keyCode);

	virtual BoundingBox GetBoundingBox();

	void Release();

	std::unordered_map<StateName, Animation*> animations;
	std::unordered_map<StateName, bool> allow;
	Animation*		currentAnim;
	PlayerState*	currentState;
	StateName PreviousState; //save the laststate of the character
	int				health, lives;
	bool			isOnGround, isAttacking, shieldFlying;
	Shield*			shield;
private:
	static Player*	instance;

	bool startcheck = false;
};
