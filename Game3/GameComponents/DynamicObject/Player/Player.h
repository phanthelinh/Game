#pragma once
#include "../../../Framework/Animation.h"
#include "PlayerData.h"
#include "PlayerState.h"
#include "PlayerRunningState.h"
#include "PlayerStandingState.h"
#include "PlayerFightingState.h"
#include "PlayerSitdownState.h"
#include "PlayerFallingState.h"
#include "PlayerJumpingState.h"
#include "PlayerUpStairState.h"
#include "PlayerDownStairState.h"
#include "../DynamicObject.h"
#include "../../GameObject.h"
#include "Weapon/Whip.h"


#define PLAYER_MAX_JUMP_VELOCITY		100.0f //van toc nhay lon nhat
#define PLAYER_MIN_JUMP_VELOCITY		-145.0f //van toc nhay thap nhat
#define PLAYER_MAX_RUNNING_SPEED		120.0f //toc do chay nhanh nhat cua player
#define PLAYER_FALLING					140.0f


class Player 
	:public DynamicObject
{
public:
	Player();
	~Player();

	enum MoveDirection
	{
		MoveToLeft,
		MoveToRight,
		None
	};
	RECT GetBound();

	void Update(float deltaTime);

	void Draw(D3DXVECTOR3 position, D3DXVECTOR3 cameraPosition, RECT sourceRect = RECT(), D3DXVECTOR3 center = D3DXVECTOR3());
	
	//Set new state
	void SetState(PlayerState * newState);
	//Return a PlayerState* coincide with the state name
	void SetState(PlayerState::StateName stateName);
	//Get the current state
	PlayerState::StateName GetState();
	//Get the the state before it change to Fight
	PlayerState::StateName GetLastState();
	//Get the direction of player, left or right
	MoveDirection GetDirection();
	//Handle key board, when it is pressed
	void HandleKeyboard(std::map<int, bool> keys);
	//Event on a key was pressed
	void OnKeyPressed(int key);
	//Event on a key was released
	void OnKeyUp(int key);
	//Set reverse anim, if true, flip horizontal
	void SetReverse(bool flag);
	//Get current reverse
	bool GetCurrentReverse();
	//Get current animation
	Animation* GetCurrentAnimation();
	//The offset position to draw player's weapon on Fight state
	D3DXVECTOR3 weaponPos;
	virtual Box getBox();
	//handle collision when player attack
	virtual void OnCollision(GameObject* entity, float deltaTime);
	//get waepon of certain object, used to check collision
	virtual GameObject* GetWeaponObject();

	PlayerData* GetPlayerData();
	void JumpBack();
	
	
	bool allowMoveLeft, allowMoveRight;
	//check if object is on ground or not
	bool onGround;
	bool onStair;
	bool allowUpStair, allowDownStair;
	
private:
	//Event on changing animation
	void ChangeAnimation(PlayerState::StateName state);
	PlayerState::StateName curState, lastState;
	PlayerData *playerData;
	bool allowJump;
	bool curReverse;
	bool isCollideStairBottom, isCollideStairTop;
	bool isStopAnim;
	Animation * curAnim,
		*standingAnim, //used with falling
		*runningAnim,
		*sittingAnim, //used with juming
		*downFightingAnim,
		*standFightingAnim,
		*upStairFightingAnim,
		*downStairFightingAnim,
		*upStairAnim,
		*downStairAnim;
	Whip* whip;
	//State
	int hp;
};
