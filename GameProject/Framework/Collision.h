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
	CollisionResult() { isCollide = false; entryTime = 1.0f; sideX = sideY = 0; sideCollided = CollisionSide::Unknown_; }
};

class Collision
{
private:
	static Collision* instance;
public:
	static Collision* GetInstance();

	bool IsCollide(BoundingBox b1, BoundingBox b2);

	CollisionResult SweptAABB(BoundingBox movingObj, BoundingBox staticObj, float deltaTime = 0);

	BoundingBox SlideCollision(BoundingBox movingObj, CollisionResult colResult);

	BoundingBox BounceCollision(BoundingBox movingObj, CollisionResult colResult);
};
