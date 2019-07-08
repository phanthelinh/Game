#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include "GameComponents/GameObject.h"
#include "GlobalVar.h"
#include "GameComponents/DynamicObject/Enemy/AxeKnight.h"
#include "GameComponents/DynamicObject/Enemy/Fleamen.h"
#include "GameComponents/StaticObject/Ground/Ground.h"
#include "GameComponents/DynamicObject/Enemy/BoneTower.h"
#include "GameComponents/StaticObject/StairBottomObj.h"
#include "GameComponents/StaticObject/StairTopObj.h"
#include "GameComponents/DynamicObject/Enemy/RedSkeleton.h"
#include "GameComponents/DynamicObject/Enemy/Skeleton.h"
#include "GameComponents/DynamicObject/Door.h"
#include "GameComponents/StaticObject/Wall.h"
#include "GameComponents/DynamicObject/Candle/BigCandle.h"
#include "GameComponents/DynamicObject/Candle/Candle.h"
#include "GameComponents/DynamicObject/Enemy/Panther.h"

class GameUtility
{
public:
	GameUtility();
	~GameUtility();

	static void GetObjectInforFromFile(const char* filePath, std::vector<GameObject*> &list, GameObject::GameObjectTypes type, bool isLeft = false);
};

