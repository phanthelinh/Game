#pragma once
#include "../GameObject.h"
#include "../Player/Player.h"
#include "Weapon.h"
#include <unordered_map>
#include <unordered_set>

class Enemy: public GameObject
{
private:
	static Player*	currPlayer;

public:
	Animation*		currentAnim;
	PlayerState*	currentState;
	float			maxHealth, currHealth;
	Weapon* weaponType;

	std::unordered_map<StateName, Animation*> animations;

	Enemy();

	virtual void Update(float deltaTime);

	virtual void Draw();

	virtual void SetState(StateName statename);

	virtual void CheckCollision(std::unordered_set<GameObject*> lstCollideable, float deltaTime);

	virtual void OnCollision(GameObject* object, float deltaTime = 0);


	virtual BoundingBox GetBoundingBox();

	virtual void Release();

};