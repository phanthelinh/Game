#pragma once
#include "../../Framework/Animation.h"
#include "PlayerState.h"
#include "../GameObject.h"
#include "PlayerStandingState.h"
#include <unordered_map>
#include <unordered_set>
#include "../Shield/Shield.h"
#include "../../Framework/Global.h"
#include "../../Framework/Collision.h"

#define PLAYER	Player::GetInstance()


class Player
	:public GameObject
{
public:
	Player();

	static Player* GetInstance();

	void Update(float deltaTime);

	void Draw();

	void ChangeState(PlayerState* newState);

	void CheckCollision(std::unordered_set<GameObject*> colliableObjects);

	void HandleKeyboard(std::map<int, bool> keys);

	virtual BoundingBox GetBoundingBox();

	std::unordered_map<StateName, Animation*> animations;
	std::unordered_map<StateName, bool> allow;
	Animation*		currentAnim;
	PlayerState*	currentState;
	int				health, lives;
	bool			isOnGround, isAttacking, shieldFlying;
	Shield*			shield;
private:
	static Player*	instance;
};
