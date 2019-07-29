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

bool Collision::IsCollide(BoundingBox b1, BoundingBox b2)
{
	return !(b1.right < b2.left || b1.left > b2.right || b1.top > b2.bottom || b1.bottom < b2.top);
}

CollisionResult Collision::SweptAABB(BoundingBox movingObj, BoundingBox staticObj, float deltaTime)
{
	float dxEntry, dyEntry;	//distance require occurring collision
	float dxExit, dyExit;	//disrtance require finishing collision
	
	CollisionResult result;
	result.isCollide = false;
	result.entryTime = 1.0f;
	result.sideX = result.sideY = 0;
	result.sideCollided = CollisionSide::Unknown_;

	movingObj.vX = movingObj.vX - staticObj.vX;
	movingObj.vY = movingObj.vY - staticObj.vY;
	//y axis is looking down -> vy > 0: going down
	BoundingBox BPhaseBox;
	if (deltaTime != 0)
	{
		BPhaseBox.left = movingObj.vX > 0 ? movingObj.left : movingObj.left + movingObj.vX*deltaTime;
		BPhaseBox.top = movingObj.vY > 0 ? movingObj.top : movingObj.top + movingObj.vY*deltaTime;
		BPhaseBox.right = movingObj.vX > 0 ? movingObj.right + movingObj.vX : movingObj.right - movingObj.vX*deltaTime;
		BPhaseBox.bottom = movingObj.vY > 0 ? movingObj.bottom + movingObj.vY : movingObj.bottom + movingObj.vY*deltaTime;
		BPhaseBox.vX = movingObj.vX;
		BPhaseBox.vY = movingObj.vY;
	}
	else
	{
		BPhaseBox.left = movingObj.vX > 0 ? movingObj.left : movingObj.left + movingObj.vX;
		BPhaseBox.top = movingObj.vY > 0 ? movingObj.top : movingObj.top + movingObj.vY;
		BPhaseBox.right = movingObj.vX > 0 ? movingObj.right + movingObj.vX : movingObj.right - movingObj.vX;
		BPhaseBox.bottom = movingObj.vY > 0 ? movingObj.bottom + movingObj.vY : movingObj.bottom + movingObj.vY;
		BPhaseBox.vX = movingObj.vX;
		BPhaseBox.vY = movingObj.vY;
	}

	if (!IsCollide(BPhaseBox, staticObj))
		return result;

	if (movingObj.vX > 0)
	{
		dxEntry = staticObj.left - movingObj.right;
		dxExit = staticObj.right - movingObj.left;
	}
	else {
		dxEntry = staticObj.right - movingObj.left;
		dxExit = staticObj.left - movingObj.right;
	}
	//Object is going from top to bottom
	if (movingObj.vY > 0)	
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

	if (movingObj.vX == 0.0f)
	{
		//due to diving by zero
		txEntry = -INFINITY;
		txExit = INFINITY;
	}
	else {
		txEntry = dxEntry / movingObj.vX;
		txExit = dxExit / movingObj.vX;
	}

	if (movingObj.vY == 0.0f)
	{
		tyEntry = -INFINITY;
		tyExit = INFINITY;
	}
	else {
		tyEntry = dyEntry / movingObj.vY;
		tyExit = dyExit / movingObj.vY;
	}
	float entryTime, exitTime;
	//Calculate time on entry and exit 
	entryTime = (float) max(txEntry, tyEntry);
	exitTime = (float) min(txExit, tyExit);

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

BoundingBox Collision::SlideCollision(BoundingBox movingObj, CollisionResult colResult)
{
	float remainTime = 1.0f - colResult.entryTime;
	//float mag = sqrt((movingObj.vX*movingObj.vX + movingObj.vY * movingObj.vY))*remainTime;
	float dotProduct = (movingObj.vX* colResult.sideY + movingObj.vY *colResult.sideX) *remainTime;
	BoundingBox b = movingObj;
	/*if (dotProduct > 0.0f)
		dotProduct = 1.0f;
	else if (dotProduct < 0.0f)
		dotProduct = -1.0f;
*/
	b.vX = dotProduct * colResult.sideY;// *mag;
	b.vY = dotProduct * colResult.sideX;// *mag;
	return b;
}

BoundingBox Collision::BounceCollision(BoundingBox movingObj, CollisionResult colResult)
{
	float remainTime = 1.0f - colResult.entryTime;
	BoundingBox b = movingObj;
	b.vX *= remainTime;
	b.vY *= remainTime;
	if (abs(colResult.sideX) > 0.0001f)
		b.vX *= -1;
	if (abs(colResult.sideY) > 0.0001f)
		b.vY *= -1;
	return b;
}
