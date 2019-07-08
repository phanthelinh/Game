#include "GameCollision.h"


GameCollision::GameCollision()
{
}

GameCollision::~GameCollision()
{
}

bool GameCollision::isCollide(Box b1, Box b2)
{
	return !(b1.right < b2.left || b1.left > b2.right || b1.top > b2.bottom || b1.bottom < b2.top);
}

GameCollision::SideCollision GameCollision::GetSideCollision(Box source, Box target)
{
	if (source.left < target.right && source.right > target.left)
	{
		if (source.top <= target.bottom && source.top > target.top)
		{
			return SideCollision::Top;
		}
		if (source.bottom >= target.top && source.bottom < target.bottom)
		{
			return SideCollision::Bottom;
		}
	}
	if (source.top < target.bottom && source.bottom > target.top)
	{
		if (source.left <= target.right && source.left > target.left)
		{
			return SideCollision::Left;
		}
		if (source.right >= target.left && source.right < target.right)
		{
			return SideCollision::Right;
		}
	}
	return SideCollision::Unknown;
}

Box GameCollision::getBroadPhaseRect(Box b, float dtTime)
{
	//do truc y huong xuong -> vy > 0: vat dang di xuong
	Box BPhaseBox;

	BPhaseBox.left = b.vx > 0 ? b.left : b.left + b.vx*dtTime;
	BPhaseBox.top = b.vy > 0 ? b.top : b.top + b.vy*dtTime;
	BPhaseBox.right = b.vx > 0 ? b.right + b.vx*dtTime : b.right - b.vx*dtTime;
	BPhaseBox.bottom = b.vy > 0 ? b.bottom + b.vy*dtTime : b.bottom + b.vy*dtTime;
	BPhaseBox.vx = b.vx;
	BPhaseBox.vy = b.vy;

	return BPhaseBox;
}

double GameCollision::sweptAABB(Box movingObj, Box unmovingObj, float& normalX, float& normalY)
{
	float dxEntry, dyEntry;	//khoang cach obj can di de va cham
	float dxExit, dyExit;	//khoang cach obj de het va cham
	
	if (movingObj.vx > 0)
	{
		dxEntry = unmovingObj.left - movingObj.right;
		dxExit = unmovingObj.right - movingObj.left;
	}
	else {
		dxEntry = unmovingObj.right - movingObj.left;
		dxExit = unmovingObj.left - movingObj.right;
	}

	if (movingObj.vy > 0)	//vat di tu tren xuong
	{
		dyEntry = unmovingObj.top - movingObj.bottom;
		dyExit = unmovingObj.bottom - movingObj.top;
	}
	else {

		dyEntry = unmovingObj.bottom - movingObj.top;
		dyExit = unmovingObj.top - movingObj.bottom;
	}

	//thoi gian 2 object giao nhau tren cac truc
	double txEntry, tyEntry, txExit, tyExit;

	if (movingObj.vx == 0.0f)
	{
		//vi chia cho 0
		txEntry =  -INFINITY;
		txExit =  INFINITY;
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

	//thoi gian va cham se lay thoi gian entry lon nhat, vi phai giao nhau tren ca 2 truc
	//thoi gian ket thuc va cham se lay thoi gian exit nho nhat
	double tEntry, tExit;

	tEntry = (txEntry > tyEntry) ? txEntry : tyEntry;
	tExit = (txExit < tyExit) ? txExit : tyExit;

	//va cham xay ra khi tEntry < tExit 
	//0 < tEntry < 1
	if (tEntry > tExit || txEntry < 0.0f && tyEntry < 0.0f || txEntry > 1.0f || tyEntry > 1.0f) 
	{
		//khong xay ra va cham
		normalX = 0;
		normalY = 0;
		return 1.0f;	
	}

	if (txEntry > tyEntry)
	{
		//va cham vao ben phai
		if (dxEntry < 0.0f)
		{
			normalX = 1;
			normalY = 0;
		}
		else
		{
			normalX = -1;
			normalY = 0;
		}
	}
	else
	{
		//va cham phan top movingObj
		if (dyEntry < 0.0f)
		{
			normalX = 0;
			normalY = 1;
		}
		else
		{
			normalX = 0;
			normalY = -1;
		}
	}
	return tEntry;
}
