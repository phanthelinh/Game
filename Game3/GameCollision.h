#pragma once
#include <Windows.h>
#include<limits>

typedef struct Box {
	float left;
	float right;
	float top;
	float bottom;
	float vx;
	float vy;
};

class GameCollision
{
private:
	Box box;
public:
	GameCollision();
	~GameCollision();

	enum SideCollision
	{
		Top,
		Left,
		Right,
		Bottom,
		Unknown
	};

	bool isCollide(Box b1, Box b2);
	/*
	Get the side collision of source to target when they are already detected collision. Return the source's side collision
	*/
	SideCollision GetSideCollision(Box source, Box target);

	//tinh thoi gian va cham giua 2 hinh chu nhat
	double sweptAABB(Box movingObj, Box unmovingObj, float& normalX, float& normalY);
	
	//tim RECT bao phu obj tu vi tri ban dau den vi tri tiep theo
	//neu broadPhaseRect tim dc va cham unmovingObj => collision
	Box getBroadPhaseRect(Box b, float deltaTime);

	//float SweptAABB(Box b1, Box b2, float& normalx, float& normaly, int dt)
	//{
	//	float xInvEntry, yInvEntry;
	//	float xInvExit, yInvExit;

	//	// find the distance between the objects on the near and far sides for both x and y

	//	// ??ng b? d?u cho cùng h??ng thôi
	//	if (b1.vx > 0.0f)
	//	{
	//		xInvEntry = b2.left - b1.right;
	//		xInvExit = b2.right - b1.left;
	//	}
	//	else
	//	{
	//		xInvEntry = b2.right - b1.left;
	//		xInvExit = b2.left - b1.right;
	//	}

	//	if (b1.vy < 0.0f)
	//	{
	//		yInvEntry = b2.top - b1.bottom;
	//		yInvExit = b2.bottom - b1.top;
	//	}
	//	else
	//	{
	//		yInvEntry = b2.bottom - b1.top;
	//		yInvExit = b2.top - b1.bottom;
	//	}

	//	// find time of collision and time of leaving for each axis (if statement is to prevent divide by zero)

	//	//tìm th?i gian ?? b?t ??u và k?t thúc va ch?m :
	//	float xEntry, yEntry;
	//	float xExit, yExit;

	//	if (b1.vx == 0.0f)
	//	{
	//		xEntry = -INFINITY;
	//		xExit = INFINITY;
	//	}
	//	else
	//	{
	//		xEntry = xInvEntry / (b1.vx * dt);
	//		xExit = xInvExit / (b1.vx * dt);
	//	}

	//	if (b1.vy == 0.0f)
	//	{
	//		yEntry = -std::numeric_limits<float>::infinity();
	//		yExit = std::numeric_limits<float>::infinity();
	//	}
	//	else
	//	{
	//		yEntry = yInvEntry / (b1.vy * dt);
	//		yExit = yInvExit / (b1.vy * dt);
	//	}

	//	// th?i gian va ch?m là th?i gian l?n nh?t c?a 2 tr?c (2 tr?c ph?i cùng ti?p xúc thì m?i va ch?m)

	//	float entryTime = max(xEntry, yEntry);
	//	// th?i gian h?t va ch?m là th?i gian c?a 2 tr?c, (1 cái ra kh?i là object h?t va ch?m)
	//	float exitTime = min(xExit, yExit);

	//	// if there was no collision
	//	if (entryTime > exitTime || xEntry < 0.0f && yEntry < 0.0f || xEntry > 1.0f || yEntry > 1.0f)
	//	{
	//		normalx = 0.0f;
	//		normaly = 0.0f;
	//		return 1.0f;
	//	}
	//	else // if there was a collision
	//	{
	//		// calculate normal of collided surface
	//		if (xEntry > yEntry)
	//		{
	//			if (xInvEntry < 0.0f)
	//			{
	//				normalx = 1.0f;
	//				normaly = 0.0f;
	//			}
	//			else
	//			{
	//				normalx = -1.0f;
	//				normaly = 0.0f;
	//			}
	//		}
	//		else
	//		{
	//			if (yInvEntry < 0.0f)
	//			{
	//				normalx = 0.0f;
	//				normaly = 1.0f;
	//			}
	//			else
	//			{
	//				normalx = 0.0f;
	//				normaly = -1.0f;
	//			}
	//		}

	//		// return the time of collision
	//		return entryTime;
	//	}
	//}
};

