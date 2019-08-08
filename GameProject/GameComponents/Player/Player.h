#pragma once
#include <unordered_map>
#include <unordered_set>
#include <exception>
#include "PlayerState.h"
#include "PlayerStandingState.h"
#include "PlayerDiedState.h"
#include "PlayerDashingState.h"
#include "PlayerHurt.h"
#include "PlayerWaterRun.h"
#include "PlayerWaterStand.h"
#include "PlayerInjuringState.h"
#include "../Shield/Shield.h"
#include "../../Framework/Global.h"
#include "../../Framework/Collision.h"
#include "../../Framework/Animation.h"
#include "../../Framework/Grid.h"

#define PLAYER	Player::GetInstance()

enum Button
{
	Z, //jump
	X, //attack or jump down
	C, //dash
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
	void Update(float deltaTime);

	void Draw();

	//void ChangeState(PlayerState* newState);
	void ChangeState(StateName statename);

	void CheckCollision(std::unordered_set<GameObject*> lstCollideable, float deltaTime);
	//Used for check collision with Ground
	void OnCollision(GameObject* object, float deltaTime = 0);
	void HandleKeyboard(std::map<int, bool> keys, float deltaTime);

	void OnKeyDown(int keyCode);

	void OnKeyUp(int keyCode);

	virtual BoundingBox GetBoundingBox();

	void Release();
	void JumpBack();	//when injured

	std::unordered_map<StateName, Animation*> animations;
	std::unordered_map<StateName, bool> allow;
	Animation*		currentAnim;
	PlayerState*	currentState;
	StateName PreviousState; //save the laststate of the character
	int				health, lives;
	bool			isOnGround, isAttacking, shieldFlying, isOnWater;
	bool			isImmu;
	Shield*			shield;
	RECT standingGround;	//save ground player is standing on
	bool			isBossKilled;	//flag for boss is killed
	float			scores;
	bool			isStandOnFlyingBar;
	GameObject*		barObject;
private:
	static Player*	instance;
};
