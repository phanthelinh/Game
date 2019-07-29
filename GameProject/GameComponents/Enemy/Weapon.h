#pragma once
#include "../GameObject.h"
#include "Enemy.h"
#include <unordered_map>
#include <unordered_set>

class Weapon: public GameObject
{
private:
	static Enemy*	currEnemy;

public:
	float fDamage;
	Weapon();

};