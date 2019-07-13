#pragma once
#include "../GameComponents/GameObject.h"

#define COLLISION Collision::GetInstance()


enum CollisionSide
{
	Left,
	Top,
	Right,
	Bottom,
	Unknown_
};

struct CollisionResult
{
	bool isCollide;
	float entryTime;
	int sideX, sideY;
	CollisionSide sideCollided;
};

class Collision
{
private:
	static Collision* instance;
public:
	static Collision* GetInstance();

	bool IsCollide(BoundingBox b1, BoundingBox b2);

	CollisionResult SweptAABB(BoundingBox movingObj, BoundingBox staticObj);
};
