#pragma once
#define COLLISION Collision::GetInstance()

struct Box
{
	float left;
	float right;
	float top;
	float bottom;
	float vx;
	float vy;
};

enum CollisionSide
{
	Left,
	Top,
	Right,
	Bottom,
	Unknown
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

	bool IsCollide(Box b1, Box b2);

	CollisionResult SweptAABB(Box movingObj, Box staticObj);
};
