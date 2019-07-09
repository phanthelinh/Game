#include "Collision.h"
#include <limits>
#include <algorithm>

Collision* Collision::instance = nullptr;

Collision * Collision::GetInstance()
{
	if (instance != nullptr)
		return instance;
	else
	{
		instance = new Collision();
		return instance;
	}
}

bool Collision::IsCollide(Box b1, Box b2)
{
	return !(b1.right < b2.left || b1.left > b2.right || b1.top > b2.bottom || b1.bottom < b2.top);
}

CollisionResult Collision::SweptAABB(Box movingObj, Box staticObj)
{
	float dxEntry, dyEntry;	//distance require occurring collision
	float dxExit, dyExit;	//disrtance require finishing collision
	
	CollisionResult result;
	result.isCollide = false;
	result.entryTime = 1.0f;
	result.sideX = result.sideY = 0;
	result.sideCollided = CollisionSide::Unknown;

	movingObj.vx = movingObj.vx - staticObj.vx;
	movingObj.vy = movingObj.vy - staticObj.vy;
	//y axis is looking down -> vy > 0: going down
	Box BPhaseBox;

	BPhaseBox.left = movingObj.vx > 0 ? movingObj.left : movingObj.left + movingObj.vx;
	BPhaseBox.top = movingObj.vy > 0 ? movingObj.top : movingObj.top + movingObj.vy;
	BPhaseBox.right = movingObj.vx > 0 ? movingObj.right + movingObj.vx : movingObj.right - movingObj.vx;
	BPhaseBox.bottom = movingObj.vy > 0 ? movingObj.bottom + movingObj.vy : movingObj.bottom + movingObj.vy;
	BPhaseBox.vx = movingObj.vx;
	BPhaseBox.vy = movingObj.vy;

	if (!IsCollide(BPhaseBox, staticObj))
		return result;

	if (movingObj.vx > 0)
	{
		dxEntry = staticObj.left - movingObj.right;
		dxExit = staticObj.right - movingObj.left;
	}
	else {
		dxEntry = staticObj.right - movingObj.left;
		dxExit = staticObj.left - movingObj.right;
	}
	//Object is going from top to bottom
	if (movingObj.vy > 0)	
	{
		dyEntry = staticObj.top - movingObj.bottom;
		dyExit = staticObj.bottom - movingObj.top;
	}
	else {

		dyEntry = staticObj.bottom - movingObj.top;
		dyExit = staticObj.top - movingObj.bottom;
	}

	//time to intersect with axises
	double txEntry, tyEntry, txExit, tyExit;

	if (movingObj.vx == 0.0f)
	{
		//due to diving by zero
		txEntry = -INFINITY;
		txExit = INFINITY;
	}
	else {
		txEntry = dxEntry / movingObj.vx;
		txExit = dxExit / movingObj.vx;
	}

	if (movingObj.vy == 0.0f)
	{
		tyEntry = -INFINITY;
		tyExit = INFINITY;
	}
	else {
		tyEntry = dyEntry / movingObj.vy;
		tyExit = dyExit / movingObj.vy;
	}
	float entryTime, exitTime;
	//Calculate time on entry and exit 
	entryTime = (float) std::max(txEntry, tyEntry);
	exitTime = (float) std::min(txExit, tyExit);

	//if not collision
	//collision occur when entryTime < exitTime 
	//0 < entryTime < 1
	if (entryTime > exitTime || (txEntry < 0.0f && tyEntry < 0.0f) || txEntry > 1.0f || tyEntry > 1.0f)
	{
		return result;
	}
	else
	{
		result.isCollide = true;
		result.entryTime = entryTime;

		if (txEntry > tyEntry)
		{
			if (dxEntry < 0.0f)
			{
				result.sideX = 1;
				result.sideY = 0;
				result.sideCollided = CollisionSide::Right;
			}
			else
			{
				result.sideX = -1;
				result.sideY = 0;
				result.sideCollided = CollisionSide::Left;
			}
			//result.sideX = (dxEntry < 0 ? 1 : -1);
		}
		else
		{
			if (dyEntry < 0)
			{
				result.sideX = 0;
				result.sideY = 1;
				result.sideCollided = CollisionSide::Top;
			}
			else
			{
				result.sideX = 0;
				result.sideY = -1;
				result.sideCollided = CollisionSide::Bottom;
			}
			//result.ny = (dyEntry < 0 ? 1 : -1);
		}
	}
	return result;
}
